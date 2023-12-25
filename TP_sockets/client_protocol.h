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

/*CLase Protocolo para la comunicación parte cliente.*/

class Client_protocol {
private:
    const std::string hostname;
    const std::string servname;
    Socket skt;

public:
    explicit Client_protocol(
    const std::string& hostname,
    const std::string& servname);

    /*envia mensaje*/
    void enviar_mensaje(std::vector<int8_t>& mensaje);

    /*recibe mensaje*/
    std::vector<uint16_t> recibir_mensaje();

    Client_protocol(const Client_protocol&) = delete;
    Client_protocol& operator=(const Client_protocol&) = delete;

    Client_protocol(Client_protocol&&) = default;
    Client_protocol& operator=(Client_protocol&&) = default;
};

#endif  // CLIENT_PROTOCOL_H_
