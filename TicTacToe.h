#ifndef TICTACTOE_C_GRAPHICS_TICTACTOE_H
#define TICTACTOE_C_GRAPHICS_TICTACTOE_H

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
#define PLAY_AGAIN_X 270
#define YEAH_BUTTON_Y 190
#define NAH_BUTTON_Y 240

const int INTERFACE_SIZE = 650;
const int BOARD_SIZE = 3;
int botDifficulty;

int board[BOARD_SIZE][BOARD_SIZE] = { {2,2,2},{2,2,2},{2,2,2} };
int copyArray[BOARD_SIZE][BOARD_SIZE] = { {2,2,2},{2,2,2},{2,2,2} };

char titleText[15] = "TIC TAC TOE", additionalText[30] = "Implemented using graphics.h",
        madeByText[15] = "Made by: Beka", easyModeText[10] = "Easy mode", mediumModeText[15] = "Medium mode",
        hardModeText[10] = "Hard mode", singleModeText[15] = "Single Player", multiplayerText[15] = "Multiplayer",
        exitText[5] = "Exit";

struct node
{
    int row;
    int col;
    int score;
}bestMove, currentMove;

struct GameAccount
{
    int points;
    char mode;
    char player1Name[50];
    char player2Name[50];
    int numberOfPlays;
    int player1Wins;
    int player2Wins;
    int draws;
} game;

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
void drawFinalMessage();
int checkButtonClick(int x, int y, int mouseX, int mouseY);
void drawButtonPlay(int x, int y, char* label);
void playAgainMenuSingle();
void singlePlayerGame();
void playAgainMenuDouble();
void doublePlayerGame();
void initializeGame(int players, char mode, char player1Name[50], char player2Name[50]);
void gameplay();

#endif
