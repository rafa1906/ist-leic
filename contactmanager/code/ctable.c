/*
* File: ctable.c
* Author: Rafael Goncalves
* Description: Main contact hashtable file
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctable.h"


/* init_ctable: Inits the hashtable; sets all entries to NULL */
void init_ctable() {
    ctable = (entry *) calloc(CTABLESIZE, sizeof(entry));
}

/* free_ctable: Frees the memory used by the hashtable */
void free_ctable() {
    int i;

    for (i = 0; i < CTABLESIZE; i++) { remove_entries(ctable[i]); }
    free(ctable);
}

/* hash_name: Hashes a name (which will be used as the key afterwards) using djb2 */
int hash_name(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) { hash = ((hash << 5) + hash) + c; }

    /* Makes sure the hash is within bounds */
    return hash % CTABLESIZE;
}

/* add_entry: Given a key and a contact, tries to add the contact to the hashtable;
              returns the new entry if successful and NULL if not */
entry add_entry(char* key, Contact *new_contact) {
    entry current, new_entry;
    int i = hash_name(key);         /* Gets the hash */

    current = ctable[i];            /* Visits the index corresponding to the hash */

    /* Checks if there is already a contact with the same key; returns NULL if so */
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            printf("Name was already added.\n");
            free_contact(new_contact);

            return NULL;
        }

        current = current->next;
    }

    /* If possible, adds the contact to the hashtable and to the linked list and
       returns the new entry */
    new_entry = (entry) malloc(sizeof(struct entry));

    new_entry->next = ctable[i];

    new_entry->key = (char *) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new_entry->key, key);

    new_entry->target = push_contact(new_contact);

    ctable[i] = new_entry;

    return new_entry;
}

/* remove_entries: Removes all entries at a certain index */
void remove_entries(entry current) {
    while (current != NULL) {
        entry next = current->next;

        free(current->key);
        free(current);

        current = next;
    }
}

/* search_by_hash: Searches a contact by hash and prints its data */
void search_by_hash(char *name) {
    entry current;
    int i = hash_name(name);

    if(ctable[i] == NULL) { printf("Name not found.\n"); return; }

    current = ctable[i];

    /* Checks all entries at the specified index */
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

    printf("Name not found.\n");
}

/* delete_by_hash: Deletes a contact from the hashtable and from the linked list
                   by hash */
void delete_by_hash(char *name) {
    entry current, prev;
    int i = hash_name(name);

    current = ctable[i];
    prev = NULL;

    if(ctable[i] == NULL) { printf("Name not found.\n"); return; }

    while (current != NULL) {
        if (strcmp(current->key, name) == 0) {
            /* Adjusts the list created by the separate chaining solution */
            if (prev == NULL) { ctable[i] = current->next; }
            else { prev->next = current->next; }

            /* Deletes the contact from the data structures */
            delete_from_list(current->target);
            free(current->key);
            free(current);

            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Name not found.\n");
}

/* change_email_by_hash: Changes an email given a certain hash */
void change_email_by_hash(char *name, char *new_email, char *domain) {
    entry current;
    int i = hash_name(name);

    if(ctable[i] == NULL) { printf("Name not found.\n"); return; }

    current = ctable[i];

    while (current != NULL) {
        if (strcmp(current->key, name) == 0) {
            change_email_in_list(current->target, new_email, domain);

            return;
        }

        current = current->next;
    }

    printf("Name not found.\n");
}
