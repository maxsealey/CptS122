#include "musicManager.h"

// Runs main menu and executes chosen option
void run_main_menu(void)
{
	int option = 0;

	Node *list = NULL;

	while (option != EXIT)
	{
		option = display_main_menu(); // displays menu and gets choice

		switch (option)
		{
		case LOAD:
			load(&list); 
			break;
		case STORE:
			store(list); 
			break;
		case DISPLAY:
			display(list); 
			break;
		case INSERT:
			printf("Not yet implemented\n"); 
			break;
		case DELETE:
			printf("Not yet implemented\n");
			break;
		case EDIT:
			printf("Note: This function is incomplete.\n");
			system("pause");
			system("cls");
			edit(&list);
			break;
		case SORT:
			printf("Not yet implemented\n");
			break;
		case RATE:
			rate(&list);
			break;
		case PLAY:
			play(&list);
			break;
		case SHUFFLE:
			printf("Not yet implemented\n");
			break;
		case EXIT:
			store(list);
			printf("Goodbye!\n\n");
			break;
		default:
			break;
		}
	}
}

int display_main_menu(void)
{
	int selection = 0;

	do
	{
		printf("Main Menu\n");
		printf("(1) Load\n");
		printf("(2) Store\n");
		printf("(3) Display\n");
		printf("(4) Insert\n");
		printf("(5) Delete\n");
		printf("(6) Edit\n");
		printf("(7) Sort\n");
		printf("(8) Rate\n");
		printf("(9) Play\n");
		printf("(10) Shuffle\n");
		printf("(11) Exit\n");

		scanf("%d", &selection);
		system("cls");
	} while (selection > 11 || selection < 1);

	return selection;
}

Bool load(Node ** pHead)
{
	FILE *infile = fopen("musicPlayList.csv", "r");

	Bool success = FALSE;

	Record newData;
	Node *newNode = NULL;

	char *checkString = NULL;
	char tempStr[MAX_STR_LEN] = { '\0' };

	while (!feof(infile))
	{
		checkString = get_line(tempStr, infile);

		if (checkString != NULL)
		{
			parse_line(tempStr, &newData); // strtok line, assigns to newData
			success = insertFront(pHead, newData);  // makes node, inserts in list
		}
	}

	fclose(infile);
	return success;
}

void store(Node * pHead)
{
	FILE *outfile = NULL;
	Node *pCur = NULL;

	outfile = fopen("musicPlayList.csv", "w");
	pCur = pHead;

	while (pCur != NULL)
	{
		write_to_file(pCur->data, outfile);
		pCur->pPrev = pCur;
		pCur = pCur->pNext;
	}

	fclose(outfile);
}

void display(Node * pHead)
{
	int option = 0;

	Node *pCur = NULL;
	pCur = pHead;

	option = determineDisplayOption();

	switch (option)
	{
	case ALL:
		printList(&pHead);
		system("pause");
		system("cls");
		break;
	case ARTIST:
		searchForArtist(&pHead);
		break;
	default:
		printf("Something went wrong.\n");
		break;
	}
}

void edit(Node ** pHead)
{
	searchForArtist(pHead);
	// Incomplete function
}

void rate(Node ** pHead)
{
	Node *pCur = *pHead;
	int rating = 0;

	while (pCur != NULL)
	{
		printf("What would you like to rate this song?\n");
		print_to_screen(pCur->data);
		scanf("%d", &rating);
		pCur->data.rating = rating;
		pCur = pCur->pNext;
		system("cls");
	}

}

void play(Node ** pHead)
{
	Node *start = determinePlayStart(pHead), *pCur = NULL;
	pCur = start;
	while (pCur != NULL)
	{
		print_to_screen(pCur->data);
		system("pause");
		system("cls");
		pCur = pCur->pNext;
	}
}

Node * determinePlayStart(Node ** pHead)
{
	Node *pCur = *pHead;
	char song[MAX_STR_LEN] = { '\0' };
	Bool found = FALSE;
	int index = 0;

	printf("Enter song name to play first (exactly as recorded): \n");
	fgetc(stdin);
	fgets(song, MAX_STR_LEN, stdin);

	for (index = 0; index < MAX_STR_LEN; index++)
	{
		if (song[index] == '\n')
		{
			song[index] = '\0';
		}
	}

	while (pCur != NULL && found == FALSE)
	{
		if (strcmp(pCur->data.songTitle, song) == 0)
		{
			found = TRUE;
		}
		else
		{
			pCur = pCur->pNext;
		}
	}
	
	return pCur;
}

