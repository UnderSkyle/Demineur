#include "game.h"


void updateScoreboard(FILE* file, int timer, char username[], char filename[]){
  FILE * filetemp = fopen("temp.txt", "w+");
  char currentUser[200];
  int already = 0;
  int currentValue = 0;
  for(int i=0; i<5; i++){
    fscanf(file, "%s", currentUser);
    fscanf(file, "%d", &currentValue);
    if(currentValue > timer && already == 0){
      fprintf(filetemp,"%s\n%d\n", username,timer);
      printf("%s %d minutes %d secondes",currentUser,currentValue/60, currentValue%60);
      already = 1;
    }
    else{
      fprintf(filetemp,"%s\n%d\n",currentUser,currentValue);
      printf("%s %d minutes %d secondes",currentUser,currentValue/60, currentValue%60);
    }
  }

  fclose(file);
  remove(filename);
  rename("temp.txt", filename);
}

void emptyBuff(){ // empty the buffer for scanf
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

unsigned long getTimeSec(){ //get the current time for the timer
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return tv.tv_sec;
}

void placeFlag(int** board, int size, int i, int j){ // used to place flags on the board and remove them
  if(i < 0 || i >size-1 || j<0 || j>size-1){
  }
  else if(board[i][j] < -100){
    board[i][j] = board[i][j]+100;
  }
  else if(board[i][j] < 0){
    board[i][j] = board[i][j]-100;
  }
}

void reveal(int** board, int size, int i, int j){ // reveal a space with recursion
  if(i < 0 || i >size-1 || j<0 || j>size-1 || board[i][j] < -100){
  }
  else if(board[i][j] > 0){
  }
  else if(board[i][j] != -1){
    board[i][j] = board[i][j]*(-1);
  }
  else if(board[i][j] == -1){
    board[i][j] = board[i][j]*(-1);
    if(i != 0){ //UP
        reveal(board, size, i-1,j);
      }
      if(i != size-1){ //DOWN
        reveal(board, size, i+1,j); 
      }
      if(j != 0){ //LEFT
        reveal(board, size, i,j-1);
        
      }
      if(j != size-1){//Right
       reveal(board, size, i,j+1);
      }
      if(j != size-1 && i != 0){ //RIGHT UP
        reveal(board, size, i-1,j+1);
      }
      if(j != size-1 && i != size-1){//RIGHT DOWN
        reveal(board, size, i+1,j+1);
      }
      if(j != 0 && i != 0){//LEFT UP
       reveal(board, size, i-1,j-1);
      }
      if(j != 0 && i != size-1){// LEFT DOWN
        reveal(board, size, i+1,j-1);
      }
  }
}

int askSize(){ //ask a board size
  int size = -1;
  printf("choisissez une taille entre 3 et 50\n");
  while(size < 3 || size >50){
    scanf("%d",&size);
    emptyBuff();
  }
  return size;
}

int askBomb(int size){ //ask the nomber of bombs (capped 25%)
  int bomb = -1;
  printf("choisissez une taille entre 1 et %d\n", (size*size)/4);
  while(bomb < 1 || bomb >(size*size)/4){
    scanf("%d",&bomb);
    emptyBuff();
  }
  return bomb;
}

int isBomb(int** board, int i,int j){ //Is the space a bomb
  if(board[i][j] == -10){
    return 1;
  }
  else{
    return 0;
  }
}

int endGame(int** board, int size){ //deal with the end of the game
  int end = 0;
  int test = 0;
  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
      if(board[i][j] == 10){//if BOMB end
        end = 1;
      }
      if(board[i][j] < 0 && board[i][j] != -10 && board[i][j] != -110){ //If board all revealed eccept bombe and flaged bombe
        test++;
      }
    }
  }
  if(test == 0){
    end = 2;
  }
  return end;
}

void printTime(unsigned long timer, int* ms, int* s, int*m){
   printf("%ld \n", timer);
   *ms = timer%1000;
   *s = timer/1000;
   *m = *s/60;
   *s = *s%60;
  printf("Vous avez fini la partie en %d m  %d s  %d ms",*m ,*s ,*ms);
}

void getCo(int* i, int* j, int size){ //get a the co with letters and numbers
  char k;
  int l;
  printf("Ecrire le coordonées Ex: A 5 \n");
  do{
  scanf("%c", &k);
  scanf("%d", &l);
  emptyBuff();
  }while(k<'A' || k > 'A'+size || l<1 || l>size);
  *i = (int)k-'A';
  *j = l-1;
}

void checkBomb(int** board, int size){ //used to set the board to correct value 
  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
      if(board[i][j] != -10){
        if(i != 0){ //UP
          board[i][j] -= isBomb(board, i-1,j);
        }
        if(i != size-1){ //DOWN
          board[i][j] -= isBomb(board, i+1,j); 
        }
        if(j != 0){ //LEFT
          board[i][j] -= isBomb(board, i,j-1);
        }
        if(j != size-1){//Right
          board[i][j] -= isBomb(board, i,j+1);
        }
        if(j != size-1 && i != 0){ //RIGHT UP
          board[i][j] -= isBomb(board, i-1,j+1);
        }
        if(j != size-1 && i != size-1){//RIGHT DOWN
          board[i][j] -= isBomb(board, i+1,j+1);
        }
        if(j != 0 && i != 0){//LEFT UP
          board[i][j] -= isBomb(board, i-1,j-1);
        }
        if(j != 0 && i != size-1){//RIGHT UP
          board[i][j] -= isBomb(board, i+1,j-1);
        }
      }
    }
  }
}

void addBomb(int** board, int size, int bomb) {//add the good number of bomb in the board
  int count,a,b;
  count=0;
  while (count<bomb) {
      a=rand()%size;
      b=rand()%size;
      if(board[a][b] != -10){
        board[a][b]=-10;
        count=count+1;
      }
    }
}

int** setupBoard(int size){ //Setop game board with size and bombs
  int** board = malloc(size * sizeof(int*));//board creation
  for(int i = 0; i<size; i++){
    board[i] = malloc(size * sizeof(int));
  }
   for(int i = 0; i<size; i++){
     for(int j = 0; j<size; j++){
        board[i][j] = -1;
      }
    }  
	return board;
}

void printBoard(int size, int** tab) {
    char up = 'A';
    int column = 1;
    printf("   ");
    for(int k = 0; k<size; k++){ // print the char for the x coordinate
      printf("%c ", up);
      up++;
    }
    printf("\n");
    for(int i=0;i<size;i++) { 
        printf("%d ",column); // handle the y coordinate
        if(column < 10){
          printf(" ");
        }
        column++;
        for(int j=0;j<size;j++) {
          if(tab[i][j] < -100){ // drapeau
            printf("+ ");
            }
          else if(tab[i][j] < 0){ //Si tab< 0 alors cache
            printf("~ ");
          }
          else if(tab[i][j] == 10){ // bomb
            printf("* ");
          }
          else{
            printf("%d ", tab[i][j]-1);
          }
        }
      printf("\n");
    }
}
