// Copyright [2022] pgallino

#include "./client_parser_linea.h"
#include <netinet/in.h>

Parser_comandos::Parser_comandos() {}

void Parser_comandos::clasificar_comando(
    const std::string& comando,
    uint8_t& codigo) {
    if (comando == "create") {
        codigo = CREATE;
    } else if (comando == "join") {
        codigo = JOIN;
    } else if (comando == "broadcast") {
        codigo = BROADCAST;
    } else if (comando == "read") {
        codigo = READ;
    }
}

std::string Parser_comandos::procesar_linea_comandos(
    const std::string& linea,
    uint8_t& codigo,
    uint32_t& partida) {
    std::string comando;
    std::stringstream input_stringstream(linea);
    input_stringstream >> comando;
    if (comando != "leave") {
        std::string parametro;
        input_stringstream >> parametro;
        if (comando == "join") partida = stoi(parametro);
        clasificar_comando(comando, codigo);
        return parametro;
    } else {
        codigo = LEAVE;
        return "";
    }
}
