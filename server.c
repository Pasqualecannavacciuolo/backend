#include "server.h"

#define PROTOCOL_PORT 5193
#define QUEUE_LEN 6

int socket_descriptor;

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