// Copyright [2022] pgallino

#ifndef COMMON_SERVER_H_
#define COMMON_SERVER_H_

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <atomic>
#include "common_socket.h"
#include "server_protocol.h"
#include "common_juego.h"

/* Clase servidor*/

class Server {
    private:
    Protocol_server protocol;
    Juego juego;

    /*imprime estado del juego*/
    void imprimir_estado(const std::vector<uint16_t>& estado);
    public:
    explicit Server(const std::string& servname, const int maxx, const int maxy);

    /*inicia servidor*/
    void start(void);

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;
};

#endif  // COMMON_SERVER_H_
