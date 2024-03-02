#ifndef TICTACTOE_C_GRAPHICS_TICTACTOE_H
#define TICTACTOE_C_GRAPHICS_TICTACTOE_H

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 40
#define PLAY_AGAIN_X 270
#define YEAH_BUTTON_Y 190
#define NAH_BUTTON_Y 240

const int BOARD_SIZE = 3;
int botDifficulty;

int board[BOARD_SIZE][BOARD_SIZE] = { {2,2,2},{2,2,2},{2,2,2} };
int copyArray[BOARD_SIZE][BOARD_SIZE] = { {2,2,2},{2,2,2},{2,2,2} };

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
