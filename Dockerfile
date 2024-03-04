# Usa un'immagine di base
FROM ubuntu:latest

# Installa le dipendenze necessarie
RUN apt-get update && \
    apt-get install -y gcc

# Copia il codice sorgente all'interno dell'immagine
COPY server.c server.h /usr/src/server/
COPY handlers.c handlers.h /usr/src/server/
COPY responses.c responses.h /usr/src/server/

# Compila il codice sorgente
WORKDIR /usr/src/server/
RUN gcc -o server server.c handlers.c responses.c

# Apri le porte necessarie
EXPOSE 5193

# Comando di avvio del server
CMD ["./server"]
