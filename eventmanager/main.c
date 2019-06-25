/*
* File: main.c
* Author: Rafael Goncalves
* Description: Main file for the event manager
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"


char c, input[STRLEN];          /* Char reader and input buffer */
Event events[MAXEVENTS];        /* Scheduled events array */


/* main: Inits events[] and extracts a command from user input */
int main() {
    int i;

    for (i = 0; i < MAXEVENTS; i++) { events[i] = init_event(); }   /* Inits events[] */

    while ((c = getchar()) != 'x') {        /* Exits if user enters 'x' */
        getchar();

        switch (c) {
            case 'a':                       /* Adds an event */
                add_event();
                break;

            case 'l':                       /* Lists all events */
                list_all();
                break;

            case 's':                       /* Lists all events in a room */
                list_room();
                break;

            case 'r':                       /* Removes an event */
                remove_event();
                break;

            case 'i':                       /* Changes event start time  */
                change_start();
                break;

            case 't':                       /* Changes event duration */
                change_duration();
                break;

            case 'm':                       /* Changes event room */
                change_room();
                break;

            case 'A':                       /* Adds a participant to an event */
                add_part();
                break;

            case 'R':                       /* Removes a participant from an event */
                remove_part();
                break;

            default:
                break;
        }
    }

    return 0;
}

/* add_event: Adds an event according to user input */
void add_event() {
    int i;
    char buffer[STRLEN];            /* Input buffer */
    Event event = init_event();     /* Inits the event */

    /* Extracts event data */
    strcpy(event.description, read_input(input));
    event.date = str_to_date(strcpy(buffer, read_input(input)));
    event.start = str_to_time(strcpy(buffer, read_input(input)));
    event.duration = atoi(strcpy(buffer, read_input(input)));
    event.room = atoi(strcpy(buffer, read_input(input)));
    strcpy(event.organiser, read_input(input));

    /* Extracts participants */
    for (i = 0; i < MAXPART; i++) {
        strcpy(event.participants[i], read_input(input));

        if (c == '\n') { break; }   /* Breaks if there are no more participants to add */
    }

    push_event(event, 0);           /* Pushes event with control value 0 */
}

/* list_all: Lists all events in stdio by chronological order */
void list_all() {
    int i;

    /* Traverses events[] */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */

        print_results(events[i]);
    }
}

/* list_room: Lists all events in a room in stdio by chronological order */
void list_room() {
    int i, key;

    key = atoi(read_input(input));      /* Extracts the room */

    /* Traverses events[] and compares the rooms with key */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */
        if (events[i].room == key) { print_results(events[i]); }
    }
}

/* remove_event: Removes an event */
void remove_event() {
    int i;
    char key[STRLEN];

    strcpy(key, read_input(input));     /* Extracts description */

    /* Looks for the event; if found, pops it */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */
        if (strcmp(events[i].description, key) == 0) { pop_event(i); return; }
    }

    printf("Event %s not found.\n", key);    /* Error message if event does not exist*/
}

/* change_start: Changes start time */
void change_start() {
    char key[STRLEN], new_start[STRLEN];

    strcpy(key, read_input(input));         /* Extracts description */
    strcpy(new_start, read_input(input));   /* Extracts new start time */

    change_event(key, new_start, 0);        /* Calls change_event with control value 0 */
}

/* change_duration: Changes duration */
void change_duration() {
    char key[STRLEN], new_duration[STRLEN];

    strcpy(key, read_input(input));             /* Extracts description */
    strcpy(new_duration, read_input(input));    /* Extracts new duration */

    change_event(key, new_duration, 1);         /* Calls change_event with control value 1 */
}

/* change_room: Changes room */
void change_room() {
    char key[STRLEN], new_room[STRLEN];

    strcpy(key, read_input(input));             /* Extracts description */
    strcpy(new_room, read_input(input));        /* Extracts new room */

    change_event(key, new_room, 2);             /* Calls change_event with control value 2 */
}

