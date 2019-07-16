/*
* File: contacts.c
* Author: Rafael Goncalves
* Description: Main contact register file
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacts.h"


/* init_list: Inits the list; sets head and tail to NULL */
void init_list() {
    head = NULL;
    tail = NULL;
}

/* free_list: Frees the memory used by the list; deletes the nodes and their
              respective contacts */
void free_list() {
    link current = head;

    /* If the list is empty, does nothing */
    if (head == NULL) { return; }

    /* Deletes the nodes and their respective contacts one by one */
    while (current != NULL) {
        link next = current->next;

        free_contact(current->contact);
        free(current);

        current = next;
    }

    head = NULL;
}

/* push_contact: Adds a new contact at the end of the list; returns a pointer to
                 the new node */
link push_contact(Contact *contact) {
    link current = tail;
    link new_node = (link) malloc(sizeof(struct node));

    new_node->contact = contact;
    new_node->next = NULL;

    /* Adds a contact; if the list is empty, sets it as head */
    if (head == NULL) { new_node->prev = NULL; head = new_node; }
    else { current->next = new_node; new_node->prev = current; }

    tail = new_node;

    return new_node;
}

/* traverse_list: Traverses the list in order and prints each contact's data */
void traverse_list() {
    link current = head;

    while (current != NULL) {
        printf("%s %s %s\n", current->contact->name,
                             current->contact->email,
                             current->contact->phone);

        current = current->next;
    }
}

/* delete_from_list: Deletes a node from the list and its respective contact data */
void delete_from_list(link target) {
    /* Adjusts the adjacent nodes */
    if (target->next == NULL && target->prev == NULL) { head = NULL; tail = NULL; }
    else if (target->prev == NULL) { head = target->next; target->next->prev = NULL; }
    else if (target->next == NULL) { tail = target->prev; target->prev->next = NULL; }
    else { target->prev->next = target->next; target->next->prev = target->prev; }

    /* Decrements the domain counter */
    target->contact->domain_occ->occ--;

    free_contact(target->contact);
    free(target);
}

/* change_email_in_list: Changes a contact's email */
void change_email_in_list(link target, char *new_email, char *domain) {
    free(target->contact->email);

    /* Decrements the old domain counter */
    target->contact->domain_occ->occ--;

    /* Increments the new domain counter */
    target->contact->domain_occ = add_occ(domain);

    target->contact->email = (char *) malloc(sizeof(char) * (strlen(new_email) + 1));
    strcpy(target->contact->email, new_email);
}

/* create_contact: Creates a new contact with the given name, email and phone */
Contact * create_contact(char *name, char *email, char *phone) {
    Contact *new_contact = (Contact *) malloc(sizeof(Contact));

    new_contact->name = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new_contact->name, name);

    new_contact->email = (char *) malloc(sizeof(char) * (strlen(email) + 1));
    strcpy(new_contact->email, email);

    new_contact->phone = (char *) malloc(sizeof(char) * (strlen(phone) + 1));
    strcpy(new_contact->phone, phone);

    /* Temporarily sets the domain pointer to NULL */
    new_contact->domain_occ = NULL;

    return new_contact;
}

/* free_contact: Removes a contact and the data it holds */
void free_contact(Contact *contact) {
    free(contact->name);
    free(contact->email);
    free(contact->phone);

    free(contact);
}
