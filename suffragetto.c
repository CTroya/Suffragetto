#include "suffragetto.h"
#include <stdio.h>
#include <gtk/gtk.h>
/*Retorna un numero random para definir que bando comienza la partida
*/
int coinFlip( int range){
	static int xd = 0;
	(xd == 0)? srand(time(NULL)):1;
	xd++;
	return rand()%(range+1);
}

int cpuPlay(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],char piece){
    FILE *cpuPanel = fopen("moveLog.cop","a+");
	puntMovecpu = &moveCounterAi;
    aiPiece = piece;
    int coord[4];
    char a;
    do{
        for(int i = 0;i < 4; i++)
            coord[i] = coinFlip(16);
    }while(checkJugada(coord,board,colorBoard,piece) == false);
    fprintf(cpuPanel,"%c %d-%c %d",coord[1]+ 'A',coord[0]+1,coord[3] + 'A',coord[2]+1);    
    printf("\n%c %d - %c %d\n",coord[1]+ 'A',coord[0]+1,coord[3] + 'A',coord[2]+1);
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    int isJump = isJumpable(board,colorBoard,coord,piece);
    int eaten = board[midPosicI][midPosicJ];
    a = board[coord[0]][coord[1]];
    board[coord[0]][coord[1]] = blank;
    board[coord[2]][coord[3]] = a;
    board[midPosicI][midPosicJ] = (isJump == 2)? blank: board[midPosicI][midPosicJ];
    (isJump == 2)? rehab(eaten,board,colorBoard): 1;
    if(isJump){
        consecJump(board,colorBoard,coord,piece);//WIP
        fprintf(cpuPanel,"-%c %d - %c %d",coord[1]+ 'A',coord[0]+1,coord[3] + 'A',coord[2]+1);
        fprintf(cpuPanel,"|%d\n",moveCounterAi++);
    }
    else{
        fprintf(cpuPanel,"|%d\n",moveCounterAi++);
    }
    fclose(cpuPanel);
}
/*Menu principal
*/
void mainMenu(void){
    int pause;
    printf("\n                                                                                                 ");
    printf("Menu Principal:\n");
    printf("                                                                                           ");
   // printf("(Se recomienda activar los sonidos ^^)");
    printf("\n                                                                                           ");
    printf("1.Jugar");
    printf("\n                                                                                           ");
    printf("2.Ver el lore y reglas");
    printf("\n                                                                                           ");
    printf("3.Creditos");
    int c = getInt("\n                                                                                           :",1,3);
    switch (c){
        case 1:
            break;
        case 2:
            system("clear");
            banner("banner.txt");
            banner("rulesnlore.txt");
            printf("\nPress ENTER to continue.");
            pause = getchar();
        break;
        case 3:
            system("clear");
            banner("banner.txt");
            banner("credits.txt");
            printf("\nPress ENTER to continue.");
            pause = getchar();
        break;
    }
}
/*Pide al usuario la configuracion de su partida
option = Determina el modo de juego cpu vs humano, humano vs humano etc...
        1. PvsCPU
        2. PvP
        3. CPUvsCPU
optionPiece = Indica que bando quiere elige el usuario
        1. Suffragette
        2. Policias
        3. Todo Aleatorio
optionStart = Indica que bando empieza
        1.Suffragette
        2.Policias
        3.Aleatorio
*/
#define HvsCpu 1
#define HvsH 2
#define CpuvsCpu 3
#define suff 1
#define cop 2
#define random 3
#define suffInit 1
#define copInit 2
#define randInit 3

