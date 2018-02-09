//
// Created by michael on 15.01.18.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <cmath>
#include <limits>

#include <wrapper/DataWrapper.h>

#include <PlatformManager.h>
#include <loader/weightloader/AlexNetWeightLoader.h>
#include <algorithm>

#include "PlatformTest.h"

//const float eps = std::numeric_limits<float>::epsilon();
// be more lenient with our epsilon as our test data lacks the necessary precision
const float eps = 0.001;

TEST_CASE("Activation ReLU test") {
    PlatformManager& pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    ActivationFunction *f = p->createActivationFunction(LayerType::ACTIVATION_RELU);
    REQUIRE(f != nullptr);

    std::vector<float> data = {0, 2.2, -3.3f, 4.4, -5.5f};
    std::vector<int> s(1, 5);
    DataWrapper in(s, data);
    DataWrapper out(s);

    f->execute(in, out);
    REQUIRE(out.getData()[0] == 0);
    REQUIRE(out.getData()[1] == 2.2f);
    REQUIRE(out.getData()[2] == 0);
    REQUIRE(out.getData()[3] == 4.4f);
    REQUIRE(out.getData()[4] == 0);

}

TEST_CASE("Convolution test") {
    int inSize = 11;
    int stride = 1;
    int padding = 0;
    int filterSize = 3;
    int outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    int numFilters = 1;
    int numPlanes = 2;

    // generate input data
    std::vector<float> data;
    for (int y = 0 ; y < inSize; y++) {
        for (int x = 0; x < inSize; x++) {
            data.push_back(x+y);
        }
    }
    for (int y = 0 ; y < inSize; y++) {
        for (int x = 0; x < inSize; x++) {
            data.push_back(2*(x+y));
        }
    }

    DataWrapper input({numPlanes, inSize, inSize}, data);

    // output data
    DataWrapper output({numFilters, outSize, outSize});

    // filter data and bias data
    std::vector<float> filterData = {
            1,1,1,
            2,2,2,
            3,3,3,

            4,4,4,
            5,5,5,
            6,6,6,

    };
    std::vector<int> filterDim = {numPlanes, filterSize, filterSize};

    std::vector<float> biasData = {
            0.5
    };
    std::vector<int> biasDim = {numFilters};

    WeightWrapper weights(filterDim, filterData, biasData, biasDim);

    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    ConvolutionFunction *f = p->createConvolutionFunction();
    REQUIRE(f != nullptr);

    f->execute(input, output, weights, stride, filterSize, numFilters, padding);

    REQUIRE(output.getData()[0] == 234.5f);
    REQUIRE(output.getData()[10] == 450.5f);
    REQUIRE(output.getSizeOfDimension(2) == 9);


    // This time with padding
    padding = 1;
    outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    output = DataWrapper({numFilters, outSize, outSize});

    f->execute(input, output, weights, stride, filterSize, numFilters, padding);

    REQUIRE(output.getData()[0] == 57.5f);
    REQUIRE(output.getData()[12] == 234.5f);
    REQUIRE(output.getData()[24] == 450.5f);
    REQUIRE(output.getSizeOfDimension(2) == 11);

}

template<typename T>
std::vector<T> split(const std::string& line) {
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

std::vector<float> getDataFromFile(std::string path) {
    char* resolved_path;
    // Getting the real path from execution dir.
    // We pass NULL and let realpath allocate the string which means we have to free() it later.
    resolved_path = realpath(path.c_str(), NULL);
    // Open file
    std::ifstream file(resolved_path);
    std::string str;

    file.seekg(0, std::ios::end);
    str.reserve(static_cast<unsigned long>(file.tellg()));
    file.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(file)),
               std::istreambuf_iterator<char>());

    std::vector<float> data = split<float>(str);

    free(resolved_path);
    return data;
}

