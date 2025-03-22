#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "TicTacToe.h"

int board[BOARD_SIZE][BOARD_SIZE] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
int copyArray[BOARD_SIZE][BOARD_SIZE] = {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}};
int botDifficulty = 0;
struct Move bestMove, currentMove;
struct GameAccount game;

int evaluateBoard(int temp[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (temp[i][0] == temp[i][1] && temp[i][1] == temp[i][2]) {
            if (temp[i][0] == 0) return -10;
            if (temp[i][0] == 1) return 10;
        }
        if (temp[0][i] == temp[1][i] && temp[1][i] == temp[2][i]) {
            if (temp[0][i] == 0) return -10;
            if (temp[0][i] == 1) return 10;
        }
    }
    if (temp[0][0] == temp[1][1] && temp[1][1] == temp[2][2]) {
        if (temp[0][0] == 0) return -10;
        if (temp[0][0] == 1) return 10;
    }
    if (temp[0][2] == temp[1][1] && temp[1][1] == temp[2][0]) {
        if (temp[0][2] == 0) return -10;
        if (temp[0][2] == 1) return 10;
    }
    return 0;
}

int countEmptyCells() {
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == 2) count++;
    return count;
}

int minimaxMoveEvaluation(int l, int c) {
    int eval = evaluateBoard(board);
    if (eval == 10 && l >= 0) return 10 - (9 - l);
    if (eval == -10 && l >= 0) return -10 + (9 - l);
    if (l == 0 || countEmptyCells() == 0) return 0;

    int value = (c == 1) ? -1000 : 1000;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 2) {
                board[i][j] = c;
                int score = minimaxMoveEvaluation(l - 1, !c);
                board[i][j] = 2;
                if (c == 1 && score > value) value = score;
                if (c == 0 && score < value) value = score;
            }
        }
    }
    return value;
}

void makeMoveAI() {
    delay(1500);
    int emptyRows[9], emptyCols[9], numEmpty = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == 2) {
                emptyRows[numEmpty] = i;
                emptyCols[numEmpty] = j;
                numEmpty++;
            }

    if (numEmpty == 0) return;

    if (botDifficulty == 0) {
        int randIndex = rand() % numEmpty;
        board[emptyRows[randIndex]][emptyCols[randIndex]] = 1;
    } else if (botDifficulty == 1) {
        if (rand() % 2 == 0) {
            int randIndex = rand() % numEmpty;
            board[emptyRows[randIndex]][emptyCols[randIndex]] = 1;
        } else {
            int bestScore = -1000;
            for (int k = 0; k < numEmpty; k++) {
                int i = emptyRows[k], j = emptyCols[k];
                board[i][j] = 1;
                int score = minimaxMoveEvaluation(countEmptyCells() - 1, 0);
                board[i][j] = 2;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove.row = i;
                    bestMove.col = j;
                }
            }
            board[bestMove.row][bestMove.col] = 1;
        }
    } else {
        int bestScore = -1000;
        for (int k = 0; k < numEmpty; k++) {
            int i = emptyRows[k], j = emptyCols[k];
            board[i][j] = 1;
            int score = minimaxMoveEvaluation(countEmptyCells() - 1, 0);
            board[i][j] = 2;
            if (score > bestScore) {
                bestScore = score;
                bestMove.row = i;
                bestMove.col = j;
            }
        }
        board[bestMove.row][bestMove.col] = 1;
    }
}

int checkMouseBoxJ(int x) {
    for (int j = 0; j < BOARD_SIZE; j++) {
        int left = GRID_LEFT + j * CELL_WIDTH + CLICK_PADDING;
        int right = GRID_LEFT + (j + 1) * CELL_WIDTH - CLICK_PADDING;
        if (x > left && x < right) return j;
    }
    return -1;
}

int checkMouseBoxI(int y) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        int top = GRID_TOP + i * CELL_HEIGHT + CLICK_PADDING;
        int bottom = GRID_TOP + (i + 1) * CELL_HEIGHT - CLICK_PADDING;
        if (y > top && y < bottom) return i;
    }
    return -1;
}

