// Copyright [2023] pgallino

#include <string>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <vector>
#include "./server_partida.h"
#include "./server_juego.h"
#define EXITO 0x00
#define FALLO 0x01

Juego::Juego() :
    partidas{},
    codigo(0),
    mutex() {
}

uint32_t Juego::crear_partida(const std::vector<char>& scenario,
    Queue<std::vector<char>>* jugador) {
    std::lock_guard<std::mutex> lock(mutex);
    Partida partida(codigo, scenario);
    partida.agregar_jugador(jugador);
    partidas.emplace(codigo, std::move(partida));
    std::cout << "Created match: " << codigo << "\n";
    return codigo++;
}

uint8_t Juego::unir_partida(uint32_t codigo, Queue<std::vector<char>>* jugador) {
    std::lock_guard<std::mutex> lock(mutex);
    if (partidas.count(codigo)>0) {
        Partida &partida = partidas.at(codigo);
        partida.agregar_jugador(jugador);
        std::cout << "Joined to match: " << codigo << "\n";
        return EXITO;
    }
    std::cout << "Match does not exist: " << codigo << "\n";
    return FALLO;
}

void Juego::broadcast_partida(uint32_t codigo, const std::vector<char>& mensaje) {
    std::lock_guard<std::mutex> lock(mutex);
    Partida &partida = partidas.at(codigo);
    partida.limpiar_jugadores();
    partida.push_broadcast(mensaje);
}


