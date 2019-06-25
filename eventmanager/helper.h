/*
* Ficheiro: helper.h
* Autor: Rafael Goncalves 92544
* Descricao: Header do organizador de eventos; contem constantes e estruturas
*/


/* CONSTANTES */
#define STRLEN 64               /* Tamanho maximo de string */
#define MAXPART 3               /* Numero maximo de participantes */
#define MAXPEOPLE 4             /* Numero maximo de pessoas presentes */
#define MAXEVENTS 1000          /* Numero maximo de eventos */
#define MINUTES 60              /* Numero de minutos numa hora */
#define SHIFTTWO 100            /* Faz um shift left de 2 */
#define SHIFTFOUR 10000         /* Faz um shift left de 4 */
#define SHIFTSIX 1000000        /* Faz um shift left de 6 */


/* ESTRUTURAS */
/* Tipo booleano */
typedef enum { false, true } bool;

/* Tipo data (dia/mes/ano) */
typedef struct date {
    int day;
    int month;
    int year;
} Date;

/* Tipo tempo (hora/minuto) */
typedef struct time {
    int hour;
    int min;
} Time;

/* Tipo evento */
typedef struct event {
    char description[STRLEN];               /* Guarda a descricao do evento */
    Date date;                              /* Guarda a data do evento */
    Time start;                             /* Guarda a hora de comeco do evento */
    int duration;                           /* Guarda a duracao do evento */
    int room;                               /* Guarda a sala do evento */
    char organiser[STRLEN];                 /* Guarda o organizador do evento */
    char participants[MAXPART][STRLEN];     /* Guarda os participantes do evento */
} Event;
