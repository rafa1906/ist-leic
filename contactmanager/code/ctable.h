/*
* Ficheiro: ctable.h
* Autor: Rafael Goncalves 92544
* Descricao: Header do ficheiro responsavel pela gestao da hashtable dos contactos
*/

#ifndef CTABLE_H
#define CTABLE_H

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"

/* CONSTANTES */
#define CTABLESIZE 5003

/* ESTRUTURAS */
/* entry: Entrada da hashtable dos contactos; e constituida por uma chave, um
          ponteiro para o contacto em questao e um ponteiro para a proxima
          entrada com o mesmo indice */
typedef struct entry {
    char *key;
    link target;
    struct entry *next;
} * entry;

/* VARIAVEIS */
entry *ctable;          /* Ponteiro para a primeira posicao da hashtable */

/* PROTOTIPOS */
void init_ctable();
void free_ctable();
int hash_name(char *key);
entry add_entry(char* key, Contact *new_contact);
void remove_entries(entry current);
void search_by_hash(char *name);
void delete_by_hash(char *name);
void change_email_by_hash(char *name, char *new_email, char *domain);

#endif
