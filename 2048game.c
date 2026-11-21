#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void initializeboard(int board[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
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
    int i, j;
    for(i = 0; i < 4; i++) {
        printf("+------+------+------+------+\n");
        for(j = 0; j < 4; j++) {
            if(board[i][j] == 0)
                printf("|      ");
            else
                printf("|  %2d  ", board[i][j]);
        }
        printf("|\n");
    }
    printf("+------+------+------+------+\n");
}
void moveLineLeft(int line[4], int *score) {
    int temp[4] = {0};
    int i, j = 0;
    for (i = 0; i < 4; i++) {
        if (line[i] != 0) {
            temp[j] = line[i];
            j++;
        }
    }
    for (i = 0; i < 3; i++) {
        if (temp[i] != 0 && temp[i] == temp[i + 1]) {
            temp[i] = temp[i] * 2;
            *score = *score + temp[i];

            temp[i + 1] = temp[i + 2];
            temp[i + 2] = temp[i + 3];
            temp[i + 3] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        line[i] = temp[i];
    }
}
int boardChanged(int oldBoard[4][4], int board[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (oldBoard[i][j] != board[i][j]) {
                return 1;
            }
        }
    }
    return 0;
}
int moveLeft(int board[4][4], int *score) {
    int oldBoard[4][4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            oldBoard[i][j] = board[i][j];
        }
    }
    for (i = 0; i < 4; i++) {
        moveLineLeft(board[i], score);
    }
    return boardChanged(oldBoard, board);
}
int moveRight(int board[4][4], int *score) {
    int oldBoard[4][4];
    int line[4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            oldBoard[i][j] = board[i][j];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            line[j] = board[i][3 - j];
        }
        moveLineLeft(line, score);
        for (j = 0; j < 4; j++) {
            board[i][3 - j] = line[j];
        }
    }
    return boardChanged(oldBoard, board);
}
int moveUp(int board[4][4], int *score) {
    int oldBoard[4][4];
    int line[4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            oldBoard[i][j] = board[i][j];
        }
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            line[i] = board[i][j];
        }
        moveLineLeft(line, score);
        for (i = 0; i < 4; i++) {
            board[i][j] = line[i];
        }
    }
    return boardChanged(oldBoard, board);
}
int moveDown(int board[4][4], int *score) {
    int oldBoard[4][4];
    int line[4];
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            oldBoard[i][j] = board[i][j];
        }
    }
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            line[i] = board[3 - i][j];
        }
        moveLineLeft(line, score);
        for (i = 0; i < 4; i++) {
            board[3 - i][j] = line[i];
        }
    }
    return boardChanged(oldBoard, board);
}
int main() {
    int board[4][4] = {0};
    int score = 0;
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
