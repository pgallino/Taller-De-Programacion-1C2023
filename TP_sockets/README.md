# Sockets TP1 - TALLER DE PROGRAMACIÓN I

Padrón: 107587

Nombre: Gallino Pedro

El trabajo se centra en la comunicación de un servidor con un cliente y una pequeña lógica de juego.
Para ello utilicé el TDA socket brindado por la cátedra con sus librerias de errores.

Se tiene un Cliente, que interactua con el servidor mediante un socket. El cliente, con Client_protocol puede enviar y recibir mensajes de la forma correcta.
Además se tiene un parser, para leer los archivos con los comandos y poder enviarlos.

Por otro lado, el servidor cuenta con Server_protocol, para enviar y recibir mensajes correctamente.

La lógica del juego está implementada en common_juego, donde el servidor ejecuta los comandos recibidos.


