# include <stdio.h>
# include <stdlib.h>
# include <time.h>

//void addBomb(int** board);

void reveal(int** board, int size, int i, int j){
  if(i < 0 || i >size-1 || j<0 || j>size-1){
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
      if(j != 0 && i != size-1){
        reveal(board, size, i+1,j-1);
      }
  }
}



int askSize(){
  int size = -1;
  while(size < 0 || size >50){
    scanf("%d",&size);
  }
}

int isBomb(int** board, int i,int j){
  if(board[i][j] == -10){
    return 1;
  }
  else{
    return 0;
  }
}


void checkBomb(int** board, int size){
  for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
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
      if(j != 0 && i != size-1){
        board[i][j] -= isBomb(board, i+1,j-1);
      }
    }
  }
}

void addBomb(int** board, int size, int bomb) {
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
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
          if(tab[i][j] < 0){
            printf("~ ");
          }
          else if(tab[i][j] == 10){
            printf("* ");
          }
          else{
            printf("%d ", tab[i][j]-1);
          }
        }
      printf("\n");
    }
}

int main(){	
  int choice, size, bomb;
  srand(time(NULL));
  printf("Choisir la taille de la taille du plateau de jeu : \n 1.Normal \n2.Expert \n3.Custom\n");
  scanf("%d", &choice);
  if(choice == 1){
    size = 9;
    bomb =10;
  }
  if(choice == 2){
    size = 16;
    bomb =40;
  }
  if(choice == 3){
    //TODO free choice with bomb capped at 25 %
  }
	int** board = setupBoard(size); //setup of the board
  addBomb(board, size, bomb); //add Bomb to the board
  checkBomb(board, size); //add the numbers of bombs around
  reveal(board, size, 5, 5);
	printBoard(size, board);
	return 0;
}
