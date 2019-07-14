/*
* Ficheiro: cctable.c
* Autor: Rafael Goncalves 92544
* Descricao: Ficheiro principal da hashtable dos dominios
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dtable.h"

/* PROGRAMA */
/* init_dtable: Inicializa a hashtable dos dominios (aloca espaco para a tabela
                e inicializa todas as suas posicoes a NULL) */
void init_dtable() {
    dtable = (pair *) calloc(DTABLESIZE, sizeof(pair));
}

/* free_dtable: Liberta a memoria que foi usada pela tabela ao longo da execucao
                do programa */
void free_dtable() {
    int i;

    for (i = 0; i < DTABLESIZE; i++) { remove_pairs(dtable[i]); }
    free(dtable);
}

/* hash_domain: Obtem uma hash a partir de uma string que armazena o dominio;
                utiliza a funcao hash djb2 */
int hash_domain(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) { hash = ((hash << 5) + hash) + c; }

    return hash % DTABLESIZE;
}

/* add_occ: Regista uma ocorrencia de um dado dominio */
pair add_occ(char* key) {
    pair current, new_pair;
    int i = hash_domain(key);

    current = dtable[i];

    while (current != NULL) {
        /* Se o dominio ja estiver armazenado, incrementa o contador das
           ocorrencias */
        if (strcmp(current->key, key) == 0) { current->occ++; return current; }

        current = current->next;
    }

    /* Se o dominio nao estiver armazenado, cria um novo par para o armazenar */
    new_pair = (pair) malloc(sizeof(struct pair));

    new_pair->next = dtable[i];

    new_pair->key = (char *) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new_pair->key, key);

    new_pair->occ = 1;

    dtable[i] = new_pair;

    return new_pair;
}

/* remove_pairs: Remove todos os pares numa linha */
void remove_pairs(pair current) {
    while (current != NULL) {
        pair next = current->next;

        free(current->key);
        free(current);

        current = next;
    }
}

/* occ_by_hash: Extrai o numero de ocorrencias dado um certo dominio (0 se o
                dominio nao estiver registado) */
int occ_by_hash(char *domain) {
    pair current;
    int i = hash_domain(domain);

    if(dtable[i] == NULL) { return 0; }

    current = dtable[i];

    while (current != NULL) {
        if (strcmp(current->key, domain) == 0) { return current->occ; }

        current = current->next;
    }

    return 0;
}
