// Copyright [2022] pgallino

#ifndef SERVER_PROTOCOL_H_
#define SERVER_PROTOCOL_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>

#include "./common_socket.h"

#define RELOAD 3
#define SHOOTING 1
#define NOP 0

/*CLase Protocolo para la comunicación parte servidor.*/

class Protocol_server {
private:
    const std::string servname;
    Socket skt;
    Socket peer;
public:
    explicit Protocol_server(
    const std::string& servname);

    /*recibe mensaje*/
    std::vector<int8_t> recibir_mensaje(bool *was_closed);

    /*envia mensaje*/
    void enviar_mensaje(std::vector<uint16_t>& mensaje);

    Protocol_server(const Protocol_server&) = delete;
    Protocol_server& operator=(const Protocol_server&) = delete;

    Protocol_server(Protocol_server&&) = default;
    Protocol_server& operator=(Protocol_server&&) = default;
};

#endif  // SERVER_PROTOCOL_H_