int gameMenu(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4]){
    int optionMode = 0, optionPiece = 0, optionStart = 0;
    system("clear");
    banner("banner.txt");
    printf("                                                                                                    Menu del Juego:\n");
    printf("                                                                                           1.Modo Humano vs Computadora\n");
    printf("                                                                                           2.Modo Humano vs Humano\n");
    printf("                                                                                           3.Modo Computadora vs Computadora\n");
    optionMode = getInt("                                                                                           :",1,3);
    if(optionMode == HvsCpu){
        system("clear");
        banner("banner.txt");
        printf("                                                                                                Elige tu bando: ^^\n");
        printf("                                                                                           1.Suffragettes\n");
        printf("                                                                                           2.Policias\n");
        printf("                                                                                           3.Aleatorio\n");
        optionPiece = getInt("                                                                                           :",1,3);
    }
    system("clear");
    banner("banner.txt");
    if(optionMode == HvsCpu && optionPiece == random){
        playingTime(board,colorBoard,coord,coinFlip(3));
        return 0;
    }
    printf("                                                                                                    Elige que bando quieres que empiece: ^^\n");
    printf("                                                                                           1.Suffragettes\n");
    printf("                                                                                           2.Policias\n");
    printf("                                                                                           3.Aleatorio\n");
    optionStart = getInt("                                                                                           :",1,3);
    system("clear");
    banner("banner.txt");
    if(optionMode == HvsH && optionStart == random){
        playingTime(board,colorBoard,coord,coinFlip(1)+4);
        return 0;
    }
    if(optionMode == CpuvsCpu && optionStart == random){
        playingTime(board,colorBoard,coord,coinFlip(1)+6);
        return 0;
    }
    //Chicos, pueden apreciar la belleza de esta ecuacion diferencial? - Omar Romero xD
    //HvsCpu
    (optionMode == HvsCpu && optionStart == suff && optionPiece == suff)? playingTime(board,colorBoard,coord,0): NULL;
    (optionMode == HvsCpu && optionStart == cop  && optionPiece == cop)? playingTime(board,colorBoard,coord,1): NULL;
    (optionMode == HvsCpu && optionStart == suff && optionPiece == cop)? playingTime(board,colorBoard,coord,2): NULL;
    (optionMode == HvsCpu && optionStart == cop  && optionPiece == suff)? playingTime(board,colorBoard,coord,3): NULL;
    //HvsH
    (optionMode == HvsH && optionStart == suff)? playingTime(board,colorBoard,coord,4): NULL;
    (optionMode == HvsH && optionStart == cop)? playingTime(board,colorBoard,coord,5): NULL;
    //CpuvsCpu
    (optionMode == CpuvsCpu && optionStart == suff)? playingTime(board,colorBoard,coord,6): NULL;
    (optionMode == CpuvsCpu && optionStart == cop)? playingTime(board,colorBoard,coord,7): NULL;
}
//Inicializa los valores de los arrays que representan al tablero
void initBoard(int colorBoard[boardSize][boardSize],int piecesBoard[boardSize][boardSize]){
    
    for(int i = 0; i<boardSize;i++){
        for(int j = 0; j<boardSize;j++){//Esto podria optimizar mas tarde
            piecesBoard[i][j] = blank;//Llena de blanks el array de fichas
            if(j > 3 || j < 13){
                colorBoard[i][j] = red;
            }
            if(j > 0 && j < 3 || j > 13 && j < 16 ){
                colorBoard[i][j] = yellow;
            }
            if(j == 0 || j == 16 ){
                colorBoard[i][j] = (j == 0)? Hospital: Prison;
            }
            if(j > 6 && j < 10){
                colorBoard[i][j] = (i == 3 || i == 4)? albertHall:(i == 12 || i == 13)? commonHouse: red;
            }
            if(j == 1 || j == 15){
               colorBoard[i][j] = (i <= 5 && j == 15)? prisonYard:(i >= 11 && j == 1)? hospitalGrounds: yellow;
            }
            if(j == 1 && i < 4 || j == 15 && i > 12){
                colorBoard[i][j] = (j == 1)? Hospital: Prison;
            }
        }
    //Inicializamos el tablero de fichas
    }
    for(int i = 3; i < 6;i++){
        for(int j = 0; j < boardSize;j++){
            if(j > 1 && j < 15){
                piecesBoard[i][j] = (i == 3 && j > 5 && j < 11 && colorBoard[i][j] != albertHall)? suffPiece: blank;
                
                if(i == 4 && j > 3 && j < 13 && colorBoard[i][j] != albertHall){
                    piecesBoard[i][j] = (j % 4 == 0)? suffLeader: suffPiece;
                }
                if(i == 5 && j > 1 && j < 15){
                    piecesBoard[i][j] = (j == 2 || j == 8 || j == 14)? suffLeader: suffPiece;
                }
            }
        }        
    }
    for(int i = 11; i < 16;i++){
        for(int j = 0; j < boardSize;j++){
            if(j > 1 && j < 15){
                piecesBoard[i][j] = (i == 13 && j > 5 && j < 11 && colorBoard[i][j] != commonHouse)? copPiece: blank;
                
                if(i == 12 && j > 3 && j < 13 && colorBoard[i][j] != commonHouse){
                    piecesBoard[i][j] = (j % 4 == 0)? copLeader: copPiece;
                }
                if(i == 11 && j > 1 && j < 15){
                    piecesBoard[i][j] = (j == 2 || j == 8 || j == 14)? copLeader: copPiece;
                }
            }
        }        
    }
    rehab(3,piecesBoard,colorBoard);
}

