// Copyright [2022] pgallino

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

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
#define CREATE 0x01
#define JOIN 0x02
#define BROADCAST 0x03
#define READ 0x04

/*CLase Protocolo para la comunicación parte cliente.*/

class Client_protocol {
private:
    const std::string hostname;
    const std::string servname;
    Socket skt;
    void armar_mensaje_largo_x(std::vector<char>& partial,
    const std::string& mensaje,
    const uint8_t& codigo);

public:
    explicit Client_protocol(
    const std::string& hostname,
    const std::string& servname);

    /*envia mensaje*/
    void enviar_mensaje(const uint8_t& codigo, const std::string& mensaje);

    /*recibe mensaje*/
    std::vector<char> recibir_mensaje(const uint8_t& codigo);

    Client_protocol(const Client_protocol&) = delete;
    Client_protocol& operator=(const Client_protocol&) = delete;

    Client_protocol(Client_protocol&&) = default;
    Client_protocol& operator=(Client_protocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
