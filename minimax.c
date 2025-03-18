#include <stdio.h>
#define MIN -999
#define MAX 999
#define HUMAN 'X'
#define COMPUTER 'O'
char board[3][3];

void initializeBoard() {    
	for (int i = 0; i < 3; i++) {        
		for (int j = 0; j < 3; j++) {            
			board[i][j] = ' ';        
			}    
		}
	}

void printBoard() {    
	printf("\n");    
	for (int i = 0; i < 3; i++) {        
		for (int j = 0; j < 3; j++) {            
			printf(" %c ", board[i][j]);            
			if (j < 2) printf("|");        
			}        
		printf("\n");        
		if (i < 2)  printf("-----------\n");    
		}    
	printf("\n");
	}

int evaluate() {    
	for (int row = 0; row < 3; row++) {    
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) { 
			if (board[row][0] == HUMAN) return 10;
			else if (board[row][0] == COMPUTER) return -10;        
			}    
		}        
	for (int col = 0; col < 3; col++) {
		if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
			if (board[0][col] == HUMAN) return 10;
			else if (board[0][col] == COMPUTER) return -10;        
			}    
		}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {    
		if (board[0][0] == HUMAN) return 10;        
		else if (board[0][0] == COMPUTER) return -10;    
		}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {    
		if (board[0][2] == HUMAN) return 10;
		else if (board[0][2] == COMPUTER) return -10;
		}
return 0;
}


int isMovesLeft() {    
	for (int i = 0; i < 3; i++)        
	       for (int j = 0; j < 3; j++)            
			if (board[i][j] == ' ') return 1;    
	return 0;
	}

int minimax(int depth, int isMax) {    
        int score = evaluate();    
        if (score == 10) return score; 
        if (score == -10) return score;
        if (!isMovesLeft()) 
               return 0;    
        if (isMax) {
               int best = MIN;
               for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                                 if (board[i][j] == ' ') {
                                        board[i][j] = HUMAN;
                                        best = (minimax(depth + 1, 0) > best) ? minimax(depth + 1, 0) : best;
                                        board[i][j] = ' ';
                                       } 
                                 }        
                          }        
              return best;    
              }
        else { 
             int best = MAX;
             for (int i = 0; i < 3; i++) {
                     for (int j = 0; j < 3; j++) {
                             if (board[i][j] == ' ') {
                                       board[i][j] = COMPUTER;
                                        best = (minimax(depth + 1, 1) < best) ? minimax(depth + 1, 1) : best; 
                                         board[i][j] = ' ';
                                         } 
                               } 
                         }
                 return best;
                 }
          }

void findBestMove() {
    int bestVal = MAX;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = COMPUTER;
                int moveVal = minimax(0, 1);
                board[i][j] = ' ';
                if (moveVal < bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    board[bestRow][bestCol] = COMPUTER;
}


void playerMove() {
    int row, col;
    printf("Enter your move (row and column: 0-2): ");
    scanf("%d %d", &row, &col);
    if (board[row][col] == ' ') {
        board[row][col] = HUMAN;
    } else {
        printf("Invalid move! Try again.\n");
        playerMove();
    }
}

int main() {
    initializeBoard();
    int turn = 0;
    while (isMovesLeft() && evaluate() == 0) {
        printBoard();
        if (turn % 2 == 0) {
            playerMove();
        } else {
            findBestMove();
        }
        turn++;
    }
    printBoard();
    int result = evaluate();
    if (result == 10) printf("Human wins!\n");
    else if (result == -10) printf("Computer wins!\n");
    else printf("It's a draw!\n");
    return 0;
}



