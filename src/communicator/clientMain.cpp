//
// Created by jallmenroeder on 04/02/18.
//

#include <iostream>
//#include <ClassificationRequest.h>
#include "Client.h"

int main() {
    Client client = Client(grpc::CreateChannel(
            "localhost:50051", grpc::InsecureChannelCredentials()));

    //ClassificationRequest request = ClassificationRequest()

    std::vector<NetInfo*> nets = client.queryNets();

    std::cout << nets.size() << std::endl;
}