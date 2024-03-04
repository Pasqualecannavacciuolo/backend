#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define PROTOCOL_PORT 5193
#define QUEUE_LEN 6

int socket_descriptor;

void handle_int_signal() {
    printf("\nRicevuto segnale SIGINT. Terminazione del server...\n");
    close(socket_descriptor);
    exit(EXIT_SUCCESS);
}

void handle_client(int client_fd) {
    char buffer [1024];
    ssize_t bytes_received;

    // Leggi la richiesta HTTP dal client
    bytes_received = recv(client_fd, buffer, sizeof(buffer), 0);
    if(bytes_received < 0) {
        fprintf(stderr, "Errore nella lettura della richiesta HTTP\n");
        close(client_fd);
        return;
    }

    // Stampa la richiesta HTTP ricevuta dal client
    printf("Richiesta HTTP ricevuta:\n%s", buffer);

    // Invia una risposta HTTP statica al client
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello, World";
    send(client_fd, response, strlen(response), 0);

    // Chiudi la connessione con il client
    close(client_fd);

}

int main()
{
    // Serve per terminare in modo corretto il server premendo CTRL+C
    signal(SIGINT, handle_int_signal);

    // Definisco il socket_descriptor
    socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    if (socket_descriptor < 0)
    {
        fprintf(stderr, "Errore - Impossibile creare il socket!\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = 0;
    server_address.sin_port = htons((u_short)PROTOCOL_PORT);

    // Binding dell'indirizzo locale al socket
    if (bind(socket_descriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        fprintf(stderr, "Binding Fallito!\n");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_descriptor, QUEUE_LEN) < 0)
    {
        fprintf(stderr, "Errore nella fase di ascolto!\n");
        exit(EXIT_FAILURE);
    }

    printf("Server in ascolto sulla porta %d...\n", PROTOCOL_PORT);

    while (1)
    {
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);
        int client_fd = accept(socket_descriptor, (struct sockaddr *)&client_address, &client_address_len);;
        if (client_fd < 0)
        {
            fprintf(stderr, "Errore nella fase di accetazione!\n");
            continue;
        }
        // Gestisci la richiesta del client
        handle_client(client_fd);
    }
    close(socket_descriptor);
    return 0;
}