/*
* Ficheiro: cctable.c
* Autor: Rafael Goncalves 92544
* Descricao: Ficheiro principal da hashtable dos contactos
*/


/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctable.h"

/* PROGRAMA */
/* init_ctable: Inicializa a hashtable dos contactos (aloca espaco para a tabela
                e inicializa todas as suas posicoes a NULL) */
void init_ctable() {
    ctable = (entry *) calloc(CTABLESIZE, sizeof(entry));
}

/* free_ctable: Liberta a memoria que foi usada pela tabela ao longo da execucao
                do programa */
void free_ctable() {
    int i;

    for (i = 0; i < CTABLESIZE; i++) { remove_entries(ctable[i]); }
    free(ctable);
}

/* hash_name: Obtem uma hash a partir de uma string que serve de chave; utiliza
              a funcao hash djb2 */
int hash_name(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) { hash = ((hash << 5) + hash) + c; }

    /* Transforma a hash num valor dentro do range da tabela */
    return hash % CTABLESIZE;
}

/* add_entry: Dada uma chave, adiciona o contacto associado a esse nome a tabela
              dos contactos; retorna no final a entrada adicionada ou NULL no
              caso de nao ser possivel adicionar o contacto */
entry add_entry(char* key, Contact *new_contact) {
    entry current, new_entry;
    int i = hash_name(key);         /* Obtem a hash para uma chave */

    current = ctable[i];            /* Viaja para a posicao indicada pela hash */

    /* Percorre as entradas numa dada posicao da tabela, caso encontre uma chave
       semelhante a do input da erro e retorna NULL */
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("Nome existente.\n");
            free_contact(new_contact);

            return NULL;
        }

        current = current->next;
    }

    /* Caso seja possivel, adiciona o contacto a hashtable e a lista ligada,
       retornando no final um ponteiro para a entrada */
    new_entry = (entry) malloc(sizeof(struct entry));

    new_entry->next = ctable[i];

    new_entry->key = (char *) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new_entry->key, key);

    new_entry->target = push_contact(new_contact);

    ctable[i] = new_entry;

    return new_entry;
}

/* remove_entries: Remove todas as entradas numa linha da hashtable */
void remove_entries(entry current) {
    while (current != NULL) {
        entry next = current->next;

        free(current->key);
        free(current);

        current = next;
    }
}

/* search_by_hash: Procura um contacto atraves da hash do nome e imprime a
                   informacao relativa a esse contacto; caso o contacto nao
                   exista da erro */
void search_by_hash(char *name) {
    entry current;
    int i = hash_name(name);

    if(ctable[i] == NULL) { printf("Nome inexistente.\n"); return; }

    current = ctable[i];

    /* Percorre uma linha ate encontrar (ou nao) a chave procurada */
    while (current != NULL) {
        if (strcmp(current->key, name) == 0) {
            link target = current->target;

            printf("%s %s %s\n", target->contact->name,
                                 target->contact->email,
                                 target->contact->phone);

            return;
        }

        current = current->next;
    }

    printf("Nome inexistente.\n");
}

/* delete_by_hash: Apaga um contacto atraves da hash do nome; remove o contacto
                   da hashtable dos contactos e da lista ligada; caso o contacto
                   nao exista da erro */
void delete_by_hash(char *name) {
    entry current, prev;
    int i = hash_name(name);

    current = ctable[i];
    prev = NULL;

    if(ctable[i] == NULL) { printf("Nome inexistente.\n"); return; }

    while (current != NULL) {
        if (strcmp(current->key, name) == 0) {
            /* Ajusta a lista ligada criada pela solucao de encadeamento externo */
            if (prev == NULL) { ctable[i] = current->next; }
            else { prev->next = current->next; }

            /* Apaga o contacto da lista ligada e da hashtable */
            delete_from_list(current->target);
            free(current->key);
            free(current);

            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Nome inexistente.\n");
}

/* change_email_by_hash: Altera o email de um contacto dada a hash do nome; caso
                         o contacto nao exista da erro */
void change_email_by_hash(char *name, char *new_email, char *domain) {
    entry current;
    int i = hash_name(name);

    if(ctable[i] == NULL) { printf("Nome inexistente.\n"); return; }

    current = ctable[i];

    while (current != NULL) {
        if (strcmp(current->key, name) == 0) {
            change_email_in_list(current->target, new_email, domain);

            return;
        }

        current = current->next;
    }

    printf("Nome inexistente.\n");
}
