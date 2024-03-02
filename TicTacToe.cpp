#include<graphics.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"TicTacToe.h"


int evaluateBoard(int temp[BOARD_SIZE][BOARD_SIZE])
{
    int i;

    for (i = 0; i < BOARD_SIZE; i++) // Checking for rows and columns
    {
        if (temp[i][0] == temp[i][1] && temp[i][1] == temp[i][2])
        {
            if (temp[i][0] == 0)
                return -10;
            else if (temp[i][0] == 1)
                return +10;
        }

        if (temp[0][i] == temp[1][i] && temp[1][i] == temp[2][i])
        {
            if (temp[0][i] == 0)
                return -10;
            else if (temp[0][i] == 1)
                return +10;
        }
    }

    // Checking for diagonals
    if (temp[0][0] == temp[1][1] && temp[1][1] == temp[2][2])
    {
        if (temp[1][1] == 0)
            return -10;
        else if (temp[1][1] == 1)
            return +10;
    }

    if (temp[0][2] == temp[1][1] && temp[1][1] == temp[2][0])
    {
        if (temp[1][1] == 0)
            return -10;
        else if (temp[1][1] == 1)
            return +10;
    }

    return 0;
}

int countEmptyCells()
{
    int emptyCellCount = 0;

    for (int row = 0; row < BOARD_SIZE; ++row)
    {
        for (int col = 0; col < BOARD_SIZE; ++col)
        {
            if (board[row][col] == 2)
            {
                ++emptyCellCount;
            }
        }
    }

    return emptyCellCount;
}

int minimaxMoveEvaluation(int l, int c)
{
    if (evaluateBoard(board) == 10 && l >= 0)
        return evaluateBoard(board) - 9 + l;
    else if (evaluateBoard(board) == -10 && l >= 0)
        return evaluateBoard(board) + 9 - l;
    else if (l == 0 && evaluateBoard(board) == 0)
        return 0;
    else
    {
        int score;
        int value;
        int t = 0;
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (board[i][j] == 2)
                {
                    board[i][j] = c;
                    score = minimaxMoveEvaluation(l - 1, !c);
                    if (c == 1)
                    {
                        if (score > value && t > 0)
                            value = score;
                        if (t == 0)
                            value = score;
                    }
                    if (c == 0)
                    {
                        if (score < value && t>0)
                            value = score;
                        if (t == 0)
                            value = score;
                    }
                    t++;
                    board[i][j] = 2;
                }
            }
        }
        return value;
    }
}

void makeMoveAI()
{
    delay(1500);
    int emptyCellCount = countEmptyCells();
    int isFirstIteration = 1;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 2)
            {
                if (rand() % 100 < 100)
                {
                    board[i][j] = 1;
                    return;
                }

                board[i][j] = 1;
                currentMove.row = i;
                currentMove.col = j;
                currentMove.score = minimaxMoveEvaluation(emptyCellCount - 1, 0);

                if (currentMove.score > bestMove.score && !isFirstIteration)
                {
                    bestMove = currentMove;
                }

                if (isFirstIteration)
                {
                    bestMove = currentMove;
                    isFirstIteration = 0;
                }

                board[i][j] = 2;
            }
        }
    }

    board[bestMove.row][bestMove.col] = 1;
}

int checkMouseBoxJ(int x)
{
    if (x > 265 && x < 365) {
        return 2;
    }
    else if (x > 155 && x < 255) {
        return 1;
    }
    else if (x > 45 && x < 145) {
        return 0;
    }
    return -1;
}

int checkMouseBoxI(int y)
{
    if (y > 295 && y < 395) {
        return 2;
    }
    else if (y > 185 && y < 285) {
        return 1;
    }
    else if (y > 75 && y < 175) {
        return 0;
    }
    return -1;
}

void getMousePos(int& x, int& y)
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    x = cursorPos.x;
    y = cursorPos.y;
}

