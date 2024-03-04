#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "../responses.h"
#include "../formatters/libro.h"

#ifndef LIBRERIA_H
#define LIBRERIA_H

// Prototipi delle funzioni

/**
 * Genera una rappresentazione JSON di una libreria con alcuni libri di esempio.
 * La funzione inizializza una struttura Libreria con alcuni libri predefiniti e
 * genera una stringa JSON che rappresenta la lista dei libri con i relativi dettagli.
 * La stringa JSON generata include titolo, autore e ISBN di ciascun libro.
 *
 * @return Puntatore a una stringa allocata dinamicamente contenente la rappresentazione JSON della libreria.
 *         Il chiamante è responsabile di liberare la memoria allocata.
 */
char* get_all();

#endif