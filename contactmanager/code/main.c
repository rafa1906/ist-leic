/*
* Ficheiro: main.c
* Autor: Rafael Goncalves 92544
* Descricao: Ficheiro principal do sistema de gestao de contactos
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

/* PROGRAMA */
/* main: Inicializa as estruturas de dados (lista ligada e hashtables) e deteta
         qual o comando a processar; aquando da saida do programa (introducao do
         comando 'x'), liberta a memoria ocupada */
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
    } while (c != 'x');

    quit();

    return 0;
}
