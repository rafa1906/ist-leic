/*
* Ficheiro: interface.c
* Autor: Rafael Goncalves 92544
* Descricao: Ficheiro principal da interface com o utilizador
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

/* PROGRAMA */
/* init: Aloca memoria para as estruturas de dados utilizadas (lista ligada,
         hashtable dos contactos e hashtable dos dominios) */
void init() {
    init_list();
    init_ctable();
    init_dtable();
}

/* quit: Liberta a memoria alocada aquando durante o uso das estruturas de dados */
void quit() {
    free_list();
    free_ctable();
    free_dtable();
}

/* add_contact: Le um nome, um email e um numero do stdio e regista-o como um
                contacto, guardando as informacoes introduzidas na lista ligada
                e na hashtable dos contactos e a informacao relativa ao dominio
                na hashtable dos dominios */
void add_contact() {
    Contact *new_contact;
    entry new_entry;
    char name[MAXNAME], email[MAXEMAIL], phone[MAXNUMBER], temp[MAXEMAIL];
    char *domain;

    scanf("%s %s %s", name, email, phone);

    strcpy(temp, email);
    strtok(temp, "@");
    domain = strtok(NULL, " ");         /* Extrai o dominio do email */

    /* Tenta adicionar o contacto a hashtable dos contactos e a lista ligada
       (caso o nome nao esteja ja registado) */
    new_contact = create_contact(name, email, phone);
    new_entry = add_entry(new_contact->name, new_contact);

    /* Caso tenha sido possivel adicionar o contacto, regista a ocorrencia do
       dominio */
    if (new_entry != NULL) { new_entry->target->contact->domain_occ = add_occ(domain); }
}

/* list_all: Percorre a lista ligada que guarda as informacoes dos contactos e
             imprime-os por ordem de introducao */
void list_all() {
    traverse_list();
}

/* search_name: Procura um contacto pelo nome e imprime os dados desse contacto */
void search_name() {
    char name[MAXNAME];

    scanf("%s", name);

    search_by_hash(name);
}

/* remove_contact: Remove um contacto pelo nome, eliminando-o das estruturas de
                   dados que o referenciam e atualizando o contador de dominios */
void remove_contact() {
    char name[MAXNAME];

    scanf("%s", name);

    delete_by_hash(name);
}

/* change_email: Altera o email de um contacto dado o seu nome, atualizando o
                 contandor de dominios */
void change_email() {
    char name[MAXNAME], new_email[MAXEMAIL], temp[MAXEMAIL];
    char *domain;

    scanf("%s %s", name, new_email);

    strcpy(temp, new_email);
    strtok(temp, "@");
    domain = strtok(NULL, " ");         /* Extrai o dominio do email */

    change_email_by_hash(name, new_email, domain);
}

/* domain_occ: Procura na hashtable dos dominios o numero de ocorrencias de um
               dado dominio e imprime o valor */
void domain_occ() {
    int occ = 0;
    char domain[MAXEMAIL];

    scanf("%s", domain);

    occ = occ_by_hash(domain);

    printf("%s:%d\n", domain, occ);
}