void getMousePos(int& x, int& y) {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    x = cursorPos.x;
    y = cursorPos.y;
}

void playChance(int c) {
    int x, y;
    while (true) {
        getMousePos(x, y);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            int boxI = checkMouseBoxI(y);
            int boxJ = checkMouseBoxJ(x);
            if (boxI != -1 && boxJ != -1 && board[boxI][boxJ] == 2) {
                board[boxI][boxJ] = c;
                break;
            }
            delay(100);
        }
    }
}

void drawMarksOnScreen(char mark) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (copyArray[i][j] != board[i][j]) {
                int centerX = GRID_LEFT + j * CELL_WIDTH + CELL_WIDTH / 2;
                int centerY = GRID_TOP + i * CELL_HEIGHT + CELL_HEIGHT / 2;
                if (mark == 'o')
                    circle(centerX, centerY, MARK_SIZE);
                else {
                    line(centerX - MARK_SIZE, centerY - MARK_SIZE, centerX + MARK_SIZE, centerY + MARK_SIZE);
                    line(centerX + MARK_SIZE, centerY - MARK_SIZE, centerX - MARK_SIZE, centerY + MARK_SIZE);
                }
                copyArray[i][j] = board[i][j];
            }
        }
    }
}

void drawGameInterface(char gameTitle[]) {
    cleardevice();
    setcolor(8);
    rectangle(10, 10, INTERFACE_SIZE + 10, INTERFACE_SIZE);
    settextjustify(1, 2);
    settextstyle(3, 0, 4);
    outtextxy(INTERFACE_SIZE / 2 + 10, 15, "TIC TAC TOE");
    settextstyle(3, 0, 2);
    outtextxy(INTERFACE_SIZE / 2 + 15, 45, gameTitle);
    setcolor(8);
    line(GRID_LEFT + CELL_WIDTH, GRID_TOP, GRID_LEFT + CELL_WIDTH, GRID_TOP + 3 * CELL_HEIGHT);
    line(GRID_LEFT + 2 * CELL_WIDTH, GRID_TOP, GRID_LEFT + 2 * CELL_WIDTH, GRID_TOP + 3 * CELL_HEIGHT);
    line(GRID_LEFT, GRID_TOP + CELL_HEIGHT, GRID_LEFT + 3 * CELL_WIDTH, GRID_TOP + CELL_HEIGHT);
    line(GRID_LEFT, GRID_TOP + 2 * CELL_HEIGHT, GRID_LEFT + 3 * CELL_WIDTH, GRID_TOP + 2 * CELL_HEIGHT);
    settextstyle(3, 0, 3);
    outtextxy(INTERFACE_SIZE - 70, INTERFACE_SIZE / 2 + 90, "Made By: Beka");
}

void drawWinningLine(int team) {
    setlinestyle(2, 0, 3);
    int startX, startY, endX, endY;
    switch (team) {
        case 1: startX = GRID_LEFT; startY = GRID_TOP + CELL_HEIGHT / 2; endX = GRID_LEFT + 3 * CELL_WIDTH; endY = startY; break;
        case 2: startX = GRID_LEFT; startY = GRID_TOP + 3 * CELL_HEIGHT / 2; endX = GRID_LEFT + 3 * CELL_WIDTH; endY = startY; break;
        case 3: startX = GRID_LEFT; startY = GRID_TOP + 5 * CELL_HEIGHT / 2; endX = GRID_LEFT + 3 * CELL_WIDTH; endY = startY; break;
        case 4: startX = GRID_LEFT + CELL_WIDTH / 2; startY = GRID_TOP; endX = startX; endY = GRID_TOP + 3 * CELL_HEIGHT; break;
        case 5: startX = GRID_LEFT + 3 * CELL_WIDTH / 2; startY = GRID_TOP; endX = startX; endY = GRID_TOP + 3 * CELL_HEIGHT; break;
        case 6: startX = GRID_LEFT + 5 * CELL_WIDTH / 2; startY = GRID_TOP; endX = startX; endY = GRID_TOP + 3 * CELL_HEIGHT; break;
        case 7: startX = GRID_LEFT; startY = GRID_TOP; endX = GRID_LEFT + 3 * CELL_WIDTH; endY = GRID_TOP + 3 * CELL_HEIGHT; break;
        default: startX = GRID_LEFT + 3 * CELL_WIDTH; startY = GRID_TOP; endX = GRID_LEFT; endY = GRID_TOP + 3 * CELL_HEIGHT; break;
    }
    line(startX, startY, endX, endY);
}

