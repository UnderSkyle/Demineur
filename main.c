# include <stdio.h>
# include <stdlib.h>
# include <time.h>

//void addBomb(int** board);

/*int askSize(){
  int size = -1;
  while(size < 0 || size >50){
    scanf("%d",&size);
  }
}
*/


void addBomb(int** tab, int size) {
  int count,a,b;
  count=0;
  while (count<11) {
      a=rand()%size;
      b=rand()%size;
      if(tab[a][b] != -9){
        tab[a][b]=-9;
        count=count+1;
      }
    }
}


int** setupBoard(int choice){ //Setop game board with size and bombs
  int size = 10;
  int** board = malloc(size * sizeof(int*));//board creation
  for(int i = 0; i<size; i++){
    board[i] = malloc(size * sizeof(int));
  }
   for(int i = 0; i<size; i++){
     for(int j = 0; j<size; j++){
        board[i][j] = 0;
      }
    }
	addBomb(board, size);
  
	return board;
}



void printBoard(int size, int** tab) {
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
          if(tab[i][j] < 0){
            printf("~ ");
          }
          else{
            printf("%d ", tab[i][j]);
          }
        }
      printf("\n");
    }
}

int main(){	
  srand(time(NULL));
	int** board = setupBoard(1);
	printBoard(10, board);
	return 0;
}
