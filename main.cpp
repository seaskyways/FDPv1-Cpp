//
// Created by seaskyways on 9/14/17.
//

#include <iostream>
#include "FDPMessage.cpp"

int main() {
    const auto in = "\1\1\1:hello:{\"man\\#\":true}#ack";
    auto message = fdp::FDPMessage::parse(in);

    std::cout << "Message is " << message;
}