//Imprime el tablero en el terminal con colores y demas! :D
void printBoard(int colorBoard[boardSize][boardSize],int piecesBoard[boardSize][boardSize]){
    int *pieceCounterArr = countPieces(piecesBoard,colorBoard);
    printf("                                                                                      Total de Suffragettes en partida: %d\n",pieceCounterArr[0]);
    printf("                                                                                      Total de Policias en partida: %d\n",pieceCounterArr[1]);
    printf("\n                                      			    A    B    C    D    E    F    G    H    I    J    K    L    M    N    O    P    Q");
    for(int i=0;i<boardSize;i++){
        printf("\n");
        for(int j=0; j<boardSize;j++){
             if (j == 0 && i < 9) {
                printf("                                      			%d-", i+1);
            }
            if(j == 0 && i >= 9){
                printf("                                      		       %d-", i+1);
            }
            if(piecesBoard[i][j] == blank){//Casilla vacia
                switch (colorBoard[i][j]){
                    case red:
                        printf(ANSI_COLOR_RED "|███|"ANSI_COLOR_RESET);;
                        break;
                    case yellow:
                        printf(ANSI_COLOR_YELLOW"|███|"ANSI_COLOR_RESET);
                        break;
                    case Hospital: case Prison:
                        printf(ANSI_COLOR_BLUE"|███|"ANSI_COLOR_RESET);
                        break;
                    case prisonYard: case hospitalGrounds:
                        printf(ANSI_COLOR_GREEN"|███|"ANSI_COLOR_RESET);
                        break;
                    case albertHall: case commonHouse:
                        printf(ANSI_COLOR_BLACK"|███|"ANSI_COLOR_RESET);
                        break;
                }
            }
            if(piecesBoard[i][j] == suffPiece){//Sufragette
                switch (colorBoard[i][j]){
                case red:
                    printf(ANSI_COLOR_RED"|█"ANSI_COLOR_GREENB"█"ANSI_COLOR_RED"█|"ANSI_COLOR_RESET);
                    break;
                case yellow:
                   printf(ANSI_COLOR_YELLOW"|█"ANSI_COLOR_GREENB"█"ANSI_COLOR_YELLOW"█|"ANSI_COLOR_RESET);
                    break;
                case Hospital: case Prison:
                    printf(ANSI_COLOR_BLUE"|█"ANSI_COLOR_GREENB"█"ANSI_COLOR_BLUE"█|"ANSI_COLOR_RESET);
                    break;
                case prisonYard: case hospitalGrounds:
                    printf(ANSI_COLOR_GREEN"|█"ANSI_COLOR_GREENB"█"ANSI_COLOR_GREEN"█|"ANSI_COLOR_RESET);
                    break;
                case albertHall: case commonHouse:
                    printf(ANSI_COLOR_WHITE"|█"ANSI_COLOR_GREENB"█"ANSI_COLOR_WHITE"█|"ANSI_COLOR_RESET);
                    break;
                }
            }
            if(piecesBoard[i][j] == suffLeader){//Lider Suffragette
                switch (colorBoard[i][j]){
                case red:
                    printf(ANSI_COLOR_RED"|█"ANSI_COLOR_MAGENTA"█"ANSI_COLOR_RED"█|"ANSI_COLOR_RESET);
                    break;
                case yellow:
                   printf(ANSI_COLOR_YELLOW"|█"ANSI_COLOR_MAGENTA"█"ANSI_COLOR_YELLOW"█|"ANSI_COLOR_RESET);
                    break;
                case Hospital: case Prison:
                    printf(ANSI_COLOR_BLUE"|█"ANSI_COLOR_MAGENTA"█"ANSI_COLOR_BLUE"█|"ANSI_COLOR_RESET);
                    break;
                case prisonYard: case hospitalGrounds:
                    printf(ANSI_COLOR_GREEN"|█"ANSI_COLOR_MAGENTA"█"ANSI_COLOR_GREEN"█|"ANSI_COLOR_RESET);
                    break;
                case albertHall: case commonHouse:
                    printf(ANSI_COLOR_BLACK"|█"ANSI_COLOR_MAGENTA"█"ANSI_COLOR_BLACK"█|"ANSI_COLOR_RESET);
                    break;
                }
            }
            if(piecesBoard[i][j] == copPiece){//Policia
                switch (colorBoard[i][j]){
                case red:
                    printf(ANSI_COLOR_RED"|█"ANSI_COLOR_CYAN"█"ANSI_COLOR_RED"█|"ANSI_COLOR_RESET);
                    break;
                case yellow:
                   printf(ANSI_COLOR_YELLOW"|█"ANSI_COLOR_CYAN"█"ANSI_COLOR_YELLOW"█|"ANSI_COLOR_RESET);
                    break;
                case Hospital: case Prison:
                    printf(ANSI_COLOR_BLUE"|█"ANSI_COLOR_CYAN"█"ANSI_COLOR_BLUE"█|"ANSI_COLOR_RESET);
                    break;
                case prisonYard: case hospitalGrounds:
                    printf(ANSI_COLOR_GREEN"|█"ANSI_COLOR_CYAN"█"ANSI_COLOR_GREEN"█|"ANSI_COLOR_RESET);
                    break;
                case albertHall: case commonHouse:
                    printf(ANSI_COLOR_BLACK"|█"ANSI_COLOR_CYAN"█"ANSI_COLOR_BLACK"█|"ANSI_COLOR_RESET);
                    break;
                }
            }
            if(piecesBoard[i][j] == copLeader){//Policia Lider
                switch (colorBoard[i][j]){
                case red:
                    printf(ANSI_COLOR_RED"|█"ANSI_COLOR_WHITE"█"ANSI_COLOR_RED"█|"ANSI_COLOR_RESET);
                    break;
                case yellow:
                   printf(ANSI_COLOR_YELLOW"|█"ANSI_COLOR_WHITE"█"ANSI_COLOR_YELLOW"█|"ANSI_COLOR_RESET);
                    break;
                case Hospital: case Prison:
                    printf(ANSI_COLOR_BLUE"|█"ANSI_COLOR_WHITE"█"ANSI_COLOR_BLUE"█|"ANSI_COLOR_RESET);
                    break;
                case prisonYard: case hospitalGrounds:
                    printf(ANSI_COLOR_GREEN"|█"ANSI_COLOR_WHITE"█"ANSI_COLOR_GREEN"█|"ANSI_COLOR_RESET);
                    break;
                case albertHall: case commonHouse:
                    printf(ANSI_COLOR_BLACK"|█"ANSI_COLOR_WHITE"█"ANSI_COLOR_BLACK"█|"ANSI_COLOR_RESET);
                    break;
                }
            }
        } 
        printf("\n");
    }
    printf("\n                                                                                  Total de Suffragettes en House Of Commons: %d\n",pieceCounterArr[2]);
    printf("                                                                                  Total de Policias en Albert Hall: %d\n",pieceCounterArr[3]);
}

