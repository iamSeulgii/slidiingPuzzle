/**
* @file main.c
* @author Seulgi Kim <sgkim5955@gmail.com>
* @date 2017/6/22
* @version 1.0
* @brief The time class represents a moment of time.
*
* @section LICENSE
*
* This program is free software, anybody can redistribute freely.
**/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define MAX 4


unsigned int coord_x = 0;
unsigned int coord_y = 0;
int slidingPuzzle[MAX][MAX];
bool isExisted[16] = { false, };
bool isSelected = false;


/**
* Initailize 4*4 puzzle board using random function.
* There isn't no duplicated number and numbers from 1 to 15.
**/

void initializePuzzle() {

	int randomNum;
	int i, j;
	srand(time(NULL));

	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			do {
				randomNum = rand() % 16;
			} while (isExisted[randomNum]);

			isExisted[randomNum] = true;
			if (randomNum == 0) randomNum = 16;
			slidingPuzzle[i][j] = randomNum;


		}
	}

}


/**
* Check if the puzzle board is completed.
* If numbers are assending ordered, board is completed and return true.
* Unless, board isn't completed and return false, then continue game.
**/

bool checkPuzzle() {
	int i, j;
	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			if (slidingPuzzle[i][j] != (j + 1) + (4 * i)) {
				return false;
			}
		}
	}
	return true;

}


/**
*Print out current puzzle board.
**/

void printPuzzle() {
	int i, j, k;
	int puzzle_content;
	system("clear");


	for (i = 0; i<4; i++) {
		for (j = 0; j<4; j++) {
			puzzle_content = slidingPuzzle[i][j];
			if (puzzle_content == 16)
				printf("#\t");

			else printf("%d\t", puzzle_content);
		}
		printf("\n");
	}
}


/**
*Check which piece of puzzle is next to blank(#).
*And if user inputs puzzle number, change current puzzle board using swap.
**/

void controlPuzzle() {

	char direction;
	int i, j;
	int cnt = 0;
	int k = 0;
	int temp[4] = { 0,0,0,0 };
	int* list;
	int selectedVal;
	bool isListVal = false;
	int temp_x, temp_y;
	int tempVal;

	if (!isSelected) {
		printPuzzle();
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (slidingPuzzle[i][j] == 16) {
					coord_x = i;
					coord_y = j;
				}
			}
		}

		if (coord_x != 0) {
			temp[0] = slidingPuzzle[coord_x - 1][coord_y];
		}
		if (coord_y != 0) {
			temp[1] = slidingPuzzle[coord_x][coord_y - 1];
		}
		if (coord_x != 3) {
			temp[2] = slidingPuzzle[coord_x + 1][coord_y];
		}
		if (coord_y != 3) {
			temp[3] = slidingPuzzle[coord_x][coord_y + 1];
		}

		for (i = 0; i<4; i++) {
			if (temp[i] != 0)cnt++;
		}

		list = (int*)malloc(sizeof(int)*cnt);

		for (j = 0; j<4; j++) {
			if (temp[j] != 0) {
				list[k] = temp[j];
				k++;
			}
		}

		while (!isListVal) {
			printf("Select from ");
			for (i = 0; i<cnt; i++) {
				printf("%d ", list[i]);
				if (i<cnt - 1)    printf(",");
			}
			printf("->  ");
			scanf("%d", &selectedVal);
			for (i = 0; i<cnt; i++) {
				if (list[i] == selectedVal) isListVal = true;
			}
		}
		isSelected = true;
		free(list);
	}


	else {
		for (i = 0; i<4; i++) {
			for (j = 0; j<4; j++) {
				if (slidingPuzzle[i][j] == selectedVal) {
					temp_x = i;
					temp_y = j;
				}
			}
		}
		tempVal = slidingPuzzle[coord_x][coord_y];
		slidingPuzzle[coord_x][coord_y] = slidingPuzzle[temp_x][temp_y];
		slidingPuzzle[temp_x][temp_y] = tempVal;
		isSelected = false;
	}

}

/**
*This is main function of slidingPuzzle
**/

int main() {
	initializePuzzle();
	printPuzzle();
	while (!checkPuzzle())   controlPuzzle();
	printPuzzle();
	printf("Bye!\n");
	return 0;
}

