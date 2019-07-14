/*
* File: contacts.h
* Author: Rafael Goncalves
* Description: Header for the contact register
*/


#ifndef CONTACT_H
#define CONTACT_H


#include <stdio.h>
#include <stdlib.h>
#include "dtable.h"


/* contact: Stores a contact; holds a name, an email, a phone (all strings) and
            a pointer to the respective domain in the domain hashtable */
typedef struct {
    char *name;
    char *email;
    char *phone;
    pair domain_occ;
} Contact;

/* link: Pointer to a node in the doubly linked list that stores the contacts */
typedef struct node {
    Contact *contact;
    struct node *prev;
    struct node *next;
} * link;


link head, tail;    /* First and last elements in the list, respectively */


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
