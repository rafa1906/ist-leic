/*
* Ficheiro: conatcs.c
* Autor: Rafael Goncalves 92544
* Descricao: Ficheiro principal do registo de contactos
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"

/* PROGRAMA */
/* init_list: Inicializa a lista; coloca os ponteiros head e tail a NULL */
void init_list() {
    head = NULL;
    tail = NULL;
}

/* free_list: Liberta o espaco em memoria ocupado pela lista; apaga os nos e os
              contactos */
void free_list() {
    link current = head;

    /* Se a lista for fazia, nao realiza nenhuma acao */
    if (head == NULL) { return; }

    /* Percorre os nos um a um, assim como o registo de contactos, e apaga-os um
       a um */
    while (current != NULL) {
        link next = current->next;

        free_contact(current->contact);
        free(current);

        current = next;
    }

    head = NULL;
}

/* push_contact: Adiciona um contacto ao final da lista; retorna um ponteiro
                 para o novo no */
link push_contact(Contact *contact) {
    link current = tail;
    link new_node = (link) malloc(sizeof(struct node));

    new_node->contact = contact;
    new_node->next = NULL;

    /* Adiciona o contacto; se a lista for vazia, define-o como head */
    if (head == NULL) { new_node->prev = NULL; head = new_node; }
    else { current->next = new_node; new_node->prev = current; }

    tail = new_node;

    return new_node;
}

/* traverse_list: Percorre a lista por ordem e imprime os dados de cada um dos
                  contactos */
void traverse_list() {
    link current = head;

    while (current != NULL) {
        printf("%s %s %s\n", current->contact->name,
                             current->contact->email,
                             current->contact->phone);

        current = current->next;
    }
}

/* delete_from_list: Apaga um no da lista; remove tambem a informacao do contacto */
void delete_from_list(link target) {
    /* Dependendo da posicao do no na lista, ajusta os nos adjacentes para
       acomodar a sua remocao */
    if (target->next == NULL && target->prev == NULL) { head = NULL; tail = NULL; }
    else if (target->prev == NULL) { head = target->next; target->next->prev = NULL; }
    else if (target->next == NULL) { tail = target->prev; target->prev->next = NULL; }
    else { target->prev->next = target->next; target->next->prev = target->prev; }

    /* Decrementa o contador do numero de ocorrencias do dominio do email antigo */
    target->contact->domain_occ->occ--;

    free_contact(target->contact);
    free(target);
}

/* change_email_in_list: Altera o email de um contacto atraves de um no */
void change_email_in_list(link target, char *new_email, char *domain) {
    free(target->contact->email);

    /* Decrementa o contador do numero de ocorrencias do dominio do email antigo */
    target->contact->domain_occ->occ--;

    /* Incrementa o contador do numero de ocorrencias do dominio do email novo */
    target->contact->domain_occ = add_occ(domain);

    target->contact->email = (char *) malloc(sizeof(char) * (strlen(new_email) + 1));
    strcpy(target->contact->email, new_email);
}

/* create_contact: Cria um contacto novo; atribui-lhe o nome, o email, e o
                   numero de telefenone fornecidos */
Contact * create_contact(char *name, char *email, char *phone) {
    Contact *new_contact = (Contact *) malloc(sizeof(Contact));

    new_contact->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new_contact->name, name);

    new_contact->email = (char *) malloc(sizeof(char) * (strlen(email) + 1));
    strcpy(new_contact->email, email);

    new_contact->phone = (char *) malloc(sizeof(char) * (strlen(phone) + 1));
    strcpy(new_contact->phone, phone);

    /* Define temporariamente o ponteiro para o par que guarda o dominio como
       NULL */
    new_contact->domain_occ = NULL;

    return new_contact;
}

/* free_contact: Remove um contacto e as informacoes que ele contem */
void free_contact(Contact *contact) {
    free(contact->name);
    free(contact->email);
    free(contact->phone);

    free(contact);
}