TEST_CASE("test with real data from AlexNet") {
    std::string img_data_path = TEST_RES_DIR "img_data.txt";
    std::string conv1_bias_path = TEST_RES_DIR "conv1_bias.txt";
    std::string conv1_weights_path = TEST_RES_DIR "conv1_weight.txt";
    std::string conv1_result_path = TEST_RES_DIR "conv1_data_alexnet.txt";
    std::string conv2_result_path = TEST_RES_DIR "conv2_data_out.txt";
    std::string weightspath = RES_DIR "weights/alexnet_weights.h5";

    std::vector<float> weights = getDataFromFile(conv1_weights_path);
    std::vector<float> bias = getDataFromFile(conv1_bias_path);
    std::vector<float> result = getDataFromFile(conv1_result_path);
    std::vector<float> image = getDataFromFile(img_data_path);

    std::vector<int> weightDim = {96,3,11,11};
    std::vector<int> biasDim = {96};
   // WeightWrapper weightsWrapper(weightDim, weights, bias, biasDim);
    AlexNetWeightLoader loader(weightspath);
    WeightWrapper *weightsWrapper = loader.getWeights(WeightLoader::LayerIdentifier::CONV_1);
    std::vector<int> inDim = {3, 227, 227};
    std::vector<int> outDim = {96, 55, 55};

    DataWrapper in(inDim, image);
    DataWrapper conv1_out(outDim);
    DataWrapper conv1_expected(outDim, result);

    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    /* Convolution */
    ConvolutionFunction *f = p->createConvolutionFunction();
    REQUIRE(f != nullptr);

    f->execute(in, conv1_out, *weightsWrapper, 4, 11, 96, 0);
    // out_real evaluates to 0 from i = 4 onwards

    for (int i = 0; i < 55*55; i++) { // Test the first filter fully
        REQUIRE(std::abs(conv1_out.getData()[i] - conv1_expected.getData()[i]) < eps);
    }

    for (int i = 0; i < 55*55*96; i += 2000) { // Pick one or two samples for each filter
        REQUIRE(std::abs(conv1_out.getData()[i] - conv1_expected.getData()[i]) < eps);
    }


    /* ReLU Activation */
    in = conv1_out;
    DataWrapper relu1_out(outDim);

    ActivationFunction *relu = p->createActivationFunction(LayerType::ACTIVATION_RELU);
    relu->execute(in, relu1_out);

    std::string relu1_result_path = TEST_RES_DIR "relu1_data_out.txt";
    std::vector<float> relu1_result = getDataFromFile(relu1_result_path);

    DataWrapper relu1_expected(outDim, relu1_result);
    for (int i = 0; i < 55*55; i ++) { // Test the first layer fully
        REQUIRE(std::abs(relu1_out.getData()[i] - relu1_expected.getData()[i]) < eps);
    }

    for (int i = 0; i < 55*55*96; i += 2000) { // Pick one or two samples for each filter
        REQUIRE(std::abs(relu1_out.getData()[i] - relu1_expected.getData()[i]) < eps);
    }


    /* Response Normalization */
    in = relu1_out;
    DataWrapper lrn1_out(outDim);

    ResponseNormalizationFunction *lrn = p->createResponseNormalizationFunction(LayerType::NORMALIZATION_LOCALRESPONSE);
    lrn->execute(in, lrn1_out, 2, 0.00002, 0.75, 1.0);

    std::string lrn1_result_path = TEST_RES_DIR "lrn1_data_out.txt";
    std::vector<float> lrn1_result = getDataFromFile(lrn1_result_path);

    DataWrapper lrn1_expected(outDim, lrn1_result);
    for (int i = 0; i < 55*55; i ++) { // Test the first layer fully
        REQUIRE(std::abs(lrn1_out.getData()[i] - lrn1_expected.getData()[i]) < eps);
    }

    for (int i = 0; i < 55*55*96; i += 2000) { // Pick one or two samples for each filter
        REQUIRE(std::abs(lrn1_out.getData()[i] - lrn1_expected.getData()[i]) < eps);
    }


    /* Maxpooling */
    in = lrn1_out;
    DataWrapper maxpool1_out({96, 27, 27});
    PoolingFunction *maxpool = p->createPoolingFunction(LayerType::POOLING_MAX);
    maxpool->execute(in, maxpool1_out, 2, 3, 0);

    std::string maxpool1_result_path = TEST_RES_DIR "maxpool_data_out.txt";
    std::vector<float> maxpool1_result = getDataFromFile(maxpool1_result_path);

    DataWrapper maxpool1_expected({96, 27, 27}, maxpool1_result);
    for (int i = 0; i < 27*27; i ++) { // Test the first layer fully
        REQUIRE(std::abs(maxpool1_out.getData()[i] - maxpool1_expected.getData()[i]) < eps);

    }

    for (int i = 0; i < 27*27*96; i += 400) { // Pick one or two samples for each filter
        REQUIRE(std::abs(maxpool1_out.getData()[i] - maxpool1_expected.getData()[i]) < eps);
    }

}

