#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct friend {
    int id;
    int grade;
    struct helped* helpedFriend;
} Friend;

typedef struct helped {
    struct friend* friend;
    struct helped* next;
} Helped;

Friend** friendsByID;

int nFriends = 0, nConnects = 0;

void processInput();
void addHelped(Friend* friend, Friend* helped);
void help(int grade, Friend* helped);
void printFriendsByID();
void freeMemory();

void processInput() {
    int i = 0, helperId = 0, helpedId = 0 , grade = 0;
    Friend* friend;

    scanf("%d,%d", &nFriends, &nConnects);

    friendsByID = (Friend**) calloc(nFriends, sizeof(Friend*));

    for (i = 0; i < nFriends; ++i) {
        scanf("%d",&grade);

        friend = (Friend*) calloc(1, sizeof(struct friend));

        friend->id = i + 1;
        friend->grade = grade;

        friendsByID[i] = friend;
    }

    for (i = 0; i < nConnects; ++i) {
        scanf("%d %d", &helpedId, &helperId);

        addHelped(friendsByID[helperId - 1], friendsByID[helpedId - 1]);
    }
}

void addHelped(Friend* friend, Friend* helped) {
    Helped* temp = friend->helpedFriend;

    Helped* helpedFriend = (Helped*) calloc(1, sizeof(struct helped));

    helpedFriend->friend = helped;
    helpedFriend->next = temp;

    friend->helpedFriend = helpedFriend;

    help(friend->grade, helped);
}

void help(int grade, Friend* helped) {
    Helped* current = helped->helpedFriend;

    if (grade <= helped->grade) return;

    helped->grade = grade;

    while (current != NULL) { help(grade, current->friend); current = current->next; }
}

void printFriendsByID() {
    int i = 0;

    for(i = 0; i < nFriends; ++i) printf("%d\n", friendsByID[i]->grade);
}

void freeMemory() {
    int i = 0;

    for (i = 0; i < nFriends; ++i) {
        Helped* current = friendsByID[i]->helpedFriend;
        Helped* next;

        while (current != NULL) { next = current->next; free(current); current = next; }
        free(friendsByID[i]);
    }

    free(friendsByID);
}

int main() {
    processInput();
    printFriendsByID();
    freeMemory();
    
    return 0;
}
