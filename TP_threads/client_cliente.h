// Copyright [2023] pgallino

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
#include "client_parser_linea.h"
#define CREATE 0x01
#define JOIN 0x02
#define BROADCAST 0x03
#define READ 0x04
#define LEAVE 0x05

/*Clase cliente*/

class Client {
    private:
    Client_protocol protocol;
    Parser_comandos parser;

    /*imprime el estado del juego*/
    void procesar_respuesta(const std::vector<char>& respuesta,
    const uint8_t& codigo,
    const uint32_t& partida);

    void procesar_respuesta_create(const std::vector<char>& respuesta);

    void procesar_respuesta_join(const std::vector<char>& respuesta,
    const uint32_t& partida);

    void procesar_respuesta_broadcast(const std::vector<char>& respuesta);

    public:
    explicit Client(
    const std::string& hostname,
    const std::string& servname);

    /*enciende al cliente, se conecta al servidor
    y comienza a leer el archivo*/
    void start(void);

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    Client(Client&&) = delete;
    Client& operator=(Client&&) = delete;
};

#endif  // COMMON_CLIENT_H_
