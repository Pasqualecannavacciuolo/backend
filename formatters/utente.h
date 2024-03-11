#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "prestito.h"

#define MAX_PRESTITI 10

#ifndef UTENTE_H
#define UTETNE_H

typedef struct
{
    int id;
    char nome[13];
    char cognome[10];
    Prestito prestiti[MAX_PRESTITI];
} Utente;

// Array di stringhe per i nomi delle chiavi
extern const char *utente_keys[];

/**
 * Genera una rappresentazione JSON di un utente.
 * La funzione prende in input una struttura Utente e genera una stringa JSON che
 * rappresenta i dettagli dell' utente con i relativi campi come id, nome, cognome e array dei libri presi in prestito.
 *
 * @param utente La struttura Utente da convertire in formato JSON.
 * @return Puntatore a una stringa allocata dinamicamente contenente la rappresentazione JSON del utente.
 *         Il chiamante è responsabile di liberare la memoria allocata.
 */
char* utente_to_json(Utente utente);

#endif 