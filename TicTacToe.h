#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <graphics.h>

#define BOARD_SIZE 3
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 700
#define INTERFACE_SIZE 650
#define CELL_WIDTH 110
#define CELL_HEIGHT 110
#define GRID_LEFT 40
#define GRID_TOP 70
#define CLICK_PADDING 5
#define MARK_SIZE 50
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
#define PLAY_AGAIN_X 270
#define YEAH_BUTTON_Y 190
#define NAH_BUTTON_Y 240

extern int board[BOARD_SIZE][BOARD_SIZE];
extern int copyArray[BOARD_SIZE][BOARD_SIZE];
extern int botDifficulty;

struct Move {
    int row, col, score;
};
extern struct Move bestMove, currentMove;

struct GameAccount {
    int points;
    char mode;
    char player1Name[50];
    char player2Name[50];
    int numberOfPlays;
    int player1Wins;
    int player2Wins;
    int draws;
};
extern struct GameAccount game;

int evaluateBoard(int temp[BOARD_SIZE][BOARD_SIZE]);
int countEmptyCells();
int minimaxMoveEvaluation(int l, int c);
void makeMoveAI();
int checkMouseBoxJ(int x);
int checkMouseBoxI(int y);
void getMousePos(int& x, int& y);
void playChance(int c);
void drawMarksOnScreen(char mark);
void drawGameInterface(char gameTitle[]);
void drawWinningLine(int team);
int checkWinner();
void drawCongratulations(int team, char name[]);
void drawTurn(char gameTitle[], char player1Name[50], char player2Name[50], int currentPlayer);
void gameStart(int players, char mode, char player1Name[50], char player2Name[50]);
void drawButton(int x, int y, int width, int height, char* label);
int isButtonClicked(int x, int y, int width, int height, int mouseX, int mouseY);
void drawSelectDifficulty();
int getDifficultyChoice();
void drawGameplayMenu();
int getGameplayChoice();
void drawPlayAgain();
int getPlayAgainChoice();
void drawFinalMessage();
void singlePlayerGame();
void doublePlayerGame();
void initializeGame(int players, char mode, char player1Name[50], char player2Name[50]);

#endif