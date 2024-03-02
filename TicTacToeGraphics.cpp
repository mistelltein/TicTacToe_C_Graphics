#include<graphics.h>
#include<stdio.h>
#include "TicTacToe.h"
#include "TicTacToeLogic.cpp"

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

void drawButtonPlay(int x, int y, char* label) {
    setcolor(15);
    rectangle(x, y, x + 150, y + 40);
    outtextxy(x + 75, y + 5, label);
}