//Funcion con error handling que pide al usuario una letra entre A y Q
char getChar(const char *prompt){//Tal vez deba cambiar el naming scheme e incluir limites minimos y maximos
    char c,b;
    int ioCounter = 0;
    
    do{
        if(ioCounter > 0) while(getchar() != '\n');
        printf("%s",prompt);
        c = getchar();
        b = getchar();
        c = toupper(c);
        ioCounter++;
    }while(b != '\n'|| 'A' > c || c > 'Q');
    prompt = NULL;
    return c;
}

/*Pide un entero al usuario
char Prompt: La cadena que se imprimira al pedir input
int minRange: El menor valor aceptado
int maxRange: EL mayor valor aceptado
*/
int getInt(const char *prompt, int minRange, int maxRange){// me interesa el formato int getInt(const char *prompt,...)
    char input[9];
    char numInt, c;
    int ioCounter = 0,ret;
    do{
        if(ioCounter > 0 ) while(getchar()!='\n'); //Limpia el buffer si hubo errores
            printf("%s",prompt);
            ret = scanf("%9[0-9-]s",input);
            ioCounter++;
            numInt = atoi(input);
    }while( numInt < minRange || numInt > maxRange || (c =getchar())!='\n'|| c == EOF|| ret!= 1);
   // printf("%d",numInt);
    prompt = NULL;
    return numInt;
}

