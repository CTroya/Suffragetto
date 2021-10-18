//Un vector de Strings, almacena ubicacio ,m .n de imagenes

#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <gtk/gtk.h>

//ost.raw Sample rate: 32000hz
//defines para marcarpiezas() 
#define todos 0
#define saltos 1


//Dimensiones del tablero
#define boardSize 17

//Piezas de suffragettes
#define suffPiece 's'
#define suffLeader 'S'

//Casilla no ocupada
#define blank 0

//Piezas de policia
#define copPiece 'c'
#define copLeader 'C'

//Zonas del tablero
#define red 94
#define yellow 176
#define green 177
#define purple 178
#define commonHouse 2000
#define albertHall 2001
#define prisonYard 2002
#define hospitalGrounds 2003
#define Hospital 2004
#define Prison 2005



//Colores de print
#define ANSI_COLOR_BLACK "\e[30m"
#define ANSI_COLOR_RED   "\e[0;31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_GREENB "\e[1;92m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE  "\e[0;34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_MAGENTAB "\e[1;95m"
#define ANSI_COLOR_CYAN  "\x1b[36m"
#define ANSI_COLOR_RESET "\e[0;33m"
#define ANSI_COLOR_WHITE "\e[0;37m"

//Misc
#define ERROR -9999
#define width 0
#define height 0
//#define ANSI_COLOR_RESET   "\x1b[0m" originalmente blanco pero quiero amarillo uwu "\x1b[36m"

//GTK CONSTANTS
#define squareAssetSize 50

#define redSpace 0 
#define greenSpace 1
#define yellowSpace 2
#define prison 3
#define hospital 4
#define whiteSpace 5
#define suffPieceRedSpace 6
#define suffPieceYellowSpace 7
#define suffPiecePrison 8
#define suffLeaderYellowSpace 9
#define suffLeaderRedSpace 10
#define suffLeaderPrison 11
#define copPieceYellowSpace 12
#define copPieceRedSpace 13
#define copPieceHospital 14
#define copLeaderYellowSpace 15
#define copLeaderRedSpace 16
#define copLeaderHospital 17
#define albertHallSpace 18
#define houseOfCommonsSpace 19
#define copPieceAlbertHall 20
#define copLeaderAlbertHall 21
#define suffPieceHouseOfCommons 22
#define suffLeaderHouseOfCommons 23

//Funciones de jugadas
void makePlay(int coord[4], int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],const char piece);
void playingTime(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],int dice);

//Funciones de logica del juego
int *countPieces(int board[boardSize][boardSize], int colorBoard[boardSize][boardSize]);
void rehab(int piece, int board[boardSize][boardSize], int colorBoard[boardSize][boardSize]);
int checkJugada(int coord[4],int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],char piece);
int isJumpable(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],char piece);
int consecJump(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],char piece);
void initBoard(int colorBoard[boardSize][boardSize], int piecesBoard[boardSize][boardSize]);
int jumpCounter(int board[boardSize][boardSize], int colorBoard[boardSize][boardSize], int coord[4],char piece);
int eat(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4],char piece);
int getWinner(int *counter);
int getWinnerGtk(int *counter);
void initSides(void);
int side(int piece);
void initSuffHum(void);
void initSuffCpu(void);
void randomSides(void);

//Funciones i/o y error handling
int getInt(const char *prompt,int minRange,int MaxRange);
char getChar(const char *prompt);
int coinFlip(int range);
void inputCoord(int coord[4]);
void printBoard(int colorBoard[boardSize][boardSize], int piecesBoard[boardSize][boardSize]);
int gameMenu(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],int coord[4]);
void mainMenu(void);
void banner(const char *prompt);
void startSuff(void);
void startCop(void);
void creditsBut(void);
void returnMenu(void);
void rulesMessage(void);
void continueSuffWinf(void);
void continueCopWinf(void);
void continueRulesf(void);
void continueCreditsf(void);
	