int checkWinner() {
    int i;
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 2) {
            drawWinningLine(1 + i);
            return (board[i][0] == 0) ? 1 : 2;
        }
    }
    for (i = 0; i < BOARD_SIZE; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 2) {
            drawWinningLine(4 + i);
            return (board[0][i] == 0) ? 1 : 2;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != 2) {
        drawWinningLine(7);
        return (board[1][1] == 0) ? 1 : 2;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 2) {
        drawWinningLine(8);
        return (board[1][1] == 0) ? 1 : 2;
    }
    return 0;
}

void drawCongratulations(int team, char name[]) {
    settextstyle(3, 0, 4);
    if (team == 1) {
        outtextxy(490, 80, name);
        outtextxy(490, 120, "Has");
        outtextxy(490, 160, "Won");
        outtextxy(490, 200, "The");
        outtextxy(490, 240, "Game");
    } else {
        outtextxy(490, 80, "The");
        outtextxy(490, 120, "Game");
        outtextxy(490, 160, "Has");
        outtextxy(490, 200, "Drawn");
    }
}

void drawTurn(char gameTitle[], char player1Name[50], char player2Name[50], int currentPlayer) {
    settextstyle(3, 0, 2);
    char currentPlayerText[100];
    sprintf(currentPlayerText, "Current Player: %s", (currentPlayer == 0) ? player1Name : player2Name);
    outtextxy(510, 500, currentPlayerText);
}

void gameStart(int players, char mode, char player1Name[50], char player2Name[50]) {
    game.numberOfPlays++;
    int winner = 0;
    int currentPlayer = rand() % 2;
    char head[50];
    sprintf(head, "%s VS %s", player1Name, player2Name);
    drawGameInterface(head);
    drawTurn(head, player1Name, player2Name, currentPlayer);
    char marks[2] = {'o', 'x'};

    while (countEmptyCells() != 0 && winner == 0) {
        if (players == 2 || currentPlayer == 0)
            playChance(currentPlayer);
        else
            makeMoveAI();

        drawMarksOnScreen(marks[currentPlayer]);
        drawTurn(head, player1Name, player2Name, !currentPlayer);
        currentPlayer = !currentPlayer;
        delay(100);
        winner = checkWinner();
    }

    if (winner == 1) {
        game.player1Wins++;
        drawCongratulations(1, player1Name);
    } else if (winner == 2) {
        game.player2Wins++;
        drawCongratulations(1, player2Name);
    } else {
        game.draws++;
        drawCongratulations(0, " ");
    }
}

void drawButton(int x, int y, int width, int height, char* label) {
    setcolor(15);
    rectangle(x, y, x + width, y + height);
    settextjustify(1, 2);
    settextstyle(3, 0, 2);
    outtextxy(x + width / 2, y + height / 2 - 5, label);
}

int isButtonClicked(int x, int y, int width, int height, int mouseX, int mouseY) {
    return mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height;
}

void drawSelectDifficulty() {
    cleardevice();
    settextstyle(3, 0, 4);
    outtextxy(INTERFACE_SIZE / 2 + 10, 15, "Select Difficulty");
    drawButton(250, 140, BUTTON_WIDTH, BUTTON_HEIGHT, "Easy mode");
    drawButton(250, 190, BUTTON_WIDTH, BUTTON_HEIGHT, "Medium mode");
    drawButton(250, 240, BUTTON_WIDTH, BUTTON_HEIGHT, "Hard mode");
}