void playChance(int c) //play chance for players
{
    int x, y;
    while (true) {
        getMousePos(x, y);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8001) {
            int boxI = checkMouseBoxI(y);
            int boxJ = checkMouseBoxJ(x);

            if (boxI != -1 && boxJ != -1) {
                if (board[boxI][boxJ] == 2) {
                    board[boxI][boxJ] = c;
                    break;
                }
            }
        }
    }
}

void drawMarksOnScreen(char mark) // draw marks on screen
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (copyArray[i][j] != board[i][j])
            {
                if (mark == 'o')
                    circle(95 + j * 110, 125 + i * 110, 50);
                else
                {
                    line(45 + j * 110, 75 + i * 110, 145 + j * 110, 175 + i * 110);
                    line(145 + j * 110, 75 + i * 110, 45 + j * 110, 175 + i * 110);
                }
                copyArray[i][j] = board[i][j];
            }
        }
    }

}

void drawGameInterface(char gameTitle[])
{
    initwindow(800, 700, "TIC-TAC-TOE");
    cleardevice();

    // Setting the color and style of the lines
    setcolor(8);

    // Drawing the boundaries of the field
    const int INTERFACE_SIZE  = 650;
    line(10, 10, 10, INTERFACE_SIZE);
    line(INTERFACE_SIZE  + 10, 10, INTERFACE_SIZE  + 10, INTERFACE_SIZE);
    line(10, 10, INTERFACE_SIZE  + 10, 10);
    line(10, INTERFACE_SIZE , INTERFACE_SIZE  + 10, INTERFACE_SIZE );

    // Setting the text style and displaying the title
    char gameTitleText[15] = "TIC TAC TOE";
    settextjustify(1, 2);
    settextstyle(3, 0, 4);
    outtextxy(INTERFACE_SIZE  / 2 + 10, 15, gameTitleText);

    // Displaying additional text
    settextstyle(3, 0, 2);
    outtextxy(INTERFACE_SIZE  / 2 + 15, 45, gameTitle);

    // Drawing lines on the field with a delay
    const int DELAY_TIME = 0;
    const int LINE_LENGTH = 30;

    for (int i = 10; i <= INTERFACE_SIZE  / 2; i += 10)
    {
        line(150, 70 + i - 10, 150, 70 + i + LINE_LENGTH);
        delay(DELAY_TIME);
    }

    for (int i = 10; i <= INTERFACE_SIZE  / 2; i += 10)
    {
        line(260, 70 + i - 10, 260, 70 + i + LINE_LENGTH);
        delay(DELAY_TIME);
    }

    for (int i = 10; i <= INTERFACE_SIZE / 2; i += 10)
    {
        line(40 + i - 10, 180, 40 + i + LINE_LENGTH, 180);
        delay(DELAY_TIME);
    }

    for (int i = 10; i <= INTERFACE_SIZE / 2; i += 10)
    {
        line(40 + i - 10, 290, 40 + i + LINE_LENGTH, 290);
        delay(DELAY_TIME);
    }

    // Additional information
    char additionalText[15] = "Made By: Beka";
    settextjustify(1, 2);
    settextstyle(3, 0, 3);
    outtextxy(INTERFACE_SIZE - 70, INTERFACE_SIZE / 2 + 90, additionalText);
}

void drawWinningLine(int team) // draw line if team wins
{
    setlinestyle(2, 0, 3);

    int startX, startY, endX, endY;

    switch (team) {
        case 1:
            startX = 40;
            startY = 125;
            endX = 370;
            endY = 125;
            break;
        case 2:
            startX = 40;
            startY = 235;
            endX = 370;
            endY = 235;
            break;
        case 3:
            startX = 40;
            startY = 345;
            endX = 370;
            endY = 345;
            break;
        case 4:
            startX = 95;
            startY = 70;
            endX = 95;
            endY = 400;
            break;
        case 5:
            startX = 205;
            startY = 70;
            endX = 205;
            endY = 400;
            break;
        case 6:
            startX = 315;
            startY = 70;
            endX = 315;
            endY = 400;
            break;
        case 7:
            startX = 40;
            startY = 70;
            endX = 370;
            endY = 400;
            break;
        default:
            startX = 370;
            startY = 70;
            endX = 40;
            endY = 400;
            break;
    }

    line(startX, startY, endX, endY);
    delay(50);

}