/* add_part: Funcao que adiciona um participante a um evento */
void add_part() {
    int i, j, ver = 0;
    char key[STRLEN], new_part[STRLEN];
    Event old_event, changed_event;         /* Variaveis para guardar o evento original e o alterado */

    strcpy(key, read_input(input));             /* Extrai a descricao do evento requirido */
    strcpy(new_part, read_input(input));        /* Extrai o novo participante */

    /* Loop que procura o evento requirido; caso o encontre, tenta adicionar o participante */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Testa se o evento e valido */
        if (strcmp(events[i].description, key) == 0) {          /* Testa por match */

            /* Loop que percorre os participantes ja adicionados; se houver match com
               algum destes, sai da funcao; se nao, sai do ciclo e ativa o verificador
               ver */
            for (j = 0; j < MAXPART; j++) {
                if (strcmp(events[i].participants[j], new_part) == 0) { return; }
                if (!is_valid_field(events[i].participants[j])) { ver = 1; break; }
            }

            /* Se o evento ja tiver 3 participantes, uma mensagem de erro e apresentada
               e saimos da funcao */
            if (ver == 0) {
                printf("Impossivel adicionar participante. Evento %s ja tem 3 participantes.\n", key);

                return;
            }

            old_event = pop_event(i);           /* Extrai o evento original */
            changed_event = old_event;          /* Cria uma copia do evento para alteracao */

            /* Adiciona um novo participante na posicao j */
            strcpy(changed_event.participants[j], new_part);

            /* Tenta dar push ao evento alterado, se nao for possivel, volta a dar
               push ao antigo */
            if (!push_event(changed_event, 1)) { push_event(old_event, 1); }

            return;
        }
    }

    printf("Evento %s inexistente.\n", key);    /* Mensagem de erro para o caso do evento nao existir */
}

/* remove_part: Funcao que remove um participante a um evento */
void remove_part() {
    int i, j, k;
    char key[STRLEN], del_part[STRLEN];

    strcpy(key, read_input(input));             /* Extrai a descricao do evento requirido */
    strcpy(del_part, read_input(input));        /* Extrai o participante a eliminar */

    /* Loop que procura o evento requirido; caso o encontre, tenta eliminar o participante */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Testa se o evento e valido */
        if (strcmp(events[i].description, key) == 0) {          /* Testa por match */
            for (j = 0; j < MAXPART; j++) {                     /* Percorre os participantes */

                /* Se houver match mas o evento so tiver um participante, retorna uma
                   uma mensagem de erro e sai da funcao */
                    if (strcmp(events[i].participants[j], del_part) == 0 &&
                        !is_valid_field(events[i].participants[1])) {
                    printf("Impossivel remover participante. Participante %s e o unico participante no evento %s.\n",
                            events[i].participants[j], key);

                    return;
                }

                /* Se houver match e o evento tiver mais que um participante, elimina o participante do
                   vetor que contem os participantes e ajusta-o, retrocedendo todos os participantes
                   posteriores */
                if (strcmp(events[i].participants[j], del_part) == 0) {
                    for (k = j; k < MAXPART - 1; k++) {
                        strcpy(events[i].participants[k], events[i].participants[k + 1]);
                    }

                    strcpy(events[i].participants[2], "NULL");
                }
            }

            return;
        }
    }

    printf("Evento %s inexistente.\n", key);    /* Mensagem de erro para o caso do evento nao existir */
}

/* push_event: Funcao que tenta colocar um evento no vetor events[] e que informa se
               se essa operacao e possivel ou nao */
bool push_event(Event e, int control) {
    int i = 0;
    Event temp, temp_aux;           /* Variaveis temporarias para a organizacao do vetor events[] */

    if (catch_errors(e, control)) { return false; }     /* Verifica se o evento possui erros */

    /* Verifica se o evento na posicao i ja foi inicializado e se o evento a adicionar e anterior
       a esse evento; enquanto nao for, incrementa i; quando for, sai do ciclo */
    while (is_valid_field(events[i].description)) {
        if (earlier(e, events[i]) || (same_time(e, events[i]) && e.room < events[i].room)) {
            break;
        }

        i++;
    }

    temp = events[i];       /* Preserva o evento existente na posicao i */
    events[i] = e;          /* Coloca o evento a adicionar na posicao i */

    i++;

    /* Enquanto os eventos forem validos, faz um right shift no vetor events[] */
    while (is_valid_field(events[i-1].description)) {
        temp_aux = temp;
        temp = events[i];

        events[i] = temp_aux;

        i++;
    }

    return true;
}

