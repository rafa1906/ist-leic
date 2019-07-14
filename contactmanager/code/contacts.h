/*
* Ficheiro: contacts.h
* Autor: Rafael Goncalves 92544
* Descricao: Header do ficheiro responsavel pelo registo de contactos
*/

#ifndef CONTACT_H
#define CONTACT_H

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include "dtable.h"

/* ESTRUTURAS */
/* contact: Guarda um contacto; e composta por um nome, um email e um numero de
            telefenone (todos strings) e por um ponteiro que aponta para o par
            que regista o dominio (ver dtable) */
typedef struct {
    char *name;
    char *email;
    char *phone;
    pair domain_occ;
} Contact;

/* link: Ponteiro para um no da lista duplamente ligada; e composta por um
         ponteiro para o contacto em questao, e por ponteiros para os nos
         anterior e seguinte */
typedef struct node {
    Contact *contact;
    struct node *prev;
    struct node *next;
} * link;

/* VARIAVEIS */
link head, tail;    /* Ponteiros para a primeira e ultima posicao da lista */

/* PROTOTIPOS */
void init_list();
void free_list();
link push_contact();
void delete_node_values();
void traverse_list();
void delete_from_list(link target);
void change_email_in_list(link target, char *new_email, char *domain);
Contact * create_contact(char *name, char *email, char *phone);
void free_contact(Contact *contact);

#endif
