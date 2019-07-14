/*
* File: main.c
* Author: Rafael Goncalves
* Description: Main file for the contact manager
*/


#include <stdio.h>
#include <stdlib.h>
#include "interface.h"


/* main: Inits the linked list and the hashtables; extracts a command from user
         input */
int main() {
    char c;

    init();

    do {
        scanf("%c", &c);

        switch (c) {
            case 'a':
                add_contact();
                break;

            case 'l':
                list_all();
                break;

            case 'p':
                search_name();
                break;

            case 'r':
                remove_contact();
                break;

            case 'e':
                change_email();
                break;

            case 'c':
                domain_occ();
                break;

            default:
                break;
        }
    } while (c != 'x');         /* Exits if user enters 'x' */

    quit();

    return 0;
}