//Retorna falso o verdadero dependiendo si se puede comer o no
int eat(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],char piece){
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    if(colorBoard[midPosicI][midPosicJ] == yellow || colorBoard[midPosicI][midPosicJ] == albertHall || colorBoard[midPosicI][midPosicJ]== commonHouse){
        return false;
    }else{
        char eaten = board[midPosicI][midPosicJ];
        if(board[coord[0]][coord[1]] == suffLeader){
            if(board[midPosicI][midPosicJ] == copPiece || board[midPosicI][midPosicJ]==copLeader){
                return 1;
            }
        }
        if(board[coord[0]][coord[1]] == suffPiece){
            if((board[midPosicI][midPosicJ] == copPiece || board[midPosicI][midPosicJ] == copLeader)&& abs(diffI) == abs(diffJ)){
                return 1;
            }
        }
        if(board[coord[0]][coord[1]] == copLeader){
            if(board[midPosicI][midPosicJ] == suffLeader || board[midPosicI][midPosicJ] == suffPiece ){
                return 1;
            }
        }
        if(board[coord[0]][coord[1]] == copPiece){
            if((board[midPosicI][midPosicJ] == suffPiece || board[midPosicI][midPosicJ] == suffLeader)&& abs(diffI) == abs(diffJ)){
                return 1;
            }
        }
    }
    return 0;
}
//Pone las fichas heridas en sus respectivas casillas
void rehab(int piece, int board[boardSize][boardSize], int colorBoard[boardSize][boardSize]){
    static int ocupatedHospital = 16;//El hospital se llena de abajo a arriba
    static int ocupatedPrison = 0;//La prision se llena de arriba a abajo
    //Codigo de reset
    if(piece == 3){
        ocupatedHospital = 16;
        ocupatedPrison = 0;
    }else{
    /*
        Si la pieza capturada es una suffragette, va a la carcel
        Si es un policia, va al hospital
    */
    if(piece == suffLeader || piece == suffPiece){//Hay que checkear de nuevo los statics cuando se tradeen piezas asdasdas
        if(ocupatedPrison < boardSize){
            board[ocupatedPrison][16] = piece;
            ocupatedPrison++;
        }else{
            ocupatedPrison--;
            board[ocupatedPrison][15] = piece;
        }
    }
    if(piece == copLeader || piece == copPiece){
        if(ocupatedHospital >= 0){
            board[ocupatedHospital][0] = piece;
            ocupatedHospital--;
        }else{
            ocupatedHospital++;
            board[ocupatedHospital][1] = piece;
        }
    }
    }
}
// retorna 0 si no es salto, 1 si es, 2 si es una captura tb xD
int isJumpable(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],char piece){
    bool isValid = false;
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    //-midPosic es la coordenada de la pieza a la que se quiere saltar
    isValid = (board[midPosicI][midPosicJ] == blank)? false: true;
    isValid = (diffI == 0 && diffJ == 0)? false: isValid;
    int isEatable = (isValid == true)? eat(board,colorBoard,coord,piece): 0;
    return isValid+isEatable;
}

