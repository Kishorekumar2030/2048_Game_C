#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initializeboard(int board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
}   
void addrandomtile(int board[4][4]) {
    int row;
    int col;
    do {
        row = rand() % 4;
        col = rand() % 4;
    } while (board[row][col] != 0);
        board[row][col] = 2;
    
}
void displayBoard(int board[4][4]) {
    printf("\n");

    for(int i = 0; i < 4; i++) {
        printf("+------+------+------+------+\n");

        for(int j = 0; j < 4; j++) {
            if(board[i][j] == 0)
                printf("|      ");
            else
                printf("|  %2d  ", board[i][j]);
        }

        printf("|\n");
    }

    printf("+------+------+------+------+\n");
}
int main() {
int board[4][4]={0};
srand(time(0));
initializeboard(board);
addrandomtile(board);
addrandomtile(board);
addrandomtile(board);
addrandomtile(board);
addrandomtile(board);
displayBoard(board);
return 0;
}