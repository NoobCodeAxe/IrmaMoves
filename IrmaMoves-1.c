/*
	Name: William Francois
	ID: U0000001232
*/


#include "IrmaMoves.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int i = 0;
int r = 0;
int c = 0;
char p;

char **createMapBoard(void) {                //create board

	char **board = (char **)malloc(sizeof(char *) * 8);

	for (int i = 0; i < 8; i++)
		board[i] = malloc(sizeof(char ) * 9);

	strncpy(board[0], "FF      ", 8);
	strncpy(board[1], " F      ", 8);
	strncpy(board[2], " FF     ", 8);
	strncpy(board[3], "  F     ", 8);
	strncpy(board[4], "  K     ", 8);
	strncpy(board[5], "C  B    ", 8);
	strncpy(board[6], " CC D   ", 8);
	strncpy(board[7], "  C  DD ", 8);

	if (board != NULL) {
		return board;
	}
	else {
		return NULL;
	}

	
	
}

char **destroyMapBoard(char** board) {          // free board in reverse creation order

	
	for (int i = 0; i < 8; i++) {
		free(board[i]);
	}
		

	free(board);

	return NULL;
}
 
void printMapBoard(char **board) { //output board to console
	printf("\n");
	printf("========");
	for (int i = 0; i < 8; i++)
	{
		printf("\n");
		for (int j = 0; j < 8; j++) {
           printf("%c", board[i][j]);
		}
		
	}
	printf("\n");
		
	printf("========");
	printf("\n");
}


int convert(char p) {           // set the characters equal to proper number
	switch (p) {
	case 'a':
		return 0;
		break;
	case 'b':
		return 1;
		break;
	case 'c':
		return 2;
		break;
	case 'd':
		return 3;
		break;
	case 'e':
		return 4;
		break;
	case 'f':
		return 5;
		break;
	case 'g':
		return 6;
		break;
	case 'h':
		return 7;
		break;
	}

}

void parseNotationString(char* str, Move* irmaMove) {
	char directions[20] = "";
	strcpy(directions, str);              //get directions
	int i = 0;
	char *split = strtok(directions, " ");            
	char *array[4];

	while (split != NULL )                   // split string by token. In this case a  space
	{
		array[i++] = split;
		split = strtok(NULL, " ");
	}


	//access string 
	char *from = array[0];
	int windSpeed=0;
	int windGust = 0;
	sscanf(array[1], "%d", &windSpeed);
	sscanf(array[2], "%d", &windGust);
	char *to = array[3];
	char fromcur = from[1];
	int fromRow =  atoi(&from[1]);
	int currRow = atoi(&from[1]);
	int toRow = atoi(&to[1]);

	//create location
	Location fromLoc;
	fromLoc.col = from[0];
	fromLoc.row = fromRow;
	Location toLoc;
	toLoc.col = to[0];
	toLoc.row = toRow;
	Location currentLoc;
	currentLoc.col = from[0];
	currentLoc.row = currRow;

	//set values in struct
	irmaMove->from_loc = fromLoc;
	irmaMove->to_loc = toLoc;
	irmaMove->current_loc = currentLoc;
	irmaMove->irma.wg = windGust;
	irmaMove->irma.ws = windSpeed;
}

void save(char**board, int row, int col, char part) { // saves the char changed in board so the board can be restored later
	 r = row;
	 c = col;
	 p = part;
	}


startIrma(char **board, Move *irmaMove) {              // set irma at the starting position , also save what was in the initial location
	int row = irmaMove->from_loc.row;
	char col = irmaMove->from_loc.col;
	switch (col) {
	case 'a':
		save(board, row, 0, board[row][0]);
		board[row][0] = 'I';
		break;
	case 'b':
		save(board,  row, 1, board[row][1]);
		board[row][1] = 'I';
		break;
	case 'c':
		save(board,  row, 2, board[row][2]);
		board[row][2] = 'I';
		break;
	case 'd':
		save(board,  row, 3, board[row][3]);
		board[row][3] = 'I';
		break;
	case 'e':
		save(board,  row, 4, board[row][4]);
		board[row][4] = 'I';
		break;
	case 'f':
		save(board,  row, 5, board[row][5]);
		board[row][5] = 'I';
		break;
	case 'g':
		save(board,  row, 6, board[row][6]);
		board[row][6] = 'I';
		break;
	case 'h':
		save(board,  row, 7, board[row][7]);
		board[row][7] = 'I';
		break;
	}
	
}

