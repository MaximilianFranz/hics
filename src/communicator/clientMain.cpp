//
// Created by jallmenroeder on 04/02/18.
//

#include <iostream>
#include <sstream>
#include <fstream>
//#include <ClassificationRequest.h>
#include "Client.h"

template<typename T>
static std::vector<T> split(const std::string& line) {
    std::istringstream is(line);
    return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

static std::vector<float> getDataFromFile(std::string path) {
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

int main() {
    Client client = Client(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    std::vector<NetInfo*> nets = client.queryNets();
    NetInfo alexnetinfo = *nets.at(0);

    std::string img_data_path = "../../../tests/resources/img_data.txt";

    std::vector<float> image = getDataFromFile(img_data_path);

    std::vector<int> imgDim = {3,227,227};
    ImageWrapper *img = new ImageWrapper(imgDim, image, "filepath");

    std::vector<ImageResult*> results;
    std::vector<PlatformInfo*> info_mock;
    results = client.classify({img}, alexnetinfo, OperationMode::EnergyEfficient, info_mock);

    //ClassificationRequest request = ClassificationRequest()

    std::cout << nets[0]->getName() << std::endl;

    std::vector<PlatformInfo*> platforms = client.queryPlatform();

    std::cout << platforms[0]->getDescription() << std::endl;

    std::cout << results[0]->getResults()[0].first << std::endl;
}