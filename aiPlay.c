#include "suffragetto.h"
#include "math.h"
//Retorna las coordenadas de la mejor jugada que el algoritmo saque (?)
//
#define playQuant 168
int power(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2)
        return base * power(base, exp - 1);
    else {
        int temp = power(base, exp / 2);
        return temp * temp;
    }
}

int aiPlay(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize], char side){
    FILE *cpuPanel = fopen("moveLog.cop","a+");
    int movesCounter = 0;
	puntMovecpu = &moveCounterAi;
    int albertHallI = 13 + coinFlip(1);
    int albertHallJ = 8 + power(-1,coinFlip(2))*coinFlip(1); 
    int houseI = 3 + coinFlip(1);
    int houseJ = 8 + power(-1,coinFlip(2))*coinFlip(1);
    int enemyBaseI;
    int enemyBaseJ;
    int enemyBase;
    int origI = 9999,origJ = 9999;
    if(side == copPiece||side == copLeader){
       enemyBaseI = houseI;
       enemyBaseJ = houseJ;
       enemyBase = albertHall;
    }
    if(side == suffPiece){
       enemyBaseI = albertHallI;
       enemyBaseJ = albertHallJ;
       enemyBase = commonHouse;
    }
    int flag;
    int potJumps[playQuant];
    int coord[playQuant][4] = {0};
    int moveType[playQuant] = {0};
    int scores[playQuant] = {0};
    int distI[playQuant];
    int distJ[playQuant];
    int maxScore = 0;
    int maxScoreInd;
    int start = 0;
    int end = 4;
    int tsusume;
    int conditions[2];
    while(movesCounter < 3){
        for(int i = 0; i < playQuant; i++){
            do{
                for(int j = start;j < end; j++){
                    coord[i][j] = coinFlip(16);
                }
                conditions[0] = checkJugada(coord[i],board,colorBoard,side) == false || (colorBoard[coord[i][0]][coord[i][1]] == albertHall || colorBoard[coord[i][0]][coord[i][1]] == commonHouse);
                conditions[1] = checkJugada(coord[i],board,colorBoard,side) == false || isJumpable(board,colorBoard,coord[i],side) == false|| coord[i][2] == origI && coord[i][3] == origJ;
                conditions[2] = checkJugada(coord[i],board,colorBoard,side) == false || isJumpable(board,colorBoard,coord[i],side) == false|| coord[i][2] == origI && coord[i][3] == origJ;
            }while(conditions[movesCounter]);
            distI[i] = abs(enemyBaseI - coord[i][2]);
            distJ[i] = abs(enemyBaseJ - coord[i][3]);
            potJumps[i] = jumpCounter(board,colorBoard,coord[i],side);
            moveType[i] = isJumpable(board,colorBoard,coord[i],side);
            tsusume = (coord[i][0] == coord[i][2]);
            scores[i] = 200 - distI[i] - distJ[i] + moveType[i]*20 + potJumps[i]*5 -tsusume;
        }
        for(int i = 0; i < 168;i++){
            if(scores[i] > maxScore){
                maxScore = scores[i];
                maxScoreInd = i;
            }
        }
        int *coordOut = coord[maxScoreInd];
        if(movesCounter == 0){
            origI = coordOut[0];
            origJ = coordOut[1];
        }
        fprintf(cpuPanel,"%c %d-%c %d",coordOut[1]+ 'A',coordOut[0]+1,coordOut[3] + 'A',coordOut[2]+1); 

        int diffI = (coordOut[2]-coordOut[0])/2;
        int diffJ = (coordOut[3]-coordOut[1])/2;
        int midPosicI = coordOut[0] + diffI, midPosicJ = coordOut[1] + diffJ;
        int isJump = isJumpable(board,colorBoard,coordOut,side);
    
        int eaten = board[midPosicI][midPosicJ];
        char a = board[coordOut[0]][coordOut[1]];
        board[coordOut[0]][coordOut[1]] = blank;
        board[coordOut[2]][coordOut[3]] = a;
        board[midPosicI][midPosicJ] = (isJump == 2)? blank: board[midPosicI][midPosicJ];
        (isJump == 2)? rehab(eaten,board,colorBoard): 1;
        g_print(ANSI_COLOR_RED"\nAISUPERFACHERA: %c-%d %c-%d\nmoveCounter:%d\n",coordOut[1]+'A',coordOut[0]+1,coordOut[3]+'A',coordOut[2]+1,movesCounter);
        movesCounter++;
        updateBoardGtk(colorBoard,board);
        if(colorBoard[coordOut[2]][coordOut[3]] == enemyBase) {
            fprintf(cpuPanel,"|%d\n",moveCounterAi++);
            return 1;
        }
        if(colorBoard[coord[maxScoreInd][2]][coord[maxScoreInd][3]] == enemyBase){
            fprintf(cpuPanel,"|%d\n",moveCounterAi++);
            return 1;
        }
        //if(colorBoard[coord[maxScoreInd][0]][coord[maxScoreInd][1]]) return 1;
        if(isJump && jumpCounter(board,colorBoard,coordOut,side)){
            start = 2;
            end = 4;
            for(int i = 0; i < playQuant;i++){
                coord[i][0] = coord[maxScoreInd][2];
                coord[i][1] = coord[maxScoreInd][3];
                int origI = coord[i][0];
                int origJ = coord[i][1];
            }
        }
        else{
            fprintf(cpuPanel,"|%d\n",moveCounterAi++);
            break;
        }
        printBoard(colorBoard,board);
    }
 
    fclose(cpuPanel);

    return 0;
}
