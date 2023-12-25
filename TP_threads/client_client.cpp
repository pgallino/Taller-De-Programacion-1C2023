// Copyright [2022] pgallino"

#include <iostream>
#include <string>
#include "./client_cliente.h"

int main(int argc, char *argv[]) { try {
    const char *hostname = NULL;
    const char *servname = NULL;

    if (argc == 3) {
        hostname = argv[1];
        servname = argv[2];
    } else {
        std::cerr <<
                "Bad program call.\n";
        return 1;
    }
    Client cliente(hostname, servname);
    cliente.start();
    return 0;
} catch (const std::exception& err) {
    std::cerr
        << "Something went wrong and an exception was caught: "
        << err.what()
        << "\n";
    return 1;
} catch (...) {
    std::cerr << "Something went wrong and an unknown exception was caught.\n";
    return 1;
} }

