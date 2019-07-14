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
    strcpy(event.organizer, read_input(input));

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

    printf("Event %s not found.\n", key);    /* Error message if event does not exist */
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

/* add_part: Adds a new participant */
void add_part() {
    int i, j, ver = 0;
    char key[STRLEN], new_part[STRLEN];
    Event old_event, changed_event;         /* Will store the old and the new event */

    strcpy(key, read_input(input));             /* Extracts description */
    strcpy(new_part, read_input(input));        /* Extracts new participant */

    /* Searches for the event; if found, tries to add the new participant */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */
        if (strcmp(events[i].description, key) == 0) {          /* Tests for a match */

            /* Checks if the participant was already added */
            for (j = 0; j < MAXPART; j++) {
                if (strcmp(events[i].participants[j], new_part) == 0) { return; }
                if (!is_valid_field(events[i].participants[j])) { ver = 1; break; }
            }

            /* Displays an error message if the event is already full */
            if (ver == 0) {
                printf("Impossible to add participant. Event %s is already full.\n", key);

                return;
            }

            old_event = pop_event(i);           /* Extracts original event */
            changed_event = old_event;          /* Creates a copy */

            /* Adds a new participant */
            strcpy(changed_event.participants[j], new_part);

            /* Tries to push the new event; if not possible, pushes the old one */
            if (!push_event(changed_event, 1)) { push_event(old_event, 1); }

            return;
        }
    }

    printf("Event %s not found.\n", key);    /* Error message if event does not exist */
}

/* remove_part: Removes a participant */
void remove_part() {
    int i, j, k;
    char key[STRLEN], del_part[STRLEN];

    strcpy(key, read_input(input));             /* Extracts description */
    strcpy(del_part, read_input(input));        /* Extracts the participant to be removed */

    /* Searches for the event; if found, tries to delete the participant */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */
        if (strcmp(events[i].description, key) == 0) {          /* Tests for a match */
            /* Loops through the participants */
            for (j = 0; j < MAXPART; j++) {

                /* Displays an error message if the participant in question is
                   the only one in the event */
                if (strcmp(events[i].participants[j], del_part) == 0 &&
                    !is_valid_field(events[i].participants[1])) {
                    printf("Impossible to remove participant. Participant \
                            %s is the only participant in event %s.\n",
                            events[i].participants[j], key);

                    return;
                }

                /* If there is a match and the event has more than one participant,
                   the participant is removed */
                if (strcmp(events[i].participants[j], del_part) == 0) {
                    for (k = j; k < MAXPART - 1; k++)
                        strcpy(events[i].participants[k], events[i].participants[k + 1]);

                    strcpy(events[i].participants[2], "NULL");
                }
            }

            return;
        }
    }

    printf("Event %s not found.\n", key);    /* Error message if event does not exist */
}

/* push_event: Tries to push an event to events[] */
bool push_event(Event e, int control) {
    int i = 0;
    Event temp, temp_aux;

    if (catch_errors(e, control)) { return false; }     /* Checks if the event has any errors */

    /* Determines where to put the event (according to time of start) */
    while (is_valid_field(events[i].description)) {
        if (earlier(e, events[i]) || (same_time(e, events[i]) && e.room < events[i].room))
            break;

        i++;
    }

    temp = events[i];       /* Stores current event */
    events[i] = e;          /* Adds new event in place of current event */

    i++;

    /* Right shifts events[] */
    while (is_valid_field(events[i-1].description)) {
        temp_aux = temp;
        temp = events[i];

        events[i] = temp_aux;

        i++;
    }

    return true;
}

/* pop_event: Pops events[pos] */
Event pop_event(int pos) {
    int j;
    Event e = events[pos];      /* Stores the event to pop */

    events[pos] = init_event();     /* Clears events[pos] */

    /* Left shifts events[] */
    for (j = pos + 1; j < MAXEVENTS; j++) {
        if (!is_valid_field(events[j].description)) { break; }

        events[j-1] = events[j];
    }

    events[j-1] = init_event();

    return e;
}

/* change_event: Changes an event attribute */
void change_event(char key[], char new_attribute[], int control) {
    int i;
    Event old_event, changed_event;         /* Will store the old and the new event */

    /* Searches for the event; if found, changes the specified attribute */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */

        /* Tests for a match */
        if (strcmp(events[i].description, key) == 0) {
            old_event = pop_event(i);           /* Extracts original event */
            changed_event = old_event;          /* Creates a copy */

            /* Decides what operation to execute in accordance with the control variable */
            if (control == 0) { changed_event.start = str_to_time(new_attribute); }
            if (control == 1) { changed_event.duration = atoi(new_attribute); }
            if (control == 2) { changed_event.room = atoi(new_attribute); }

            /* Tries to push the new event; if not possible, pushes the old one */
            if (!push_event(changed_event, 0)) { push_event(old_event, 0); }

            return;
        }
    }

    printf("Event %s not found.\n", key);    /* Error message if event does not exist */
}

