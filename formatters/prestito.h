#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef PRESTITO_H
#define PRESTITO_H

typedef struct
{
    int id_utente;
    char id_libro[13];
    char data_inizio[10];
    char data_scadenza[10];
} Prestito;

// Array di stringhe per i nomi delle chiavi
extern const char *prestito_keys[];

/**
 * Genera una rappresentazione JSON di un prestito.
 * La funzione prende in input una struttura Prestito e genera una stringa JSON che
 * rappresenta i dettagli del prestito con i relativi campi come id_utente, id_libro(ISBN),data_inizio e data_scadenza del prestito.
 *
 * @param prestito La struttura Prestito da convertire in formato JSON.
 * @return Puntatore a una stringa allocata dinamicamente contenente la rappresentazione JSON del prestito.
 *         Il chiamante è responsabile di liberare la memoria allocata.
 */
char* prestito_to_json(Prestito prestito);

#endif 
