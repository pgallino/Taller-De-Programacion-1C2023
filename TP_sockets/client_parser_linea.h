// Copyright [2022] pgallino

#ifndef CLIENT_PARSER_LINEA_H_
#define CLIENT_PARSER_LINEA_H_

#include <vector>
#include <sstream>
#include <string>
#include <cstdint>
#include <iostream>
#define SHOOTING 1
#define MOVING 2
#define RELOAD 3
#define NOP 0
#define COMENTARIO 4
#define RETROCEDER -1
#define AVANZAR 1
#define QUIETO 0
#define INVALIDO 5

/*Clase para procesar los archivos que lee el cliente con comandos*/

class Parser_comandos {
private:
    /*codifica el comando leido*/
    void serializar_comando(const std::string& comando, std::vector<int8_t>& comandos);

public:
    Parser_comandos();
    /*recibe los comandos leidos y los procesa*/
    std::vector<int8_t> procesar_linea_comandos(const std::string& linea);

    Parser_comandos(const Parser_comandos&) = delete;
    Parser_comandos& operator=(const Parser_comandos&) = delete;

    Parser_comandos(Parser_comandos&&) = delete;
    Parser_comandos& operator=(Parser_comandos&&) = delete;
};

#endif  // CLIENT_PARSER_LINEA_H_