int consecJump(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],char piece){//WIP
    char piezaQueSaltaxD = board[coord[2]][coord[3]]; int avJumps;
    static int jumperCounter = 0;
    static int origI,origJ;
    //printf("%d",jumperCounter);
    int auxCoord[4] = {coord[0],coord[1],coord[2],coord[3]};
    //Las posiciones de destino se vuelven las de origen, porque la pieza ya se movio
    if(jumperCounter == 0){
        origI = coord[0];
        origJ = coord[1];
    }
    coord[0] = coord[2];
    coord[1] = coord[3];
   if((avJumps = jumpCounter(board,colorBoard,auxCoord,piece))<= 0){
        (aiPiece != piece)? printf("\nNo tienes saltos disponibles, acabo tu turno\n"):1;
    	jumperCounter = 0;
        return 0;
	}
    //Ahora pedimos una nueva coordenada de destino
    if(piece != aiPiece){
        printf("\nHas saltado una pieza!\nA donde la quieres mover otra vez? Puedes dejarla ahi insertando la misma coordenada ^^\n");
        printf("Tienes %d saltos posibles!\n",avJumps);
        //printBoard(colorBoard,board);
    }
    if(piece != aiPiece){
        do{
            //coord[3] = getChar("Inserte la posicion de Columna a mover(Letra): ")-'A';
            //coord[2] = getInt("Inserte la posicion de Fila a mover(Numero): ",0,17)-1;
            if(coord[0] == coord[2] && coord[1] == coord[3]) break;
        }while(checkJugada(coord,board,colorBoard,piece) == false || isJumpable(board,colorBoard,coord,piece) == false||
               coord[2] == origI && coord[3] == origJ);
    }else{
         do{
            coord[3] = coinFlip(16);
            coord[2] = coinFlip(16);
            if(coord[0] == coord[2] && coord[1] == coord[3]) break;
        }while(checkJugada(coord,board,colorBoard,piece) == false || isJumpable(board,colorBoard,coord,piece) == false|| 
               coord[2] == origI && coord[3] == origJ);
    }
    int bruh,limit = 0;
    bruh = eat(board,colorBoard,coord,piece);
    if(piece == aiPiece && coord[0] != coord[2] && coord[1] != coord[3]) printf("La computadora salto a %c-%d\n",coord[3]+'A',coord[2]+1);
    if(piece == aiPiece && coord[0] == coord[2] && coord[1] == coord[3]) printf("La computadora se quedo en %c-%d\n",coord[3]+'A',coord[2]+1);
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    int eaten = board[midPosicI][midPosicJ];
    board[coord[0]][coord[1]] = blank; //La casilla de origen queda vacia al moverse la pieza
    board[coord[2]][coord[3]] = piezaQueSaltaxD; //La pieza ocupa el lugar de destino
    board[midPosicI][midPosicJ] = (bruh == 1)? blank: board[midPosicI][midPosicJ];
    (bruh == 1)? rehab(eaten,board,colorBoard): 1;
    if(jumperCounter <= limit && board[coord[0]][coord[1]] != board[coord[2]][coord[3]]){
        jumperCounter++;
		consecJump(board,colorBoard,coord,piece);//Si es un salto de nuevo, la funcion se llama recursivamente ^^
    }else{
    	jumperCounter = 0;
        printf("\nFin de saltos consecutivos\n");
	}
}

/*Verifica que la jugada sea valida
  int coord[4]: indices 0 y 1 coordenadas de origen - 2 y 3 coordenadas de destino
  Retorna 1 si la jugada es valida, 0 si no lo es
*/
int checkJugada(int coord[4],int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],char piece){
    bool isValid = false;
    int absDiffI = abs(coord[0]-coord[2]);
    int absDiffJ = abs(coord[1]-coord[3]);
    //No se puede seleccionar una pieza vacia
    if(board[coord[0]][coord[1]] == blank ||colorBoard[coord[0]][coord[1]] == Prison||colorBoard[coord[0]][coord[1]] == Hospital){
        return isValid;
    }
    if (colorBoard[coord[2]][coord[3]] == albertHall && piece == suffPiece ||
        piece == copPiece && colorBoard[coord[2]][coord[3]] == commonHouse){
        return false;
    }
    if(piece == suffPiece && board[coord[0]][coord[1]] == copPiece || piece == suffPiece && board[coord[0]][coord[1]]==copLeader||
        piece == copPiece && board[coord[0]][coord[1]]==suffPiece||piece == copPiece && board[coord[0]][coord[1]]==suffLeader)
        return isValid;
    //Chequeo de zonas prohibidas 
    if(colorBoard[coord[2]][coord[3]] == hospitalGrounds ||colorBoard[coord[2]][coord[3]] == prisonYard ||
        colorBoard[coord[2]][coord[3]] == Hospital || colorBoard[coord[2]][coord[3]] == hospitalGrounds||
        colorBoard[coord[2]][coord[3]] == Prison || colorBoard[coord[0]][coord[1]] == albertHall && colorBoard[coord[2]][coord[3]] != albertHall||
        colorBoard[coord[0]][coord[1]] == commonHouse && colorBoard[coord[2]][coord[3]] != commonHouse){
        return isValid;
    }
    if(absDiffI <= 1 && absDiffJ <= 1){
        isValid = (board[coord[2]][coord[3]] == blank)? true: false;
    }else{
        if(absDiffI == 2 && absDiffJ == 2 || absDiffI == 0 && absDiffJ == 2 || absDiffI == 2 && absDiffJ == 0 ){
            isValid = (board[coord[2]][coord[3]] != blank)? false: isJumpable(board,colorBoard,coord,piece);
        }
    }
    return isValid;
}


