// Copyright [2023] pgallino

#ifndef SERVER_JUEGO_H_
#define SERVER_JUEGO_H_
#include <string>
#include <cstdint>
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include "./server_partida.h"

/*clase juego que implementa la
logica del juego*/

class Juego {
    private:
    std::map<uint32_t, Partida> partidas;
    uint32_t codigo;
    std::mutex mutex;

    public:
    Juego();

    /*crea una partida asignandole un codigo
    y agrega al jugador que la creo */
    uint32_t crear_partida(const std::vector<char>& scenario, Queue<std::vector<char>>* jugador);

    /*une un jugador a la partida mediante un codigo
    si no hay partida con ese codigo retorna 1
    si hay partida con ese codigo retorna 0*/
    uint8_t unir_partida(const uint32_t codigo, Queue<std::vector<char>>* jugador);

    /*toma el mensaje del broadcast y le indica a la partida
    que se lo envie a todos los jugadores de ella*/
    void broadcast_partida(uint32_t codigo, const std::vector<char>& mensaje);

    Juego(const Juego&) = delete;
    Juego& operator=(const Juego&) = delete;

    Juego(Juego&&) = delete;
    Juego& operator=(Juego&&) = delete;
};

#endif  // SERVER_JUEGO_H_
