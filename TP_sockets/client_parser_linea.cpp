// Copyright [2022] pgallino

#include "./client_parser_linea.h"

Parser_comandos::Parser_comandos() {}
void Parser_comandos::serializar_comando(
    const std::string& comando,
    std::vector<int8_t>& comandos) {
    int8_t codigo = INVALIDO;

    if (comando == "Shooting") {
        codigo = SHOOTING;
    } else if (comando == "Moving") {
        codigo = MOVING;
    } else if (comando == "Reload") {
        codigo = RELOAD;
    } else if (comando == "1") {
        codigo = AVANZAR;
    } else if (comando == "-1") {
        codigo = RETROCEDER;
    } else if (comando == "0") {
        codigo = QUIETO;
    } else if (comando == "NOP") {
        codigo = NOP;
    }
    if (codigo != INVALIDO) comandos.push_back(codigo);
}

std::vector<int8_t> Parser_comandos::procesar_linea_comandos(
    const std::string& linea) {
    std::vector<int8_t> comandos;
    std::string comando;
    std::stringstream input_stringstream(linea);
    while (getline(input_stringstream >> std::ws, comando, ' ')) {
        serializar_comando(comando, comandos);
    }
    return comandos;
}
