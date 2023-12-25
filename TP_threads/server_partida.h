// Copyright [2023] pgallino

#ifndef SERVER_PARTIDA_H_
#define SERVER_PARTIDA_H_
#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "./server_queue.h"

class Partida {
    private:
    uint32_t codigo;
    std::vector<char> scenario;
    std::vector<Queue<std::vector<char>>*> jugadores;

    public:
    Partida(uint32_t codigo, const std::vector<char>& scenario);

    /*agrega jugador (cola del cliente)
    a la partida */
    void agregar_jugador(Queue<std::vector<char>>* jugador);

    /*itera las colas pusheando el mensaje
    en cada una */
    void push_broadcast(const std::vector<char>& mensaje);

    void limpiar_jugadores(void);

    Partida(const Partida&) = delete;
    Partida& operator=(const Partida&) = delete;

    Partida(Partida&&) = default;
    Partida& operator=(Partida&&) = default;
};

#endif  // SERVER_PARTIDA_H_