/* pop_event: Funcao que retira um evento do vetor events[] e devolve esse evento */
Event pop_event(int pos) {
    int j;
    Event e = events[pos];      /* Guarda o evento designado */

    events[pos] = init_event();     /* Elimina o evento do vetor events[] */

    /* Enquanto os eventos forem validos, faz um left shift no vetor events[] */
    for (j = pos + 1; j < MAXEVENTS; j++) {
        if (!is_valid_field(events[j].description)) { break; }

        events[j-1] = events[j];
    }

    events[j-1] = init_event();

    return e;
}

/* change_event: Funcao generica que altera um atributo a um evento */
void change_event(char key[], char new_attribute[], int control) {
    int i;
    Event old_event, changed_event;         /* Variaveis para guardar o evento original e o alterado */

    /* Loop que procura o evento requirido; caso o encontre, tenta alterar o atributo requirido */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Testa se o evento e valido */

        if (strcmp(events[i].description, key) == 0) {      /* Testa por match */
            old_event = pop_event(i);           /* Extrai o evento original */
            changed_event = old_event;          /* Cria uma copia do evento para alteracao */

            /* If's que alteram os atributos indicados pela variavel de controlo */
            if (control == 0) { changed_event.start = str_to_time(new_attribute); }
            if (control == 1) { changed_event.duration = atoi(new_attribute); }
            if (control == 2) { changed_event.room = atoi(new_attribute); }

            /* Tenta dar push ao evento alterado, se nao for possivel, volta a dar
               push ao antigo */
            if (!push_event(changed_event, 0)) { push_event(old_event, 0); }

            return;
        }
    }

    printf("Evento %s inexistente.\n", key);    /* Mensagem de erro para o caso do evento nao existir */
}

/* catch_errors: Funcao responsavel pela detecao de erros genericos */
bool catch_errors(Event e, int control) {
    int i, j, k, ver = 0;
    char atendees[MAXPEOPLE][STRLEN];

    /* Cria um vetor que contem todos os presentes num dado evento */
    strcpy(atendees[0], e.organiser);
    strcpy(atendees[1], e.participants[0]);
    strcpy(atendees[2], e.participants[1]);
    strcpy(atendees[3], e.participants[2]);

    /* Loop que procura incompatibilidades entre o evento a adicionar e os eventos ja agendados */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Testa se o evento e valido */

        /* Caso haja incompatibilidade de horarios para uma dada sala, imprime uma mensagem
           de erro */
        if (date_to_int(e.date) == date_to_int(events[i].date) &&
            incompatible_times(e, events[i])) {
            if (e.room == events[i].room) {
                printf("Impossivel agendar evento %s. Sala%d ocupada.\n", e.description,
                        e.room);

                return true;
            }

            /* Loops que percorrem, respetivamente, os presentes no evento a adicionar e os
               participantes dos eventos ja agendados */
            for (j = 0; j < MAXPEOPLE; j++) {
                for (k = 0; k < MAXPART; k++) {

                    /* Caso os presentes no evento a adicionar entrem em conflito com os
                       participantes nos eventos ja agendados, imprime uma mensagem de erro */
                    if (is_valid_field(atendees[j]) &&
                        (strcmp(atendees[j], events[i].participants[k]) == 0 ||
                         strcmp(atendees[j], events[i].organiser) == 0)) {
                            if (control == 0) {     /* Chamado pelas funcoes que alteram atributos */
                                printf("Impossivel agendar evento %s. Participante %s tem um evento sobreposto.\n",
                                        e.description, atendees[j]);
                            }

                            else {      /* Chamado pela funcao que adiciona participantes */
                                printf("Impossivel adicionar participante. Participante %s tem um evento sobreposto.\n",
                                        atendees[j]);
                            }

                            ver = 1;
                            break;
                    }
                }
            }
        }
    }

    return ver == 1;
}

/* print_results: Funcao que imprime os dados de um evento formatados */
void print_results(Event e) {
    int i;

    /* Imprime os dados genericos com a formatacao indicada */
    printf("%s %08d %04d %d Sala%d %s\n*", e.description, date_to_fint(e.date),
            time_to_int(e.start), e.duration, e.room, e.organiser);

    /* Imprime os participantes numa nova linha */
    for (i = 0; i < MAXPART; i++) {
        if (is_valid_field(e.participants[i])) { printf(" %s", e.participants[i]); }
    }

    putchar('\n');
}