/*Pide coordenadas de origen y destino y transforma los datos recibidos a indices del array de piezas.
 -int coord[4]: el array donde se guardaran los datos introducidos por el usuario
 -Indices: 0 y 1 coordenadas de origen, 2 y 3 coordenadas de destino
*/
void inputCoord(int coord[4]){
    coord[1] = getChar("Inserte la posicion de Columna a seleccionar(Letra): ")-'A';
    coord[0] = getInt("Inserte la posicion de Fila a seleccionar(Numero): ",0,17)-1;
    coord[3] = getChar("Inserte la posicion de Columna a mover(Letra): ")-'A';
    coord[2] = getInt("Inserte la posicion de Fila a mover(Numero): ",0,17)-1;
}

/*Realiza la jugada si es valida, de no serla, vuelve a llamar a inputCoord()
int coord: array donde se guardan los datos que son introducidos por el usuario
int board: array donde se guardan las piezas y su posicion dentro del tablero
int colorboard: array donde se guardan las zonas del tablero
const char piece: funcion que indica el bando que realiza la jugada
*/
void makePlay(int coord[],int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],const char piece){
    int a;

    //Este array guardara los lugares en donde el jugador ya haya pasado a fin de filtrar saltos consecutivos en posiciones
    //ya jugadas durante el turno
    if(piece == suffPiece)printf("\nTurno de las Suffragettes!\n");
    if(piece == copPiece)printf("\nTurno de los policias!\n");
    do{
        inputCoord(coord);
    }while(checkJugada(coord,board,colorBoard,piece) == false);
    //1 es salto, 2 es captura, 0 no es salto ni captura
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    int isJump = isJumpable(board,colorBoard,coord,piece);
    int eaten = board[midPosicI][midPosicJ];
    a = board[coord[0]][coord[1]];
    board[coord[0]][coord[1]] = blank;
    board[coord[2]][coord[3]] = a;
    board[midPosicI][midPosicJ] = (isJump == 2)? blank: board[midPosicI][midPosicJ];
    (isJump == 2)? rehab(eaten,board,colorBoard): 1;
    if(isJump > 0){
        consecJump(board,colorBoard,coord,piece);//WIP
    }
}
/*Cuenta las jugadas
  //counter[0]: contador de suffragettes
  //counter[1]: contador de policias
  //counter[2]: contador de Suffragettes en House of Commons
  //counter[3]: contador de Policias en Albert Hall 
*/
int *countPieces(int board[boardSize][boardSize], int colorBoard[boardSize][boardSize]){
    
    static int counter[4] = {0,0,0,0};
    int counterSuff = 0, counterCop = 0, counterSuffWins = 0, counterCopWins = 0;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            (board[i][j] == suffPiece && colorBoard[i][j] != Prison ||
             board[i][j] == suffLeader && colorBoard[i][j] != Prison)? counterSuff++:1;

            (board[i][j] == copPiece && colorBoard[i][j] != Hospital || 
             board[i][j] == copLeader && colorBoard[i][j] != Hospital)? counterCop++:1;

            (colorBoard[i][j] == albertHall && board[i][j] != blank)? counterCopWins++:1;
            (colorBoard[i][j] == commonHouse && board[i][j] != blank)? counterSuffWins++:1;
        }
    }
    counter[0] = counterSuff;
    counter[1] = counterCop;
    counter[2] = counterSuffWins;
    counter[3] = counterCopWins;
    return counter;
}
//Cuenta las piezas que estan dentro de AlbertHall o House of Commons

