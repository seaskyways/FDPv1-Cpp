//
// Created by seaskyways on 9/14/17.
//

#include <iostream>
#include "FDPMessage.cpp"

using namespace fdp;

int main() {
    const auto in = "\34:hello:{\"man\\#\":true}#ack=13#crc=1234566";
    auto message = fdp::FDPMessage::parse(in);

    for (auto &it : message->getOptions()) {
        std::cout << "Opt = " << it.first << " Value = " << it.second << '\n';
    }
}