int checkWinner() // check if a team has won
{
    int i;

    // Checking for rows
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 2)
        {
            drawWinningLine(1 + i);
            return (board[i][0] == 0) ? 1 : 2;
        }
    }

    // Checking for columns
    for (i = 0; i < BOARD_SIZE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 2)
        {
            drawWinningLine(4 + i);
            return (board[0][i] == 0) ? 1 : 2;
        }
    }

    // Checking for left diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != 2)
    {
        drawWinningLine(7);
        return (board[1][1] == 0) ? 1 : 2;
    }

    // Checking for right diagonal
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 2)
    {
        drawWinningLine(8);
        return (board[1][1] == 0) ? 1 : 2;
    }

    return 0; // No winner yet
}

void drawCongratulations(int team, char name[]) // draws congratulations of winning team
{
    int delayTime = 0;

    char hasText[4] = "Has", wonText[4] = "Won", theText[4] = "The", gameText[5]= "Game", drawnText[6] = "Drawn";

    if (team == 1)
    {
        settextstyle(3, 0, 4);
        outtextxy(490, 80, name);
        delay(delayTime);
        outtextxy(490, 120, hasText);
        delay(delayTime);
        outtextxy(490, 160, wonText);
        delay(delayTime);
        outtextxy(490, 200, theText);
        delay(delayTime);
        outtextxy(490, 240, gameText);
    }
    else
    {
        settextstyle(3, 0, 4);
        outtextxy(490, 80, theText);
        delay(delayTime);
        outtextxy(490, 120, gameText);
        delay(delayTime);
        outtextxy(490, 160, hasText);
        delay(delayTime);
        outtextxy(490, 200, drawnText);
    }
}

void drawTurn(char gameTitle[], char player1Name[50], char player2Name[50], int currentPlayer){
    settextstyle(3, 0, 2);
    char currentPlayerText[100];
    sprintf(currentPlayerText, "Current Player: %s", (currentPlayer == 0) ? player1Name : player2Name);
    outtextxy(510, 500, currentPlayerText);
}

void gameStart(int players, char mode, char player1Name[50], char player2Name[50])
{
    (game.numberOfPlays)++;
    int winner = 0;
    int currentPlayerStart = (rand() % 2 == 0) ? 0 : 1;
    int currentPlayer = currentPlayerStart;

    char head[50] = "";
    strcat(head, player1Name);
    strcat(head, " VS ");
    strcat(head, player2Name);
    drawGameInterface(head);
    drawTurn(head, player1Name, player2Name, currentPlayer);

    char marks[2];

    marks[currentPlayer] = 'o';
    marks[!currentPlayer] = 'x';

    while (countEmptyCells() != 0 && winner == 0)
    {
        if (players == 2)
        {
            playChance(currentPlayer);
        }
        else
        {
            if (currentPlayer == 0)
                playChance(0);
            else
                makeMoveAI();
        }

        drawMarksOnScreen(marks[currentPlayer]);

        drawTurn(head, player1Name, player2Name, !currentPlayer);

        currentPlayer = !currentPlayer;

        delay(100);

        winner = checkWinner();
    }

    if (winner == 1)
    {
        (game.player1Wins)++;
        drawCongratulations(1, player1Name);
    }
    else if (winner == 2)
    {
        (game.player2Wins)++;
        drawCongratulations(1, player2Name);
    }
    else
    {
        (game.draws)++;
        char empty[2] = " ";
        drawCongratulations(0, empty);
    }

    delay(2000);
    cleardevice();
    restorecrtmode();

    for (int a = 0; a < 3; a++)
        for (int b = 0; b < 3; b++)
            board[a][b] = copyArray[a][b] = 2;
}

