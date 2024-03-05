#include "libreria.h"

typedef struct
{
    Libro lista_libri[100];
} Libreria;


char *get_all()
{
    Libreria libreria;

    // Inizializzazione della libreria con alcuni libri di esempio
    Libro libro1;
    strcpy(libro1.titolo, "Geronimo Stilton");
    strcpy(libro1.autore, "John Doe");
    strncpy(libro1.isbn, "1234567891236", sizeof(libro1.isbn) - 1);
    libro1.isbn[sizeof(libro1.isbn) - 1] = '\0';
    libreria.lista_libri[0] = libro1;

    Libro libro2;
    strcpy(libro2.titolo, "1984");
    strcpy(libro2.autore, "George Orwell");
    strncpy(libro2.isbn, "9876543219875", sizeof(libro2.isbn) - 1);
    libro2.isbn[sizeof(libro2.isbn) - 1] = '\0';
    libreria.lista_libri[1] = libro2;

    Libro libro3;
    strcpy(libro3.titolo, "La Nebbia");
    strcpy(libro3.autore, "Salvador Dali");
    strncpy(libro3.isbn, "1535644678921", sizeof(libro3.isbn) - 1);
    libro3.isbn[sizeof(libro3.isbn) - 1] = '\0';
    libreria.lista_libri[2] = libro3;

    char jsonString[1024]; // Aumentato per la dimensione dell'array JSON
    //char tempStr[256]; // Aumentato per le stringhe temporanee

    // Inizializzazione della stringa JSON con l'apertura dell'array
    strcpy(jsonString, "{\"lista_libri\": [");

    // Iterazione attraverso i libri e generazione della rappresentazione JSON per ciascun libro
    for (int i = 0; i < 3; i++) { // Supponendo che ci siano solo 3 libri
        // Dopo aver inserito il primo libro devo aggiungere una virgola
        if (i > 0)
            strcat(jsonString, ", "); // Aggiungi virgola tra gli elementi dell'array
        char* libro_json = libro_to_json(libreria.lista_libri[i]);
        /*sprintf(tempStr, "{\"titolo\": \"%s\", \"autore\": \"%s\", \"isbn\": \"%s\"}",
                libreria.lista_libri[i].titolo, libreria.lista_libri[i].autore, libreria.lista_libri[i].isbn);*/
        strcat(jsonString, libro_json);
    }

    // Chiusura dell'array JSON e della stringa JSON
    strcat(jsonString, "]}");

    // Allocazione di memoria per la stringa JSON e copia del contenuto
    char *jsonResult = strdup(jsonString);
    return jsonResult;
}