restore(char** board){           // restores board to initial config by using saved values
	board[r][c] = p;
}

endIrma(char **board, Move *irmaMove) {          //draw irma at end positon and then  save the changed character
	restore(board);
	int row = irmaMove->to_loc.row;
	char col = irmaMove->to_loc.col;
	switch (col) {
	case 'a':
		save(board, row, 0, board[row][0]);
		board[row][0] = 'I';
		break;
	case 'b':
		save(board, row, 1, board[row][1]);
		board[row][1] = 'I';
		break;
	case 'c':
		save(board, row, 2, board[row][2]);
		board[row][2] = 'I';
		break;
	case 'd':
		save(board, row, 3, board[row][3]);
		board[row][3] = 'I';
		break;
	case 'e':
		save(board, row, 4, board[row][4]);
		board[row][4] = 'I';
		break;
	case 'f':
		save(board, row, 5, board[row][5]);
		board[row][5] = 'I';
		break;
	case 'g':
		save(board, row, 6, board[row][6]);
		board[row][6] = 'I';
		break;
	case 'h':
		save(board, row, 7, board[row][7]);
		board[row][7] = 'I';
		break;
	}

}

irmaMath(char**board, Move*irmaMove) {               //calculates the wind speed and gust along irma's path
	restore(board);                                  // restore board so "I" dosent mess up calculations
	int windSpeed = irmaMove->irma.ws;					// retrieve values
	int windGust = irmaMove->irma.wg;

	int fromRow = irmaMove->from_loc.row;
	int fromCol = convert(irmaMove->from_loc.col);
	int toRow = irmaMove->to_loc.row;
	int toCol = convert(irmaMove->to_loc.col);

	//start calculations           horizontal first the vertical
	if (fromCol > toCol) {
		while (fromCol != toCol) {
			fromCol -= 1;
			if (board[fromRow][fromCol] != ' ') {
				windSpeed -= 15;
				windGust -= 10;
			}
			else {
				windSpeed += 10;
				windGust += 5;
			}
		}
	}
	else if (fromCol < toCol) {
		while (fromCol != toCol) {
			fromCol += 1;
			if (board[fromRow][fromCol] != ' ') {
				windSpeed -= 15;
				windGust -= 10;
			}
			else {
				windSpeed += 10;
				windGust += 5;
			}
		}
	}


	if (fromRow > toRow) {
		while(fromRow != toRow) {
			fromRow -= 1;
				if (board[fromRow][fromCol] != ' ') {
					windSpeed -= 2;
					windGust -= 1;
				}
				else {
					windSpeed += 6;
					windGust += 3;
				}
			}
		}
	
	else if (fromRow < toRow) {
		while (fromRow != toRow) {
			fromRow += 1;
			if (board[fromRow][fromCol] != ' ') {
				windSpeed -= 2;
				windGust -= 1;
			}
			else {
				windSpeed += 6;
				windGust += 3;
			}
		}
	}
	
	//store info
	irmaMove->irma.ws= windSpeed;
	irmaMove->irma.wg =windGust;
	
}


char **predictIrmaChange(char* str, Move *irmaMove) {
	char **board = createMapBoard();                 //create board
	//add irma to map board
	parseNotationString(str, irmaMove);             //set values according to instructions user provided
	startIrma(board, irmaMove);                       // place irma at starting position
	printMapBoard(board);                          //display board
	endIrma(board, irmaMove);					// place irma at end position
	printMapBoard(board);                       // draw board
	irmaMath(board, irmaMove);                  // calculate wind speed and wind gust along irmas path
	//print out end of irma
	return board;


}


double difficultyRating(void) {
	return 3.0;
}

double hoursSpent(void) {
	return 5.5;
}