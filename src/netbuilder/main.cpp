#include <loader/weightloader/AlexNetWeightLoader.h>
#include "NetBuilder.h"
#include "NetInfo.h"
#include "NeuralNet.h"
#include <iostream>

int main(void){

    std::string FILE_PATH;
    FILE_PATH = "../../../resources/weights/alexnet_weights.h5";

    AlexNetWeightLoader alex(FILE_PATH);

//    WeightWrapper conv1 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_1);
//    WeightWrapper conv2 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_2);
//    WeightWrapper conv3 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_3);
//    WeightWrapper conv4 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_4);
//    WeightWrapper conv5 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_5);
//    WeightWrapper dense1 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::FULLY_CON_1);
//    WeightWrapper dense2 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::FULLY_CON_2);
//    WeightWrapper dense3 = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::FULLY_CON_3);
//





/*    NetInfo netInfo("AlexNet", 227, "alexnet");
    NetBuilder builder;
    NeuralNet* net = builder.buildNeuralNet(netInfo);
    bool a = net->verifyConsistency();

    std::cout << a;*/
    
    return 0;
}