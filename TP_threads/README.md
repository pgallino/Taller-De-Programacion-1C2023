# Trabajo práctico Threads.

Padrón: 107587

Nombre: Pedro Gallino

Estructura del servidor -> Está compuesto por más de un hilo:

Hilo main (principal): Lanza al hilo aceptador y lee de entrada estándar hasta recibir una "q", la cual le indica que debe cerrarse.

Hilo aceptador: Acepta clientes y lanza los hilos recv y send.

Hilo recv: recibe mensajes del cliente.

Hilo send: envía mensajes al cliente.

![image](https://user-images.githubusercontent.com/90009211/236970842-9a8baafe-80d4-46bb-a44f-676dd12830e7.png)

El hilo aceptador recibe clientes y por cada uno crea un objeto de la clase Handler. A cada Handler le pasa por referencia el monitor (clase Juego) y por movimiento el socket. La clase Handler tiene como atributo los hilos recv y send, los cuales se encargan de la comunicación con el cliente.

Los Handlers conectan los hilos recv y send mediante una cola (monitor) donde recv pushea los mensajes a enviar, y send los popea para enviarlos. Crea un objeto de la clase protocolo, pasandole el socket recibido. Los hilos utilizaran por referencia el protocolo para serializar y enviar/recibir mensajes.

![image](https://user-images.githubusercontent.com/90009211/236971388-34552c3f-64ac-41d0-a849-4ca5432bf2b7.png)

Cuando el hilo main recibe la "q" le cierra el socket al hilo aceptador para que no reciba más clientes. Este falla y lanza una excepción que es catcheada. Al catchearla se cierran los sockets de los handlers y se joinean todos los hilos. Luego, el hilo main joinea al hilo aceptador.

![image](https://user-images.githubusercontent.com/90009211/236972395-d7c4aba5-778e-4609-af15-7cfb44ad38ea.png)

El monitor (juego) tiene un map con todas las partidas creadas. Cada partida es un listado de colas (los handlers). Mediante el uso de mutex, "atomiza" los métodos para que no se genere race condition.

-Con el comando CREAR inicia una nueva partida.

-Con el comando JOIN añade un jugador a la partida.

-Con el comando BROADCAST pushea a todas las colas de la partida correspondiente el mensaje.

![image](https://user-images.githubusercontent.com/90009211/236973047-ba8a2abf-64b8-4952-85eb-7eb0edbf1214.png)

Diagrama general del servidor: 

![image](https://user-images.githubusercontent.com/90009211/236973104-7e64f14c-6dc7-43ab-891b-9383ab96d9ba.png)

Estructura del cliente -> monothread

Está compuesto por un solo hilo main (principal) y se comunica con el servidor mediante un protocolo. Lee por entrada estándar los comandos y los envía. Luego recibe las respuestas y las procesa.

![image](https://user-images.githubusercontent.com/90009211/236973317-937bca1a-db99-4391-8044-eae09b46478b.png)



