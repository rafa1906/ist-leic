/*
* Ficheiro: ctable.h
* Autor: Rafael Goncalves 92544
* Descricao: Header do ficheiro responsavel pela gestao da hashtable dos dominios
*/

#ifndef DTABLE_H
#define DTABLE_H

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>

/* CONSTANTES */
#define DTABLESIZE 503

/* ESTRUTURAS */
/* pair: Entrada da tabela de dominios; e constituida por um par chave/ocorrencias,
         em que ocorrencias indica o numero de ocorrencias do dominio em questao,
         e por um ponteiro para o proximo par na mesma linha */
typedef struct pair {
    char *key;
    int occ;
    struct pair *next;
} * pair;

/* VARIAVEIS */
pair *dtable;           /* Ponteiro para a primeira posicao da tabela */

/* PROTOTIPOS */
void init_dtable();
void free_dtable();
int hash_domain(char *key);
pair add_occ(char* key);
void remove_pairs(pair current);
int occ_by_hash(char *domain);

#endif
