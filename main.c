# include <stdio.h>
# include <stdlib.h>
# include <time.h>


void setupBoard(int* board, int bombNmb){
	
	
	
}

void printBoard(int* board, int size){
	for(int i = 0; i<size + 2; i++){
		if(i == 0){
			printf("    ");
			for(int k = 0; k < size ; k++){
				printf(" %c ", 65+k);
			}
			printf("\n");
		}
		else if(i == 1){
			printf("   ");
			for(int k = 0; k < size ; k++){
				printf("---");
			}
			printf("\n");
		}
		else{
			printf("%d", i-1);
			if(i-1 != 10){
				printf(" | ");
			}
			else{
				printf("| ");
			}
			for(int j = 0; j<size; j++){
				printf(" %d ", board[i-2][j]);
			}
			printf("\n");
		}
	}
}

int main(){
	int board* = {};
	
	setupBoard();
	printBoard(board, 10);
	return 0;
}