TEST_CASE("Maxpooling test") {
    int inSize = 5;
    int stride = 1;
    int padding = 0;
    int filterSize = 2;
    int outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    int numPlanes = 1;

    // generate input data
    std::vector<float> data;
    for (int y = 0 ; y < inSize; y++) {
        for (int x = 0; x < inSize; x++) {
            data.push_back(x+y);
        }
    }

    DataWrapper input({numPlanes, inSize, inSize}, data);
    DataWrapper output({numPlanes, outSize, outSize});


    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    PoolingFunction *f = p->createPoolingFunction(LayerType::POOLING_MAX);
    REQUIRE(f != nullptr);

    f->execute(input, output, stride, filterSize, padding);

    REQUIRE(output.getDimensions()[2] == 4);
    REQUIRE(output.getData()[0] == 2);
    REQUIRE(output.getData()[15] == 8);

    /* stride 2 will lead to cut-off */
    stride = 2;
    padding = 0;
    filterSize = 2;
    outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    output= DataWrapper({numPlanes, outSize, outSize});

    f->execute(input, output, stride, filterSize, padding);

    REQUIRE(output.getDimensions()[2] == 2);
    REQUIRE(output.getData()[1] == 4);
    REQUIRE(output.getData()[3] == 6);

    /* add some padding */
    stride = 2;
    padding = 1;
    filterSize = 3;
    outSize = (inSize - filterSize + 2 * padding) / stride + 1;
    output= DataWrapper({numPlanes, outSize, outSize});

    f->execute(input, output, stride, filterSize, padding);

    REQUIRE(output.getDimensions()[2] == 3);
    REQUIRE(output.getData()[1] == 4);
    REQUIRE(output.getData()[8] == 8);
}

TEST_CASE("Softmax test") {
    std::vector<float> data = {1, 2, 3, 4, 1, 2, 3};
    DataWrapper input({1, 7}, data);
    DataWrapper output({1, 7});

    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    LossFunction *f = p->createLossFunction(LayerType::LOSS_SOFTMAX);
    REQUIRE(f != nullptr);

    f->execute(input, output);

    REQUIRE(std::abs(output.getData()[0] - 0.024) < eps);

    float sum = 0;
    int n = output.getNumElements();
    for (int i = 0; i < n; i++) {
        sum += output.getData()[i];
    }
    REQUIRE(std::abs(sum - 1.0) < eps);
}

TEST_CASE("FullyConnected") {



    std::vector<float> easy_in = {1, 2, 3, 4};
    std::vector<float> easy_weights = {1, 1, 1, 1,
                                       2, 2, 2, 2,
                                       3, 3, 3, 3,
                                       4, 4, 4 ,4,
                                        5, 5, 5, 5};
    std::vector<float> easy_result = {10.1, 20.2, 30.3, 40.4, 50.5};



    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    FullyConnectedFunction *fc = p->createFullyConnectedFunction();
    REQUIRE(fc != nullptr);

//    ActivationFunction *relu = p->createActivationFunction(LayerType::ACTIVATION_RELU);
//    REQUIRE(relu != nullptr);

//    AlexNetWeightLoader loader(weightspath);
//    WeightWrapper fc1_weights = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_1); //TODO: Change after merge to new enum!

    DataWrapper in({4}, easy_in);
    DataWrapper out_fc({5});
    std::vector<int> biasDim = {5};
    std::vector<int> weightDim = {4, 5};
    std::vector<float> bias = {0.1, 0.2, 0.3, 0.4, 0.5};
    WeightWrapper easy_w(weightDim, easy_weights, bias , biasDim);

    fc->execute(in,out_fc,easy_w);
    for (int i = 0; i < 5; i++) {
        REQUIRE(out_fc.getData().at(i) == easy_result.at(i));
    }



}