int determineDisplayOption(void)
{
	int option = 0;

	printf("Would you like to display all records (1), or records by a certain artist (2)?\n");
	scanf("%d", &option);

	return option;
}

void write_to_file(Record data, FILE *outfile)
{
	int index = 0;
	Bool foundComma = FALSE;

	for (index = 0; data.artist[index] != '\0'; index++)
	{
		if (data.artist[index] == ',')
		{
			foundComma = TRUE;
		}
	}

	if (foundComma == TRUE)
	{
		fprintf(outfile, "\"%s\",", data.artist);
	}
	else
	{
		fprintf(outfile, "%s,", data.artist);
	}

	fprintf(outfile, "%s,%s,%s,%d:%d,%d,%d\n", data.album, data.songTitle, data.genre, 
		data.time.min, data.time.sec, data.timesPlayed, data.rating);
}

void print_to_screen(Record data)
{
	printf("Artist: %s\n", data.artist);
	printf("Album: %s\n", data.album);
	printf("Song: %s\n", data.songTitle);
	printf("Genre: %s\n", data.genre);
	printf("Time: %d:%d\n", data.time.min, data.time.sec);
	printf("Times Played: %d\n", data.timesPlayed);
	printf("Rating: %d\n\n", data.rating);
}

char * get_line(char *pStr, FILE * infile)
{
	char *temp;

	temp = fgets(pStr, MAX_STR_LEN, infile);

	return temp;
}

void parse_line(char * pStr, Record * data)
{
	if (pStr[0] == '\"')
	{
		strcpy(data->artist, strtok(pStr + 1, "\""));
	}
	else
	{
		strcpy(data->artist, strtok(pStr, ","));
	}

	strcpy(data->album, strtok(NULL, ","));	 // gets album name
	strcpy(data->songTitle, strtok(NULL, ","));	// gets song title
	strcpy(data->genre, strtok(NULL, ","));	// gets genre

	data->time.min = atoi(strtok(NULL, ":")); // gets # minutes
	data->time.sec = atoi(strtok(NULL, ",")); // gets # seconds
	data->timesPlayed = atoi(strtok(NULL, ",")); // gets # times played
	data->rating = atoi(strtok(NULL, "\n")); // gets rating
}

void searchForArtist(Node ** pHead)
{
	Node *pCur = *pHead;
	char artistName[MAX_STR_LEN] = { '\0' };

	strcpy(artistName, getArtistName());

	while (pCur != NULL)
	{
		if (strcmp(pCur->data.artist, artistName) == 0)
		{
			print_to_screen(pCur->data);
		}

		pCur = pCur->pNext;
	}
	system("pause");
	system("cls");
}

char * getArtistName(void)
{
	char artist[MAX_STR_LEN] = { '\0' };
	int index = 0;
	printf("Which artist would you like to access? (If they have a first and last name, enter '<last name>,<first name>') \n");

	fgetc(stdin);
	fgets(artist, MAX_STR_LEN, stdin);

	for (index = 0; index < MAX_STR_LEN; index++)
	{
		if (artist[index] == '\n')
		{
			artist[index] = '\0';
		}
	}

	return artist;
}

Node * makeNode(Record data)
{
	Node *temp = (Node *)malloc(sizeof(Node));

	if (temp != NULL)
	{
		temp->data = data;
		temp->pNext = NULL;
		temp->pPrev = NULL;
	}

	return temp;
}

Bool insertFront(Node ** pHead, Record newData)
{
	Bool success = FALSE;
	Node *newNode = makeNode(newData);

	if (*pHead == NULL)
	{
		*pHead = newNode;
	}
	else
	{
		newNode->pNext = *pHead;
		(*pHead)->pPrev = newNode;
		*pHead = newNode;

		success = TRUE;
	}

	return success;
}

void printList(Node ** pHead)
{
	Node *pCur = *pHead;

	while (pCur != NULL)
	{
		print_to_screen(pCur->data);

		pCur = pCur->pNext;
	}
}
