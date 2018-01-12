#include <loader/weightloader/AlexNetWeightLoader.h>

int main(void){

    std::string FILE_PATH;
    FILE_PATH = "/home/pselab/Dokumente/repo/hics/src/netbuilder/loader/weightloader/alexnet_weights.h5";

    AlexNetWeightLoader alex(FILE_PATH);

    WeightWrapper test = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::CONV_2);


    return 0;
}