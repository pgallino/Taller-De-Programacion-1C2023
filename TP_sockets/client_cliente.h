// Copyright [2022] pgallino

#ifndef COMMON_CLIENT_H_
#define COMMON_CLIENT_H_
#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "client_protocol.h"
#include "./client_parser_linea.h"
#define IDLE 0
#define SHOOTING 1
#define MOVING 2
#define SHO_MOV 3

/*Clase cliente*/

class Client {
    private:
    Client_protocol protocol;
    Parser_comandos parser;
    const std::string nombre_archivo;

    /*imprime el estado del juego*/
    void procesar_respuesta(
    const std::vector<uint16_t>& respuesta);

    public:
    explicit Client(
    const std::string& hostname,
    const std::string& servname,
    const std::string& nombre_archivo);

    /*enciende al cliente, se conecta al servidor
    y comienza a leer el archivo*/
    void start(void);

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;
};

#endif  // COMMON_CLIENT_H_
