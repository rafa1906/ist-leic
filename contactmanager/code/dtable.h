/*
* File: dtable.h
* Author: Rafael Goncalves
* Description: Header for the domain hashtable
*/


#ifndef DTABLE_H
#define DTABLE_H


#include <stdio.h>
#include <stdlib.h>


#define DTABLESIZE 503


/* pair: Domain hashtable entry; holds a 'domain/number of occurrences' pair and
         a pointer to the next pair with the same index (collisions are handled
         using separate chaining) */
typedef struct pair {
    char *key;
    int occ;
    struct pair *next;
} * pair;


pair *dtable;           /* Pointer to the first entry */


void init_dtable();
void free_dtable();
int hash_domain(char *key);
pair add_occ(char* key);
void remove_pairs(pair current);
int occ_by_hash(char *domain);

#endif
