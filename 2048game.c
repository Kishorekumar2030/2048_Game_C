#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

void initializeboard(int board[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            board[i][j] = 0;
}

void addrandomtile(int board[4][4]) {
    int empty = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (board[i][j] == 0) empty++;
    if (empty == 0) return; 

    int row, col;
    do {
        row = rand() % 4;
        col = rand() % 4;
    } while (board[row][col] != 0);
    board[row][col] = (rand() % 10 == 0) ? 4 : 2;
}

void moveLineLeft(int line[4], int *score) {
    int temp[4] = {0}, j = 0;

    for (int i = 0; i < 4; i++) {
        if (line[i] != 0) {
            temp[j++] = line[i];
        }
    }

    for (int i = 0; i < 3; i++) {
        if (temp[i] != 0 && temp[i] == temp[i + 1]) {
            temp[i] *= 2;
            *score += temp[i];
            temp[i + 1] = 0;
            i++;
        }
    }
    
    int result[4] = {0};
    j = 0;
    for (int i = 0; i < 4; i++) {
        if (temp[i] != 0) {
            result[j++] = temp[i];
        }
    }

    for (int i = 0; i < 4; i++) {
        line[i] = result[i];
    }
}

int boardChanged(int oldBoard[4][4], int board[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (oldBoard[i][j] != board[i][j]) return 1;
    return 0;
}

int moveLeft(int board[4][4], int *score) {
    int oldBoard[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) oldBoard[i][j] = board[i][j];
    for (int i = 0; i < 4; i++) moveLineLeft(board[i], score);
    return boardChanged(oldBoard, board);
}

int moveRight(int board[4][4], int *score) {
    int oldBoard[4][4], line[4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) oldBoard[i][j] = board[i][j];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) line[j] = board[i][3 - j];
        moveLineLeft(line, score);
        for (int j = 0; j < 4; j++) board[i][3 - j] = line[j];
    }
    return boardChanged(oldBoard, board);
}

int moveUp(int board[4][4], int *score) {
    int oldBoard[4][4], line[4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) oldBoard[i][j] = board[i][j];
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) line[i] = board[i][j];
        moveLineLeft(line, score);
        for (int i = 0; i < 4; i++) board[i][j] = line[i];
    }
    return boardChanged(oldBoard, board);
}

int moveDown(int board[4][4], int *score) {
    int oldBoard[4][4], line[4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) oldBoard[i][j] = board[i][j];
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) line[i] = board[3 - i][j];
        moveLineLeft(line, score);
        for (int i = 0; i < 4; i++) board[3 - i][j] = line[i];
    }
    return boardChanged(oldBoard, board);
}

Color getTileColor(int value) {
    switch (value) {
        case 0:    return (Color){205, 193, 180, 255};
        case 2:    return (Color){238, 228, 218, 255};
        case 4:    return (Color){237, 224, 200, 255};
        case 8:    return (Color){242, 177, 121, 255};
        case 16:   return (Color){245, 149, 99, 255};
        case 32:   return (Color){246, 124, 95, 255};
        case 64:   return (Color){246, 94, 59, 255};
        default:   return (Color){237, 207, 114, 255};
    }
}

int main(void) {
    int board[4][4] = {0};
    int score = 0;
    srand(time(0));
    initializeboard(board);
    addrandomtile(board);
    addrandomtile(board);

    InitWindow(460, 540, "2048 in C");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // 1. Handle Input
        int moved = 0;
        if (IsKeyPressed(KEY_LEFT))  moved = moveLeft(board, &score);
        if (IsKeyPressed(KEY_RIGHT)) moved = moveRight(board, &score);
        if (IsKeyPressed(KEY_UP))    moved = moveUp(board, &score);
        if (IsKeyPressed(KEY_DOWN))  moved = moveDown(board, &score);

        if (moved) addrandomtile(board);

        // 2. Draw GUI
        BeginDrawing();
        ClearBackground((Color){250, 248, 239, 255});

        DrawText(TextFormat("SCORE: %d", score), 20, 25, 30, DARKGRAY);
        DrawRectangleRounded((Rectangle){20, 80, 420, 420}, 0.05f, 8, (Color){187, 173, 160, 255});

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int val = board[i][j];
                int x = 32 + j * 102;
                int y = 92 + i * 102;

                DrawRectangleRounded((Rectangle){x, y, 90, 90}, 0.1f, 8, getTileColor(val));

                if (val > 0) {
                    const char *text = TextFormat("%d", val);
                    int fontSize = (val >= 1000) ? 28 : 36;
                    int textWidth = MeasureText(text, fontSize);
                    Color textColor = (val <= 4) ? (Color){119, 110, 101, 255} : WHITE;
                    DrawText(text, x + (90 - textWidth) / 2, y + (90 - fontSize) / 2, fontSize, textColor);
                }
            }
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
