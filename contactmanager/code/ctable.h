/*
* File: ctable.h
* Author: Rafael Goncalves
* Description: Header for the contact hashtable
*/


#ifndef CTABLE_H
#define CTABLE_H


#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"


#define CTABLESIZE 5003


/* entry: Contact hashtable entry; holds a key, a pointer to a contact and a
          pointer to the next entry with the same index (collisions are handled
          using separate chaining) */
typedef struct entry {
    char *key;
    link target;
    struct entry *next;
} * entry;


entry *ctable;          /* Pointer to the first entry */


void init_ctable();
void free_ctable();
int hash_name(char *key);
entry add_entry(char* key, Contact *new_contact);
void remove_entries(entry current);
void search_by_hash(char *name);
void delete_by_hash(char *name);
void change_email_by_hash(char *name, char *new_email, char *domain);

#endif
