// Copyright [2022] pgallino

#ifndef CLIENT_PARSER_LINEA_H_
#define CLIENT_PARSER_LINEA_H_

#include <vector>
#include <sstream>
#include <string>
#include <cstdint>
#include <iostream>
#define CREATE 0x01
#define JOIN 0x02
#define BROADCAST 0x03
#define READ 0x04
#define LEAVE 0x05
#define UN_BYTE 1

/*Clase para procesar los archivos que lee el cliente con comandos*/

class Parser_comandos {
private:
    /*codifica el comando leido*/
    void clasificar_comando(
    const std::string& comando,
    uint8_t& codigo);

public:
    Parser_comandos();
    /*recibe los comandos leidos y los procesa*/
    std::string procesar_linea_comandos(
    const std::string& linea,
    uint8_t& codigo,
    uint32_t& partida);

    Parser_comandos(const Parser_comandos&) = delete;
    Parser_comandos& operator=(const Parser_comandos&) = delete;

    Parser_comandos(Parser_comandos&&) = delete;
    Parser_comandos& operator=(Parser_comandos&&) = delete;
};

#endif  // CLIENT_PARSER_LINEA_H_