/* catch_errors: Catches generic errors */
bool catch_errors(Event e, int control) {
    int i, j, k, ver = 0;
    char attendees[MAXPEOPLE][STRLEN];

    /* Stores all attendees (organizer and participants) */
    strcpy(attendees[0], e.organizer);
    strcpy(attendees[1], e.participants[0]);
    strcpy(attendees[2], e.participants[1]);
    strcpy(attendees[3], e.participants[2]);

    /* Searches for conflicts between the event to add and those already in events[]  */
    for (i = 0; i < MAXEVENTS; i++) {
        if (!is_valid_field(events[i].description)) { break; }  /* Breaks if event is not valid */

        /* Checks for time conflicts */
        if (date_to_int(e.date) == date_to_int(events[i].date) &&
            incompatible_times(e, events[i])) {
            if (e.room == events[i].room) {
                printf("Impossible to schedule event %s. Room %d occupied.\n",
                        e.description, e.room);

                return true;
            }

            /* Checks for conflicts regarding attendees */
            for (j = 0; j < MAXPEOPLE; j++) {
                for (k = 0; k < MAXPART; k++) {

                    /* Prints an error message if an attendee already has another
                       event scheduled in the same time frame */
                    if (is_valid_field(attendees[j]) &&
                        (strcmp(attendees[j], events[i].participants[k]) == 0 ||
                         strcmp(attendees[j], events[i].organizer) == 0)) {
                            if (control == 0)     /* If a function changes attributes */
                                printf("Impossible to schedule event %s. Participant \
                                        %s is occupied.\n", e.description, attendees[j]);

                            else      /* If a function adds participants */
                                printf("Impossible to add participant. Participant %s \
                                        is occupied.\n", attendees[j]);

                            ver = 1;
                            break;
                    }
                }
            }
        }
    }

    return ver == 1;
}

/* print_results: Prints formatted event data */
void print_results(Event e) {
    int i;

    /* Prints an event's generic data */
    printf("%s - %08d - %04d - %d - Room %d - %s\n*", e.description, date_to_fint(e.date),
            time_to_int(e.start), e.duration, e.room, e.organizer);

    /* Prints the participants in a new line */
    for (i = 0; i < MAXPART; i++) {
        if (is_valid_field(e.participants[i])) { printf(" %s", e.participants[i]); }
    }

    putchar('\n');
}

/* read_input: Reads input */
char * read_input(char input[]) {
    int i = 0;
    char * in_ptr = input;      /* Pointer to input buffer */

    /* Reads all chars until a ':' or '\n' is found */
    while ((c = getchar()) != ':' && c != '\n') { input[i] = c; i++; }

    input[i] = '\0';

    return in_ptr;
}

/* init_event: Inits an event */
Event init_event() {
    Event e;
    int i;

    /* Sets the description to "NULL" and the date and start time to generic values */
    strcpy(e.description, "NULL");
    e.date = str_to_date("01012019");
    e.start = str_to_time("0000");

    for (i = 0; i < MAXPART; i++)
        strcpy(e.participants[i], "NULL");

    return e;
}

/* is_valid_field: Determines if a field is valid */
bool is_valid_field(char field[]) { return strcmp(field, "NULL") != 0; }

/* earlier: Verifies if e1 occurred earlier than e2 */
bool earlier(Event e1, Event e2) {
    int d1_aux = time_to_int(e1.start) + date_to_int(e1.date) * SHIFTFOUR;
    int d2_aux = time_to_int(e2.start) + date_to_int(e2.date) * SHIFTFOUR;

    return d1_aux < d2_aux;
}

/* same_time: Verifies if e1 occurred at the same time as e2 */
bool same_time(Event e1, Event e2) {
    int d1_aux = time_to_int(e1.start) + date_to_int(e1.date) * SHIFTFOUR;
    int d2_aux = time_to_int(e2.start) + date_to_int(e2.date) * SHIFTFOUR;

    return d1_aux == d2_aux;
}

/* incompatible_times: Verifies if the times in e1 and e2 are incompatible */
bool incompatible_times(Event e1, Event e2) {
    int e1_start = time_to_int(e1.start), e1_finish = time_to_int(get_finish_time(e1));
    int e2_start = time_to_int(e2.start), e2_finish = time_to_int(get_finish_time(e2));

    bool compatible = e1_finish <= e2_start || e1_start >= e2_finish;

    return !compatible;
}

/* str_to_date: Transforms a string in a date */
Date str_to_date(char str[]) {
    int temp = atoi(str);       /* Stores the int value of the date */
    Date date;

    /* Extracts year, month and day */
    date.year = temp % SHIFTFOUR;
    date.month = (temp / SHIFTFOUR) % SHIFTTWO;
    date.day = (temp / SHIFTFOUR) / SHIFTTWO;

    return date;
}

/* date_to_int: Converts a date to an int */
int date_to_int(Date date) { return date.day + date.month * SHIFTTWO + date.year * SHIFTFOUR; }

/* date_to_fint: Converts a date to a formatted int (in accordance with expected output) */
int date_to_fint(Date date) { return date.year + date.month * SHIFTFOUR + date.day * SHIFTSIX; }

/* str_to_time: Transforms a string in a time */
Time str_to_time(char str[]) {
    int temp = atoi(str);
    Time start;

    /* Extracts minutes and hour */
    start.min = temp % SHIFTTWO;
    start.hour = temp / SHIFTTWO;

    return start;
}

/* time_to_int: Converts a time to an int */
int time_to_int(Time start) { return start.min + start.hour * SHIFTTWO; }

/* get_finish_time: Extracts an event's finish time */
Time get_finish_time(Event e) {
    /* Converts a time to minutes */
    int start_min = e.start.min + e.start.hour * MINUTES, temp;

    Time finish;

    temp = start_min + e.duration;      /* Adds the duration in minutes to start_min */

    /* Extracts the finish time */
    finish.min = temp % MINUTES;
    finish.hour = temp / MINUTES;

    return finish;
}