void drawButton(int x, int y, char* label) {
    setcolor(15);
    rectangle(x, y, x + 150, y + 40);
    outtextxy(x + 75, y + 10, label);
}

void drawFinalMessage(){
    cleardevice();

    char mainText[25] = "Thanks for spending time", statisticText[20] = "Game Statistics:";

    outtextxy(370, 100, mainText);
    delay(2500);

    int x = 320;
    int y = 140;
    int lineHeight = 40;

    outtextxy(x, y, statisticText);
    y += lineHeight;

    char vsText[100];
    sprintf(vsText, "%s VS %s", game.player1Name, game.player2Name);
    outtextxy(x, y, vsText);
    y += lineHeight;

    char gamesPlayedText[100];
    sprintf(gamesPlayedText, "No. of Games Played: %d", game.numberOfPlays);
    outtextxy(x, y, gamesPlayedText);
    y += lineHeight;

    char player1WinsText[100];
    sprintf(player1WinsText, "No. of Games Won By %s: %d", game.player1Name, game.player1Wins);
    outtextxy(x, y, player1WinsText);
    y += lineHeight;

    char player2WinsText[100];
    sprintf(player2WinsText, "No. of Games Won By %s: %d", game.player2Name, game.player2Wins);
    outtextxy(x, y, player2WinsText);
    y += lineHeight;

    char drawsText[100];
    sprintf(drawsText, "No. of Games Drawn: %d", game.draws);
    outtextxy(x, y, drawsText);

    delay(5000);

    closegraph();
}

int checkButtonClick(int x, int y, int mouseX, int mouseY) {
    if (mouseX >= x && mouseX <= x + 150 && mouseY >= y && mouseY <= y + 40) {
        return 1;
    } else{
        return 0;
    }
}

void gameplay(){
    initwindow(800, 700);
    cleardevice();

    setcolor(8);

    // Drawing the boundaries of the field
    const int INTERFACE_SIZE  = 650;
    line(10, 10, 10, INTERFACE_SIZE);
    line(INTERFACE_SIZE  + 10, 10, INTERFACE_SIZE  + 10, INTERFACE_SIZE);
    line(10, 10, INTERFACE_SIZE  + 10, 10);
    line(10, INTERFACE_SIZE , INTERFACE_SIZE  + 10, INTERFACE_SIZE );

    // Setting the text style and displaying the title
    char mainText[15] = "TIC TAC TOE";
    settextjustify(1, 2);
    settextstyle(3, 0, 4);
    outtextxy(INTERFACE_SIZE  / 2 + 10, 15, mainText);

    // Displaying additional text
    char additionalText[30] = "Implemented using graphics.h";
    settextstyle(3, 0, 2);
    outtextxy(INTERFACE_SIZE  / 2 + 15, 45, additionalText);

    char madeByText[20] = "Made By: Beka", singleModeText[15] = "Single Player",
            multiplayerModeText[12] = "Multiplayer", exitText[5] = "Exit";
    settextjustify(1, 2);
    settextstyle(3, 0, 3);
    outtextxy(INTERFACE_SIZE - 70, INTERFACE_SIZE / 2 + 90, madeByText);

    drawButton(250, 140, singleModeText);
    drawButton(250, 190, multiplayerModeText);
    drawButton(250, 240, exitText);

    int choice = 0;

    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mouseX, mouseY;
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

            if (checkButtonClick(250, 140, mouseX, mouseY)) {
                choice = 1;
            } else if (checkButtonClick(250, 190, mouseX, mouseY)) {
                choice = 2;
            } else if (checkButtonClick(250, 240, mouseX, mouseY)) {
                choice = 3;
            }

            clearmouseclick(WM_LBUTTONDOWN);
        }

        if (choice != 0) {
            switch (choice) {
                case 1:
                    closegraph();
                    singlePlayerGame();
                    break;
                case 2:
                    closegraph();
                    doublePlayerGame();
                    break;
                case 3:
                    closegraph();
                    return;
            }
            break;
        }

    }
    delay(5000);
    closegraph();
}

