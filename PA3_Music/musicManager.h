#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STR_LEN 100

#define LOAD 1
#define STORE 2
#define DISPLAY 3
#define INSERT 4
#define DELETE 5
#define EDIT 6
#define SORT 7
#define RATE 8
#define PLAY 9
#define SHUFFLE 10
#define EXIT 11

#define NOT_EMPTY 0
#define EMPTY 1

#define ALL 1
#define ARTIST 2

typedef enum booleanValues
{
	FALSE, TRUE
}Bool;

typedef struct duration
{
	int min;
	int sec;
} Duration;

typedef struct record
{
	char artist[MAX_STR_LEN];
	char album[MAX_STR_LEN];
	char songTitle[MAX_STR_LEN];
	char genre[MAX_STR_LEN];
	Duration time;
	int timesPlayed;
	int rating;
} Record;

typedef struct node
{
	Record data;
	struct node *pNext;
	struct node *pPrev;
} Node;

// Runs main menu and executes chosen option
void run_main_menu(void);

// Displays main menu and returns option
int display_main_menu(void);

// loads data from file
Bool load(Node **pHead);

// Writes list contents to file
void store(Node *pHead);

// Displays record contents
void display(Node *pHead);

// Edits a record
void edit(Node **pHead);

// Goes to each record, asks for edit
void rate(Node **pHead);

// Plays each record
void play(Node **pHead);

// Determines which song to start with when playing
Node *determinePlayStart(Node **pHead);

// Determines whether to display all records, or by artist
int determineDisplayOption(void);

// Writes data to file
void write_to_file(Record data, FILE *outfile);

// prints data to screen
void print_to_screen(Record data);

// Gets line from file, returns it
char * get_line(char *pStr, FILE *infile);

// Parses through line, assignes to Record
void parse_line(char *pStr, Record *data);

// Searches for artist and displays each record
void searchForArtist(Node **pHead);

// gets name of artist from user
char * getArtistName(void);

// LINKED LIST FUNCTIONS

// Creates node	and initializes it
Node *makeNode(Record data);

// Makes node and inserts it in the front of list
Bool insertFront(Node **pHead, Record newData);

// prints items in list
void printList(Node **pHead);

#endif