/*Es la funcion que se encargara de llamar a las funciones de jugar piezas
    dice 0: suffH vs copPc
    dice 1: copH vs suffPc
    dice 2: suffPc vs copH
    dice 3: copPc vs suffH
    dice 4: suffH vs copH
    dice 5: copH vs suffH
    dice 6: suffPc vs copPc
    dice 7: copPc vs suffPc
*/
void playingTime(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],int dice){
    int *counter = countPieces(board,colorBoard);

    switch (dice){
        case 0://suffH vs copPc
            do{
                printBoard(colorBoard,board);
                makePlay(coord,board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                cpuPlay(board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 1://copH vs suffPc
            do{
                printBoard(colorBoard,board);
                makePlay(coord,board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                cpuPlay(board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 2://suffPc vs copH
            do{
                cpuPlay(board,colorBoard,suffPiece);
                printBoard(colorBoard,board);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                makePlay(coord,board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 3://copPc vs suffH
            do{
                cpuPlay(board,colorBoard,copPiece);
                printBoard(colorBoard,board);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                makePlay(coord,board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 4://suffH vs copH
            do{
                printBoard(colorBoard,board);
                makePlay(coord,board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                printBoard(colorBoard,board);
                makePlay(coord,board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 5://copH vs suffH
            do{
                printBoard(colorBoard,board);
                makePlay(coord,board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                printBoard(colorBoard,board);
                makePlay(coord,board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 6://suffPc vs copPc
        do{
                printBoard(colorBoard,board);
                printf("\nTurno de las Suffragettes!\n");
                cpuPlay(board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                printBoard(colorBoard,board);
                printf("\nTurno de los policias!\n");
                cpuPlay(board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
        case 7://copPc vs suffPc
            do{
                printBoard(colorBoard,board);
                printf("\nTurno de los policias!\n");
                cpuPlay(board,colorBoard,copPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
                printBoard(colorBoard,board);
                printf("\nTurno de las Suffragettes!\n");
                cpuPlay(board,colorBoard,suffPiece);
                counter = countPieces(board,colorBoard);
                if(counter[0] < 6 || counter[1] < 6 || counter[2] >= 6 || counter[3] >= 6) break;
            }while(1);
            break;
    }
    printBoard(colorBoard,board);
    if(getWinner(counter) == 1)
        printf("\nGanan las suffragettes!\n");
    else  
        printf("\nGanan los policias!\n");
}

int getWinner(int *counter){
    if(counter[0] < 6 || counter[3] >= 6)//policias ganan    
        return 0;
    if(counter[1] < 6 || counter[2] >= 6)//suffragettes ganan
        return 1;
}


int jumpCounter(int board[boardSize][boardSize], int colorBoard[boardSize][boardSize], int coord[4],char piece){
    int diffI = (coord[2]-coord[0])/2;
    int diffJ = (coord[3]-coord[1])/2;
    int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;
    int jumpCounter, auxCoord[4] = {coord[2],coord[3]};
    jumpCounter = (board[midPosicI][midPosicJ] == blank)? 0: -1;;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            auxCoord[2] = i;
            auxCoord[3] = j;
            if(isJumpable(board,colorBoard,auxCoord,piece) && checkJugada(auxCoord,board,colorBoard,piece)){
                jumpCounter++;
            }
        }
    }
    return jumpCounter;
}

/*Printea archivos de texto
*/
void banner(const char* prompt) {
    int i=0;
    printf(ANSI_COLOR_RESET);
    FILE * title;
    int c,end;
    int counter = 0;
    end = 1215;
    title = fopen(prompt, "r");
    c = fgetc(title);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(title);
        }
    fclose(title);
    printf("\033[0m");
    printf("\n"ANSI_COLOR_YELLOW);
}