int getDifficultyChoice() {
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            if (isButtonClicked(250, 140, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 0;
            if (isButtonClicked(250, 190, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 1;
            if (isButtonClicked(250, 240, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 2;
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

void drawGameplayMenu() {
    cleardevice();
    settextstyle(3, 0, 4);
    outtextxy(INTERFACE_SIZE / 2 + 10, 15, "TIC TAC TOE");
    settextstyle(3, 0, 2);
    outtextxy(INTERFACE_SIZE / 2 + 15, 45, "Choose game mode");
    drawButton(250, 140, BUTTON_WIDTH, BUTTON_HEIGHT, "Single Player");
    drawButton(250, 190, BUTTON_WIDTH, BUTTON_HEIGHT, "Multiplayer");
    drawButton(250, 240, BUTTON_WIDTH, BUTTON_HEIGHT, "Exit");
}

int getGameplayChoice() {
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            if (isButtonClicked(250, 140, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 1;
            if (isButtonClicked(250, 190, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 2;
            if (isButtonClicked(250, 240, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 3;
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

void drawPlayAgain() {
    cleardevice();
    settextstyle(3, 0, 2);
    outtextxy(370, 140, "Do you want to play again?");
    drawButton(PLAY_AGAIN_X, YEAH_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Yeah");
    drawButton(PLAY_AGAIN_X, NAH_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, "Nah");
}

int getPlayAgainChoice() {
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            if (isButtonClicked(PLAY_AGAIN_X, YEAH_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 1;
            if (isButtonClicked(PLAY_AGAIN_X, NAH_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, mouseX, mouseY)) return 2;
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

void drawFinalMessage() {
    cleardevice();
    settextstyle(3, 0, 2);
    outtextxy(370, 100, "Thanks for spending time");
    outtextxy(320, 140, "Game Statistics:");
    char vsText[100];
    sprintf(vsText, "%s VS %s", game.player1Name, game.player2Name);
    outtextxy(320, 180, vsText);
    char gamesPlayedText[100];
    sprintf(gamesPlayedText, "No. of Games Played: %d", game.numberOfPlays);
    outtextxy(320, 220, gamesPlayedText);
    char player1WinsText[100];
    sprintf(player1WinsText, "No. of Games Won By %s: %d", game.player1Name, game.player1Wins);
    outtextxy(320, 260, player1WinsText);
    char player2WinsText[100];
    sprintf(player2WinsText, "No. of Games Won By %s: %d", game.player2Name, game.player2Wins);
    outtextxy(320, 300, player2WinsText);
    char drawsText[100];
    sprintf(drawsText, "No. of Games Drawn: %d", game.draws);
    outtextxy(320, 340, drawsText);
    delay(5000);
}

void singlePlayerGame() {
    char playerName[50] = "Player#1";
    char computerName[10] = "Computer";
    initializeGame(1, 'o', playerName, computerName);
    while (true) {
        gameStart(1, 'o', playerName, computerName);
        delay(2000);
        drawPlayAgain();
        if (getPlayAgainChoice() == 2) {
            drawFinalMessage();
            break;
        }
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                board[i][j] = copyArray[i][j] = 2;
    }
}

void doublePlayerGame() {
    char player1Name[10] = "Player#1";
    char player2Name[10] = "Player#2";
    initializeGame(2, 'o', player1Name, player2Name);
    while (true) {
        gameStart(2, 'o', player1Name, player2Name);
        delay(2000);
        drawPlayAgain();
        if (getPlayAgainChoice() == 2) {
            drawFinalMessage();
            break;
        }
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
                board[i][j] = copyArray[i][j] = 2;
    }
}

void initializeGame(int players, char mode, char player1Name[50], char player2Name[50]) {
    game.points = players;
    game.mode = mode;
    strcpy(game.player1Name, player1Name);
    strcpy(game.player2Name, player2Name);
    game.numberOfPlays = 0;
    game.player1Wins = 0;
    game.player2Wins = 0;
    game.draws = 0;
}

int main() {
    srand(time(NULL));
    initwindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TIC-TAC-TOE");
    while (true) {
        drawGameplayMenu();
        int choice = getGameplayChoice();
        if (choice == 1) {
            drawSelectDifficulty();
            botDifficulty = getDifficultyChoice();
            singlePlayerGame();
        } else if (choice == 2) {
            doublePlayerGame();
        } else if (choice == 3) {
            break;
        }
    }
    closegraph();
    return 0;
}