/*
* File: interface.c
* Author: Rafael Goncalves
* Descricao: Main UI file
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"


/* init: Allocates memory for the data structures */
void init() {
    init_list();
    init_ctable();
    init_dtable();
}

/* quit: Frees the memory used by the data structures */
void quit() {
    free_list();
    free_ctable();
    free_dtable();
}

/* add_contact: Reads a name, an email and a phone number from stdio; stores the
                contact info in the contact list and hashtable and the domain
                info in the domain hashtable */
void add_contact() {
    Contact *new_contact;
    entry new_entry;
    char name[MAXNAME], email[MAXEMAIL], phone[MAXNUMBER], temp[MAXEMAIL];
    char *domain;

    scanf("%s %s %s", name, email, phone);

    strcpy(temp, email);
    strtok(temp, "@");
    domain = strtok(NULL, " ");         /* Extracts email domain */

    /* Tries to add the contact */
    new_contact = create_contact(name, email, phone);
    new_entry = add_entry(new_contact->name, new_contact);

    /* If the contact was added sucessfully, updates the domain hashtable */
    if (new_entry != NULL) { new_entry->target->contact->domain_occ = add_occ(domain); }
}

/* list_all: Traverses the contact list and prints contact info */
void list_all() {
    traverse_list();
}

/* search_name: Searches a contact by name and prints its info */
void search_name() {
    char name[MAXNAME];

    scanf("%s", name);

    search_by_hash(name);
}

/* remove_contact: Removes a contact; adjusts the domain hashtable in the process */
void remove_contact() {
    char name[MAXNAME];

    scanf("%s", name);

    delete_by_hash(name);
}

/* change_email: Changes an email; adjusts the domain hashtable in the process */
void change_email() {
    char name[MAXNAME], new_email[MAXEMAIL], temp[MAXEMAIL];
    char *domain;

    scanf("%s %s", name, new_email);

    strcpy(temp, new_email);
    strtok(temp, "@");
    domain = strtok(NULL, " ");         /* Extracts email domain */

    change_email_by_hash(name, new_email, domain);
}

/* domain_occ: Searches for the number of occurrences of a given domain and
               presents it in stdio */
void domain_occ() {
    int occ = 0;
    char domain[MAXEMAIL];

    scanf("%s", domain);

    occ = occ_by_hash(domain);

    printf("%s:%d\n", domain, occ);
}
