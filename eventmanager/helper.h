/*
* File: helper.h
* Author: Rafael Goncalves
* Description: Header for the event manager
*/


#define STRLEN 64               /* Max string length */
#define MAXPART 3               /* Max number of participants */
#define MAXPEOPLE 4             /* Max number of people in an event */
#define MAXEVENTS 1000          /* Max number of scheduled events */
#define MINUTES 60              /* Minutes in an hour */
#define SHIFTTWO 100            /* Left shift of 2 */
#define SHIFTFOUR 10000         /* Left shift of 4 */
#define SHIFTSIX 1000000        /* Left shift of 6 */


typedef enum { false, true } bool;      /* Boolean */

typedef struct date {       /* Holds a date */
    int day;
    int month;
    int year;
} Date;

typedef struct time {       /* Holds a time */
    int hour;
    int min;
} Time;

typedef struct event {      /* Holds an event */
    char description[STRLEN];     /* Event description */
    Date date;     /* Event date */
    Time start;     /* Event start time */
    int duration;     /* Event duration */
    int room;     /* Event room */
    char organiser[STRLEN];     /* Event organiser */
    char participants[MAXPART][STRLEN];     /* Event participants (up to 3) */
} Event;


void add_event();
void list_all();
void list_room();
void remove_event();
void change_start();
void change_duration();
void change_room();
void add_part();
void remove_part();
bool push_event(Event e, int control);
Event pop_event(int pos);
void change_event(char key[], char new_attribute[], int control);
bool catch_errors(Event e, int control);
void print_results(Event e);
char * read_input();
Event init_event();
bool is_valid_field(char field[]);
bool earlier(Event e1, Event e2);
bool same_time(Event e1, Event e2);
bool incompatible_times(Event e1, Event e2);
Date str_to_date(char * str);
int date_to_int(Date date);
int date_to_fint(Date date);
Time str_to_time(char * str);
int time_to_int(Time time);
Time get_finish_time(Event e);