void drawButtonPlay(int x, int y, char* label) {
    setcolor(15);
    rectangle(x, y, x + BUTTON_WIDTH, y + BUTTON_HEIGHT);
    outtextxy(x + BUTTON_WIDTH / 2, y + 5, label);
}

void drawPlayAgain() {
    cleardevice();
    char playAgainText[30] = "Do you want to play again?", yeahText[5] = "Yeah", nahText[4] = "Nah";
    outtextxy(370, 140, playAgainText);
    drawButtonPlay(PLAY_AGAIN_X, YEAH_BUTTON_Y, yeahText);
    drawButtonPlay(PLAY_AGAIN_X, NAH_BUTTON_Y, nahText);
}

int getMouseClickChoice(int yeahButtonY, int nahButtonY) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
        int mouseX, mouseY;
        getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);

        if (checkButtonClick(PLAY_AGAIN_X, nahButtonY, mouseX, mouseY)) {
            return 2;
        } else if (checkButtonClick(PLAY_AGAIN_X, yeahButtonY, mouseX, mouseY)) {
            return 1;
        }

        clearmouseclick(WM_LBUTTONDOWN);
    }

    return 0;
}

void handleSinglePlayerChoice(int choice) {
    switch (choice) {
        case 1:
            closegraph();
            singlePlayerGame();
            break;
        case 2:
            drawFinalMessage();
            break;
    }
}

void handleDoublePlayerChoice(int choice) {
    switch (choice) {
        case 1:
            closegraph();
            doublePlayerGame();
            break;
        case 2:
            drawFinalMessage();
            break;
    }
}

void playAgainMenu(int yeahButtonY, int nahButtonY, void (*handleChoice)(int)) {
    drawPlayAgain();

    int choice = 0;
    while (1) {
        choice = getMouseClickChoice(yeahButtonY, nahButtonY);

        if (choice != 0) {
            handleChoice(choice);
        }
    }
}

void singlePlayerGame() {
    srand(time(NULL));
    char playerName[50] = "Player#1";

    int randomNum = rand() % 2 + 1;
    char markChoice = (char)(randomNum + '0'),
            computerName[10] = "Computer";

    switch (markChoice) {
        case '1':
            initializeGame(1, 'o', playerName, computerName);
            gameStart(1, 'o', playerName, computerName);
            break;
        case '2':
            initializeGame(1, 'x', playerName, computerName);
            gameStart(1, 'x', playerName, computerName);
            break;
        default:
            printf("Wrong Choice");
            break;
    }

    playAgainMenu(YEAH_BUTTON_Y, NAH_BUTTON_Y, handleSinglePlayerChoice);
}

void doublePlayerGame() {
    srand(time(NULL));

    char player1Name[10] = "Player#1";
    char player2Name[10] = "Player#2";

    int randomNum = rand() % 2 + 1;
    char markChoice = (char)(randomNum + '0');

    switch (markChoice) {
        case '1':
            initializeGame(2, 'o', player1Name, player2Name);
            gameStart(2, 'o', player1Name, player2Name);
            break;
        case '2':
            initializeGame(2, 'x', player1Name, player2Name);
            gameStart(2, 'x', player1Name, player2Name);
            break;
        default:
            printf("Wrong Choice");
            gameplay();
            break;
    }

    playAgainMenu(YEAH_BUTTON_Y, NAH_BUTTON_Y, handleDoublePlayerChoice);
}

void initializeGame(int players, char mode, char player1Name[50], char player2Name[50])
{
    game.points = players;
    game.mode = mode;
    strcpy(game.player1Name, player1Name);
    strcpy(game.player2Name, player2Name);
    game.numberOfPlays = 0;
    game.player1Wins = 0;
    game.player2Wins = 0;
    game.draws = 0;
}

int main()
{
    gameplay();

    return 0;
}