TEST_CASE("FullyConnected one with real data") {
    std::string fc1_in = TEST_RES_DIR "fc1_data_in_flat.txt";
    std::string fc1_out = TEST_RES_DIR "fc1_data_out.txt";
    std::string weightspath = RES_DIR "weights/alexnet_weights.h5";
    std::string weightFile = TEST_RES_DIR "fc1_weights.txt";
    std::string biasFile = TEST_RES_DIR "fc1_bias.txt";

    std::vector<float> result = getDataFromFile(fc1_out);
    std::vector<float> input = getDataFromFile(fc1_in);

    std::vector<int> inDim = {9216};
    std::vector<int> outDim = {4098};

    AlexNetWeightLoader loader(weightspath);
    WeightWrapper *fc1_weights = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_1); //TODO: Change after merge to new enum!
    std::vector<float> weight = fc1_weights->getData();
    std::vector<float> bias = fc1_weights->getBias();
    WeightWrapper *transformedWeights = new WeightWrapper({4096,9216},weight, bias ,{4096} );

    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    FullyConnectedFunction *fc = p->createFullyConnectedFunction();
    REQUIRE(fc != nullptr);

    DataWrapper in({9216}, input);
    DataWrapper out_fc({4096});

    fc->execute(in, out_fc, *transformedWeights);


    ActivationFunction *relu = p->createActivationFunction(LayerType::ACTIVATION_RELU);

    DataWrapper out_relu({4096});

    relu->execute(out_fc, out_relu);

    for(int i = 0; i < 4096; i++) {
        REQUIRE(std::abs(out_relu.getData().at(i) - result.at(i)) < eps);
    }

}

TEST_CASE("FullyConnected two with real data") {
    std::string fc2_in = TEST_RES_DIR "fc7_in.txt";
    std::string fc2_out = TEST_RES_DIR "fc7_out.txt";
    std::string weightspath = RES_DIR "weights/alexnet_weights.h5";

    std::vector<float> result = getDataFromFile(fc2_out);
    std::vector<float> input = getDataFromFile(fc2_in);

    std::vector<int> inDim = {9216};
    std::vector<int> outDim = {4096};

    AlexNetWeightLoader loader(weightspath);
    WeightWrapper *fc1_weights = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_2); //TODO: Change after merge to new enum!


    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    FullyConnectedFunction *fc = p->createFullyConnectedFunction();
    REQUIRE(fc != nullptr);

    DataWrapper in({4096}, input);
    DataWrapper out_fc({4096});

    fc->execute(in, out_fc, *fc1_weights);


    ActivationFunction *relu = p->createActivationFunction(LayerType::ACTIVATION_RELU);

    DataWrapper out_relu({4096});

    relu->execute(out_fc, out_relu);

    for(int i = 0; i < 4096; i++) {
        REQUIRE(std::fabs(out_relu.getData().at(i) - result.at(i)) < eps);
    }

}


TEST_CASE("FullyConnected three with real data") {
    std::string fc3_in = TEST_RES_DIR "fc7_out.txt";
    std::string fc3_out = TEST_RES_DIR "fc8_out.txt";
    std::string weightspath = RES_DIR "weights/alexnet_weights.h5";

    std::vector<float> result = getDataFromFile(fc3_out);
    std::vector<float> input = getDataFromFile(fc3_in);


    AlexNetWeightLoader loader(weightspath);
    WeightWrapper *fc1_weights = loader.getWeights(WeightLoader::LayerIdentifier::FULLY_CON_3); //TODO: Change after merge to new enum!


    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    FullyConnectedFunction *fc = p->createFullyConnectedFunction();
    REQUIRE(fc != nullptr);

    DataWrapper in({4096}, input);
    DataWrapper out_fc({1000});

    fc->execute(in, out_fc, *fc1_weights);


    for(int i = 0; i < 1000; i++) {
        REQUIRE(std::fabs(out_fc.getData().at(i) - result.at(i)) < eps);
    }

}

TEST_CASE("Softmax with real data") {
    std::string sm_in = TEST_RES_DIR "fc8_out.txt";
    std::string sm_out = TEST_RES_DIR "sm_out.txt";
    std::string weightspath = RES_DIR "weights/alexnet_weights.h5";

    std::vector<float> result = getDataFromFile(sm_out);
    std::vector<float> input = getDataFromFile(sm_in);


    AlexNetWeightLoader loader(weightspath);


    PlatformManager &pm = PlatformManager::getInstance();
    REQUIRE(pm.getPlatforms().size() >= 1);

    Platform *p = pm.getPlatforms()[0];
    REQUIRE(p != nullptr);

    LossFunction *sm = p->createLossFunction(LayerType::LOSS_SOFTMAX);
    REQUIRE(sm != nullptr);

    DataWrapper in({1000}, input);
    DataWrapper out_sm({1000});

    sm->execute(in, out_sm);

    std::vector<float> sortRes = result;
    std::sort(sortRes.begin(), sortRes.end());

    std::vector<float> sortOut = out_sm.getData();
    std::sort(sortOut.begin(), sortOut.end());


    for(int i = 0; i < 1000; i++) {
        REQUIRE(std::fabs(out_sm.getData().at(i) - result.at(i)) < eps);
    }

}