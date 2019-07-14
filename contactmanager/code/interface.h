/*
* Ficheiro: interface.h
* Autor: Rafael Goncalves 92544
* Descricao: Header do ficheiro responsavel pela interface com o utilizador
*/

#ifndef INTERFACE_H
#define INTERFACE_H

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"
#include "ctable.h"
#include "dtable.h"

/* CONSTANTES */
#define MAXNAME 1024
#define MAXEMAIL 512
#define MAXNUMBER 64

/* PROTOTIPOS */
void init();
void quit();
void add_contact();
void list_all();
void search_name();
void remove_contact();
void change_email();
void domain_occ();

#endif
