// Copyright [2022] pgallino"

#include <iostream>
#include <string>
#include "./client_cliente.h"

int main(int argc, char *argv[]) { try {
    int ret = 1;
    const char *archivo = NULL;
    const char *hostname = NULL;
    const char *servname = NULL;

    if (argc == 4) {
        hostname = argv[1];
        servname = argv[2];
        archivo = argv[3];
    } else {
        std::cerr <<
                "Bad program call.\n";
        return ret;
    }
    Client cliente(hostname, servname, archivo);
    cliente.start();
    ret = 0;
    return ret;
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

