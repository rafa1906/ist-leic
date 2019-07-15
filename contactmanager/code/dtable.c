/*
* File: dtable.c
* Author: Rafael Goncalves
* Description: Main domain hashtable file
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dtable.h"


/* init_dtable: Inits the domain hashtable; sets all entries to NULL */
void init_dtable() {
    dtable = (pair *) calloc(DTABLESIZE, sizeof(pair));
}

/* free_dtable: Frees the memory used by the hashtable */
void free_dtable() {
    int i;

    for (i = 0; i < DTABLESIZE; i++) { remove_pairs(dtable[i]); }
    free(dtable);
}

/* hash_domain: Hashes a domain (which will be used as the key afterwards) using
                djb2 */
int hash_domain(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) { hash = ((hash << 5) + hash) + c; }

    return hash % DTABLESIZE;
}

/* add_occ: Registers a domain occurrence */
pair add_occ(char* key) {
    pair current, new_pair;
    int i = hash_domain(key);

    current = dtable[i];

    while (current != NULL) {
        /* If the domain was already added, increments the occurrence counter */
        if (strcmp(current->key, key) == 0) { current->occ++; return current; }

        current = current->next;
    }

    /* If the domain isn't found, stores it in a new entry */
    new_pair = (pair) malloc(sizeof(struct pair));

    new_pair->next = dtable[i];

    new_pair->key = (char *) malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(new_pair->key, key);

    new_pair->occ = 1;

    dtable[i] = new_pair;

    return new_pair;
}

/* remove_pairs: Removes all entries at a certain index */
void remove_pairs(pair current) {
    while (current != NULL) {
        pair next = current->next;

        free(current->key);
        free(current);

        current = next;
    }
}

/* occ_by_hash: Extracts the number of occurrences of a given domain (0 if it is
                not found) */
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
