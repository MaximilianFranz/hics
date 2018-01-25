#include <loader/weightloader/AlexNetWeightLoader.h>
#include "NetBuilder.h"
#include "NetInfo.h"
#include "NeuralNet.h"
#include <iostream>

int main(void){

    /*std::string FILE_PATH;
    FILE_PATH = "../../../src/netbuilder/loader/weightloader/alexnet_weights.h5";

    AlexNetWeightLoader alex(FILE_PATH);

    WeightWrapper test = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_2);
*/

    NetInfo netInfo("AlexNet", 227, "alexnet");
    NetBuilder builder;
    NeuralNet* net = builder.buildNeuralNet(netInfo);
    bool a = net->verifyConsistency();

    std::cout << a;
    
    return 0;
}