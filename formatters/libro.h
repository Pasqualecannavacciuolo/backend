#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef LIBRO_H
#define LIBRO_H

typedef struct
{
    char titolo[90];
    char autore[90];
    char isbn[14];
} Libro;

// Array di stringhe per i nomi delle chiavi
extern const char *libro_keys[];

/**
 * Genera una rappresentazione JSON di un libro.
 * La funzione prende in input una struttura Libro e genera una stringa JSON che
 * rappresenta i dettagli del libro con i relativi campi come titolo, autore e ISBN.
 *
 * @param libro La struttura Libro da convertire in formato JSON.
 * @return Puntatore a una stringa allocata dinamicamente contenente la rappresentazione JSON del libro.
 *         Il chiamante è responsabile di liberare la memoria allocata.
 */
char* libro_to_json(Libro libro);

#endif 
