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

void printPuzzle() {
	int i, j, k;
	int puzzle_content;
	system("cls");


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
int main() {
	initializePuzzle();
	printPuzzle();
	while (!checkPuzzle())   controlPuzzle();
	printf("bye!");
	return 0;
}