//Funciones de GTK
void insertPlayerStat(void);
void showStatsWindow(void);
int tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data);
GtkWidget *createBoardGtk(int colorBoard[boardSize][boardSize],int piecesBoard[boardSize][boardSize]);
GtkWidget *updateBoardGtk(int colorBoard[boardSize][boardSize],int piecesBoard[boardSize][boardSize]);
bool marcarPosiblesJugadas(int coordI,int coordJ,int piezaTablero[boardSize][boardSize],char piece,int moveType);
int cpuPlay(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize],char piece);
void stopMusic(GtkWidget *event_box, GdkEventButton *event, gpointer data);
void mainMenuGTK(GtkWidget *event_box, GdkEventButton *event, gpointer data);
int restartFunction(GtkWidget *event_box, GdkEventButton *event, gpointer data);
void xd2(GtkWidget *event_box, GdkEventButton *event, gpointer data);
void clickCopHum(void);
void clickCopCpu(void);
void clickSuffHum(void);
void clickSuffCpu(void);
void clickCopRandom(void);
void clickSuffRandom(void);
void closeOnlineWindow(void);
void onlineClicked (void);
void onlineConfig(void);
void configGame(void);
void contButton(GtkWidget *event_box, GdkEventButton *event, gpointer data);
void continueStatsf(void);

char *getText(const char *file);
struct jugador *getJugadores();
void printearJugadores(void);
void initPlayerStats(void);
void sortPlayerStats(void);
//Variables globales
char aiPiece;
char playerPiece;
int *puntMove;
int *puntMovecpu;
int startPiece;
char startSide;
int moveCounterAi;

//Funciones de inteligencia del juego
int aiPlay(int board[boardSize][boardSize],int colorBoard[boardSize][boardSize], char side);
GtkWidget *statsLabel;
GtkWidget *statsWindow;
GtkWidget *statsBut;
GtkWidget *startButton;
GtkWidget *startButton2;
GtkWidget *imagen; //auxiliar para cargar la imagen
GtkWidget *eventbox;
GtkWidget *tablero;
GtkWidget *gtkImagenes[boardSize][boardSize];
GtkWidget *label_turno;
GtkWidget *label_estado;
GdkColor color;
GtkWidget *window;
GtkWidget *mainWindow;
GtkWidget *windowConf;
GtkWidget *creditsWindow;
GtkWidget *rulesWindow;
GtkWidget *suffWinWindow;
GtkWidget *copWinWindow;
GtkWidget *box_tablero;
GtkWidget *imagenMenu;
GtkWidget *suffJugadas;
GtkWidget *copJugadas;
GtkWidget *restartButton;
GtkWidget *menuButton;
GtkWidget *saveButton;
GtkWidget *suffCounterLabel;
GtkWidget *copCounterLabel;
GtkWidget *suffHumanoBut;
GtkWidget *suffCpuBut;
GtkWidget *copHumanoBut;
GtkWidget *copCpuBut;
GtkWidget *startSuffBut;
GtkWidget *starCopBut;
GtkWidget *startRandomBut;
GtkWidget *randomPieceBut;
GtkWidget *randomPieceBut2;
GtkWidget *rulesButton;
GtkWidget *continueButton;
GtkWidget *creditsButton;
GtkWidget *name1But;
GtkWidget *name2But;
GtkWidget *menuButton;
GtkWidget *continueSuffWin;
GtkWidget *continueCopWin;
GtkWidget *continueCredits;
GtkWidget *continueRules;
GtkWidget *suffEntry;
GtkWidget *copEntry;
GtkWidget *copLabel;
GtkWidget *suffLabel;
GtkWidget *onlineButton;
GtkWidget *onlineWindow;
GtkWidget *onlineExit;
GtkWidget *startButton3;
GtkWidget *startCopBut1;
GtkWidget *startSuffBut1;
GtkWidget *onlineSuffOpt;
GtkWidget *onlineCopOpt;
GtkWidget *continueStats;

struct jugador{
    char nombre[40];
    int partidasJugadas;
    int partidasGanadas;
    int partidasPerdidas;
};
struct jugador jugadores[1000];