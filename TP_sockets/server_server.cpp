// Copyright [2022] pgallino

#include "./server_servidor.h"

int main(int argc, char *argv[]) { try {
    int ret = 1;
    const char *servname = NULL;
    int limx = 0;
    int limy = 0;

    if (argc == 4) {
        servname = argv[1];
        limx = atoi(argv[2]);
        limy = atoi(argv[3]);
    } else {
        std::cerr << "Bad program call";
        return ret;
    }

    Server server(servname, limx, limy);
    server.start();
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
