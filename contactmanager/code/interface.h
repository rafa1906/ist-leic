/*
* File: interface.h
* Author: Rafael Goncalves
* Description: Header for the UI file
*/


#ifndef INTERFACE_H
#define INTERFACE_H


#include <stdio.h>
#include <stdlib.h>
#include "contacts.h"
#include "ctable.h"
#include "dtable.h"


#define MAXNAME 1024
#define MAXEMAIL 512
#define MAXNUMBER 64


void init();
void quit();
void add_contact();
void list_all();
void search_name();
void remove_contact();
void change_email();
void domain_occ();

#endif
