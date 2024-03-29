// Copyright [2022] eldipa
// Código tomado de sockets-en-cpp dispuesto por la cátedra

#ifndef COMMON_SOCKET_H
#define COMMON_SOCKET_H

class Socket {
    private:
    int skt;
    bool closed;

    /*
     * Construye el socket pasándole directamente el file descriptor.
     * */
    explicit Socket(int skt);

    public:
Socket(
        const char *hostname,
        const char *servname);

explicit Socket(const char *servname);

Socket(const Socket&) = delete;
Socket& operator=(const Socket&) = delete;

Socket(Socket&&);
Socket& operator=(Socket&&);

/* `Socket::sendsome` lee hasta `sz` bytes del buffer y los envía. La función
 * puede enviar menos bytes sin embargo.
 *
 * `Socket::recvsome` por el otro lado recibe hasta `sz` bytes y los escribe
 * en el buffer (que debe estar pre-allocado). La función puede recibir
 * menos bytes sin embargo.
 *
 * Si el socket detecto que la conexión fue cerrada, la variable
 * `was_closed` es puesta a `true`, de otro modo sera `false`.
 *
 * Retorna 0 si se cerro el socket,
 * o positivo que indicara cuantos bytes realmente se enviaron/recibieron.
 *
 * Si hay un error se lanza una excepción.
 *
 * Lease manpage de `send` y `recv`
 * */
int sendsome(
        const void *data,
        unsigned int sz,
        bool *was_closed);
int recvsome(
        void *data,
        unsigned int sz,
        bool *was_closed);

/*
 * `Socket::sendall` envía exactamente `sz` bytes leídos del buffer, ni más,
 * ni menos. `Socket::recvall` recibe exactamente sz bytes.
 *
 * Si hay un error se lanza una excepción.
 *
 * Si no hubo un error pero el socket se cerro durante el envio/recibo
 * de los bytes y algunos bytes fueron enviados/recibidos,
 * se lanza también una excepción.
 *
 * Si en cambio ningún byte se pudo enviar/recibir, se retorna 0.
 *
 * En ambos casos, donde el socket se cerró, `was_closed` es puesto a `true`.
 *
 * En caso de éxito se retorna la misma cantidad de bytes pedidos
 * para envio/recibo, lease `sz`.
 *
 * */
int sendall(
        const void *data,
        unsigned int sz,
        bool *was_closed);
int recvall(
        void *data,
        unsigned int sz,
        bool *was_closed);

/*
 * Acepta una conexión entrante y retorna un nuevo socket
 * construido a partir de ella.
 *
 * En caso de error, se lanza una excepción.
 * */
Socket accept();

/*
 * Cierra la conexión ya sea parcial o completamente.
 * Lease manpage de `shutdown`
 * */
void shutdown(int how);

/*
 * Cierra el socket. El cierre no implica un `shutdown`
 * que debe ser llamado explícitamente.
 * */
int close();

/*
 * Destruye el socket. Si aun esta conectado,
 * se llamara a `Socket::shutdown` y `Socket::close`
 * automáticamente.
 * */
~Socket();
};
#endif

