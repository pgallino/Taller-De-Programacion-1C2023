// Copyright [2023] pgallino

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

class Server_protocol {
private:
    Socket skt;
    void recibir_4_bytes(std::vector<char>& partial, bool* was_closed);
    void recibir_x_longitud(std::vector<char>& partial, bool* was_closed);
public:
    explicit Server_protocol(
    Socket &&aceptado);

    std::vector<char> recibir_mensaje(uint8_t& cod_accion, bool* was_closed);
    void enviar_mensaje(const std::vector<char> &mensaje, bool* was_closed);
    void close_socket(void);

    Server_protocol(const Server_protocol&) = delete;
    Server_protocol& operator=(const Server_protocol&) = delete;

    Server_protocol(Server_protocol&&) = default;
    Server_protocol& operator=(Server_protocol&&) = default;
};

#endif  // SERVER_PROTOCOL_H_
