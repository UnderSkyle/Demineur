# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h> 

void updateScoreboard(FILE* file, int timer, char username[], char filename[]);
void emptyBuff();
unsigned long getTimeSec();
void placeFlag(int** board, int size, int i, int j);
void reveal(int** board, int size, int i, int j);
int askSize();
int askBomb(int size);
int isBomb(int** board, int i,int j);
int endGame(int** board, int size, int bomb);
void printTime(unsigned long timer, int* ms, int* s, int*m);
void getCo(int* i, int* j, int size);
void checkBomb(int** board, int size);
void addBomb(int** board, int size, int bomb);
int** setupBoard(int size);
void printBoard(int size, int** tab);