/* read_input: Funcao que le o input de acordo com a formatacao introduzida */
char * read_input(char input[]) {
    int i = 0;
    char * in_ptr = input;      /* Pointer para o buffer do input */

    /* Ciclo while que le todos os caracteres numa string ate encontrar ':' ou '\n' */
    while ((c = getchar()) != ':' && c != '\n') { input[i] = c; i++; }

    input[i] = '\0';

    return in_ptr;
}

/* init_event: Inicializa um evento e retorna-o */
Event init_event() {
    Event e;
    int i;

    /* Coloca a string "NULL" como indicador que o espaco esta disponivel para
       o agendamento de um evento e atribui uma data e hora genericas */
    strcpy(e.description, "NULL");
    e.date = str_to_date("01012019");
    e.start = str_to_time("0000");

    for (i = 0; i < MAXPART; i++) {
        strcpy(e.participants[i], "NULL");
    }

    return e;
}

/* is_valid_field: Determina se um campo e valido ou nao */
bool is_valid_field(char field[]) { return strcmp(field, "NULL") != 0; }

/* earlier: Funcao que verifica se o evento e1 ocorreu antes do evento e2 */
bool earlier(Event e1, Event e2) {
    int d1_aux = time_to_int(e1.start) + date_to_int(e1.date) * SHIFTFOUR;
    int d2_aux = time_to_int(e2.start) + date_to_int(e2.date) * SHIFTFOUR;

    return d1_aux < d2_aux;
}

/* same_time: Funcao que verifica se o evento e1 ocorreu ao mesmo tempo que o evento e2 */
bool same_time(Event e1, Event e2) {
    int d1_aux = time_to_int(e1.start) + date_to_int(e1.date) * SHIFTFOUR;
    int d2_aux = time_to_int(e2.start) + date_to_int(e2.date) * SHIFTFOUR;

    return d1_aux == d2_aux;
}

/* incompatible_times: Funcao que verifica se o horario do evento e1 e incompativel com
                       o horario do evento e2 */
bool incompatible_times(Event e1, Event e2) {
    int e1_start = time_to_int(e1.start), e1_finish = time_to_int(get_finish_time(e1));
    int e2_start = time_to_int(e2.start), e2_finish = time_to_int(get_finish_time(e2));

    /* Sera compativel se o final do evento e1 for anterior ao comeco do evento e2
       ou se o comeco do evento e1 for posterior ao fim do evento e2 */
    bool compatible = e1_finish <= e2_start || e1_start >= e2_finish;

    return !compatible;
}

/* str_to_date: Transforma uma string no tipo data */
Date str_to_date(char str[]) {
    int temp = atoi(str);       /* Armazena temporariamente o valor em int da data */
    Date date;

    /* Extrai o ano, o mes e o dia */
    date.year = temp % SHIFTFOUR;
    date.month = (temp / SHIFTFOUR) % SHIFTTWO;
    date.day = (temp / SHIFTFOUR) / SHIFTTWO;

    return date;
}

/* date_to_int: Converte uma data para int */
int date_to_int(Date date) { return date.day + date.month * SHIFTTWO + date.year * SHIFTFOUR; }

/* date_to_fint: Converte uma data para um int formatado, ou seja, um int que pode ser escrito
                 no standard output */
int date_to_fint(Date date) { return date.year + date.month * SHIFTFOUR + date.day * SHIFTSIX; }

/* str_to_time: Transforma uma string no tipo tempo */
Time str_to_time(char str[]) {
    int temp = atoi(str);
    Time start;

    /* Extrai os minutos e as horas */
    start.min = temp % SHIFTTWO;
    start.hour = temp / SHIFTTWO;

    return start;
}

/* time_to_int: Converte um tempo para int */
int time_to_int(Time start) { return start.min + start.hour * SHIFTTWO; }

/* Calcula a hora a que o evento termina */
Time get_finish_time(Event e) {
    /* Converte o tempo para apenas minutos */
    int start_min = e.start.min + e.start.hour * MINUTES, temp;

    Time finish;

    temp = start_min + e.duration;      /* Adiciona ao tempo em minutos a duracao */

    /* Calcula as horas e os minutos do final do evento */
    finish.min = temp % MINUTES;
    finish.hour = temp / MINUTES;

    return finish;
}
