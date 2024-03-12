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
        // Verifica se il numero attuale di processi figli è inferiore al massimo consentito
        if (num_children < MAX_CHILDREN)
        {
            // Accept incoming connection
            if ((client_fd = accept(socket_descriptor, (struct sockaddr *)&client_addr, &client_len)) == -1)
            {
                perror("Accepting connection failed");
                exit(EXIT_FAILURE);
            }


            // Fork a new process to handle the client
            if ((pid = fork()) == -1)
            {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                // Child process
                close(socket_descriptor);
                handle_client(client_fd);
                exit(EXIT_SUCCESS);
            }
            else
            {
                // Parent process
                close(client_fd);
                // Incrementa il numero di processi figli attivi
                num_children++;
            }
        }
        else
        {
            // Attendi che uno dei processi figli termini prima di accettare nuove connessioni
            wait(NULL);
            // Decrementa il numero di processi figli attivi
            num_children--;
        }
    }
    close(socket_descriptor);
    wait(NULL);
    return 0;
}

void handle_int_signal(int signum, int socket_descriptor) {
    // Invia un segnale di terminazione a tutti i processi figli
    for (int i = 0; i < MAX_CHILDREN; i++) {
        printf("\nPid->[%d] - Ricevuto segnale SIGINT. Terminazione del server...\n", getpid());
        kill(children[i], SIGTERM);
    }

    // Attendi che tutti i processi figli terminino
    while (num_children > 0) {
        wait(NULL);
        num_children--;
    }

    // Chiudi il socket e termina il server
    close(socket_descriptor);
    exit(EXIT_SUCCESS);
}