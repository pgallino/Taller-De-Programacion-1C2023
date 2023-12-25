// Copyright [2023] pgallino

#include "./client_cliente.h"

Client::Client(
        const std::string& hostname,
        const std::string& servname) :
    protocol(hostname, servname),
    parser() {
}

void Client::start(void) {
    std::string comando;
    uint8_t codigo;
    uint32_t partida;
    std::string linea;
    while (getline(std::cin, linea)) {
        comando = parser.procesar_linea_comandos(linea, codigo, partida);
        if (codigo == LEAVE) break;
        if (comando.size() == 0) continue;
        std::vector<char> respuesta;
        if (codigo == READ) {
            for (int i = 0; i < (stoi(comando)); i++) {
                respuesta = protocol.recibir_mensaje(codigo);
                procesar_respuesta(respuesta, codigo, partida);
            }
        } else if (codigo == CREATE || codigo == JOIN) {
            protocol.enviar_mensaje(codigo, comando);
            respuesta = protocol.recibir_mensaje(codigo);
            procesar_respuesta(respuesta, codigo, partida);
        } else {
            protocol.enviar_mensaje(codigo, comando);
        }
    }
}

void Client::procesar_respuesta(const std::vector<char>& respuesta,
    const uint8_t& codigo,
    const uint32_t& partida) {
    if (codigo == CREATE) procesar_respuesta_create(respuesta);
    if (codigo == JOIN) procesar_respuesta_join(respuesta, partida);
    if (codigo == READ) procesar_respuesta_broadcast(respuesta);
}

void Client::procesar_respuesta_create(const std::vector<char>& respuesta) {
    uint32_t codigo = *(uint32_t*) respuesta.data();
    std::cout << "Created match: " << codigo << "\n";
}
void Client::procesar_respuesta_join(const std::vector<char>& respuesta,
    const uint32_t& partida) {
    uint8_t codigo = *(uint8_t*) respuesta.data();
    if (codigo == 0) std::cout << "Joined to match: " << partida << "\n";
    if (codigo == 1) std::cout << "Match does not exist: " << partida << "\n";
}
void Client::procesar_respuesta_broadcast(const std::vector<char>& respuesta) {
    std::string s(respuesta.begin(), respuesta.end());
    std::cout << "Broadcasted: " << s << "\n";
}
