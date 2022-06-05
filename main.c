#include "game.h"

int main(){
  FILE* file;
  int size, bomb, end, s, m, ms;
  int timer;
  int choice = 0;
  char username[100]={};
  end = 0;
  int i =0;
  int j =0;
  int k =0;
  int doReveal = -1;
  srand(time(NULL));
  printf("Ecriver votre pseudo \n");
  scanf("%s",username);
  emptyBuff();
  printf("Choisir la taille de la taille du plateau de jeu : \n 1.Normal \n2.Expert \n3.Custom\n");
  while(choice < 1 || choice >3){
    scanf("%d", &choice);
    emptyBuff();
  }
  if(choice == 1){
    size = 9;
    bomb =10;
    file = fopen("9.txt","r+");
    if(file == NULL){
      printf("erreur");
      exit(1);
    }
  }
  if(choice == 2){
    size = 16;
    bomb =40;
    file = fopen("16.txt","r+");
    if(file == NULL){
      printf("erreur");
      exit(1);
    }
  }
  if(choice == 3){
    size = askSize();
    bomb = askBomb(size);
  }
	int** board = setupBoard(size); //setup of the board
  addBomb(board, size, bomb); //add Bomb to the board
  checkBomb(board, size); //add the numbers of bombs around
  printBoard(size, board);
  timer = getTimeSec();
  while(end==0){
    printf("1. Révélé une case\n2. Placer/enlever un marqueur \n");
    while(doReveal < 1 || doReveal > 2){
      scanf("%d", &doReveal);
      emptyBuff();
    }
    getCo(&i, &j, size);
    printf("\e[1;1H\e[2J");
    if(doReveal == 1){
      reveal(board, size, j, i);
    }
    else{
      placeFlag(board, size,j, i);
    }
    doReveal = 0;
    printBoard(size, board);
    end = endGame(board, size, bomb);
  }
  if(end == 1){
    printf("Vous avez perdu %s\n", username);
  }
  else{
    timer = getTimeSec() - timer;
    printf("Bravo vous avez gagné %s\n", username);
    printf("Votre temps est de %d m et %d s\n",timer/60, timer%60);
    if(file != NULL && choice == 1){
      sleep(3);
      updateScoreboard(file, timer, username, "9.txt"); 
    }
    else if(file != NULL && choice == 2){
      sleep(3);
      updateScoreboard(file, timer, username, "16.txt"); 
    }
    else if(choice == 3){
      printf("il n'y a pas de scoreboard pour les valeurs custom\n");
    }
  }
	return 0;
}
