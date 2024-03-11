#include "server.h"

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

    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = 0;
    server_address.sin_port = htons((u_short)PROTOCOL_PORT);
    memset(&(server_address.sin_zero), '\0', 8);

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
        int client_fd = accept(socket_descriptor, (struct sockaddr *)&client_address, &client_address_len);
        if (client_fd < 0)
        {
            fprintf(stderr, "Errore nella fase di accetazione!\n");
            continue;
        }
        
        // Creazione di un processo figlio
        pid_t pid = fork();
        if (pid < 0)
        {
            // Errore nella creazione del processo figlio
            fprintf(stderr, "Errore nella creazione del processo figlio!\n");
            close(client_fd);
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Processo figlio
            close(socket_descriptor); // Il processo figlio non ha bisogno di ascoltare sulla porta principale
            // Gestisci la richiesta del client
            handle_client(client_fd);
            exit(EXIT_SUCCESS);
        }
        else
        {
            // Processo padre
            close(client_fd); // Il processo padre non ha bisogno del socket del client
        }
    }
    close(socket_descriptor);
    wait(NULL);
    return 0;
}