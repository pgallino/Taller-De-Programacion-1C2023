// Copyright [2023] pgallino

#include "server_aceptador.h"

int main(int argc, char *argv[]) { try {
    const char *servname = NULL;

    if (argc == 2) {
        servname = argv[1];
    } else {
        std::cerr << "Bad program call. Expected "
                << argv[0]
                << " <servname>\n";
        return 1;
    }
    Hilo_aceptador aceptador(servname);
    aceptador.Hilo_aceptador::start(); //se lanza el hilo aceptador
    std::string entrada;
    do {
        getline(std::cin, entrada);
    } while (entrada != "q");
    aceptador.Hilo_aceptador::close(); //cierro el aceptador
    aceptador.join();

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
