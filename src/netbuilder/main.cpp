#include <loader/weightloader/AlexNetWeightLoader.h>

int main(void){

    std::string FILE_PATH;
    FILE_PATH = "/home/pselab/Dokumente/repo/hics/src/netbuilder/loader/weightloader/alexnet_weights.h5";

    AlexNetWeightLoader alex(FILE_PATH);

    WeightWrapper test = alex.getWeights(AlexNetWeightLoader::LayerIdentifier::FULLY_CON_1);

    for(int i = 0; i<4096; i++){

        std::cout << "Bias index " << i << " has value : ";
        std::cout << test.getBias().at(i) << std::endl;

    }

    return 0;
}