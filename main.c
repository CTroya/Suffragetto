#include <gtk/gtk.h>
#include "suffragetto.h"
int colorTablero[boardSize][boardSize];
int piezaTablero[boardSize][boardSize];
int coordInput[4];
//Gamemode 1  h vs cpu
//Gamemode 2  h vs h
//Gamemode 3 cpu vs cpu
//Gamemode 4 Online
int moveCounter = 1;
int gameMode = 2;
int isSuffAi = 0;
int isCopAi = 0;
pid_t pid;
char *imagenes[] = {"./Assets/redSpace.png",
					"./Assets/greenSpace.png",
					"./Assets/yellowSpace.png",
					"./Assets/prison.png",
					"./Assets/hospital.png",
					"./Assets/whiteSpace.png",
					"./Assets/suffPieceRedSpace.png",
					"./Assets/suffPieceYellowSpace.png",
					"./Assets/suffPiecePrison.png",
					"./Assets/suffLeaderYellowSpace.png",
					"./Assets/suffLeaderRedSpace.png",
					"./Assets/suffLeaderPrison.png",
					"./Assets/copPieceYellowSpace.png",
					"./Assets/copPieceRedSpace.png",
					"./Assets/copPieceHospital.png",
					"./Assets/copLeaderYellowSpace.png",
					"./Assets/copLeaderRedSpace.png",
					"./Assets/copLeaderHospital.png",
					"./Assets/albertHall.png",
					"./Assets/houseOfCommons.png",
					"./Assets/copPieceAlbertHall.png",
					"./Assets/copLeaderAlbertHall.png",
					"./Assets/suffPieceHouseOfCommons .png",
					"./Assets/suffLeaderHouseOfCommons.png"
};

int main(int argc, char *argv[]){
	startSide = copPiece;
	startPiece = 1;
	playerPiece = suffPiece;
    aiPiece = copPiece;
	
	fclose(fopen("moveLog.suff", "w"));
	fclose(fopen("moveLog.cop", "w"));
	//initSides();
  	pid = fork();
	system("killall aplay");
	printf("\nPID:%d",pid);
	if(pid == 0){
		while(1)system("aplay snkBgMusic.wav");
	}else{
	initBoard(colorTablero,piezaTablero);
	GdkColor color;	
    //Para el GtkBuilder
    guint ret;
    GtkBuilder *builder;
    GError *error = NULL;
    gtk_init (&argc, &argv);
	builder = gtk_builder_new();
	//Se carga el builder	
	ret = gtk_builder_add_from_file(builder, "tablero.glade", &error);
	if (ret == 0) {
		g_print("Error en la función gtk_builder_add_from_file:\n%s", error->message);
		return 1;
	}
	GtkWidget *label1, *label2;
	//Lista stats
	
	//Botones
	statsBut = GTK_WIDGET(gtk_builder_get_object(builder,"statsBut"));
	startCopBut1 = GTK_WIDGET(gtk_builder_get_object(builder,"startCopBut1"));
	startSuffBut1 = GTK_WIDGET(gtk_builder_get_object(builder,"startSuffBut1"));
	onlineSuffOpt = GTK_WIDGET(gtk_builder_get_object(builder,"onlineSuffOpt"));
	onlineCopOpt = GTK_WIDGET(gtk_builder_get_object(builder,"onlineCopOpt"));
	onlineExit = GTK_WIDGET(gtk_builder_get_object(builder,"onlineExit"));
	copEntry = GTK_WIDGET(gtk_builder_get_object(builder,"copEntry"));
	suffEntry = GTK_WIDGET(gtk_builder_get_object(builder,"suffEntry"));
	onlineButton = GTK_WIDGET(gtk_builder_get_object(builder,"onlineButton"));
	startButton = GTK_WIDGET(gtk_builder_get_object(builder,"startButton"));
	startButton2 = GTK_WIDGET(gtk_builder_get_object(builder,"startBut"));
	startButton3 = GTK_WIDGET(gtk_builder_get_object(builder,"startBut1"));
	restartButton = GTK_WIDGET(gtk_builder_get_object(builder,"restartButton"));
	menuButton = GTK_WIDGET(gtk_builder_get_object(builder,"menuButton"));
	saveButton = GTK_WIDGET(gtk_builder_get_object(builder,"saveButton"));
	saveButton = GTK_WIDGET(gtk_builder_get_object(builder,"saveButton"));
	suffCounterLabel = GTK_WIDGET(gtk_builder_get_object(builder,"suffCounterLabel"));
	copCounterLabel = GTK_WIDGET(gtk_builder_get_object(builder,"copCounterLabel"));
	suffHumanoBut = GTK_WIDGET(gtk_builder_get_object(builder,"suffHumanoBut"));
	suffCpuBut = GTK_WIDGET(gtk_builder_get_object(builder,"suffCpuBut"));
	copHumanoBut = GTK_WIDGET(gtk_builder_get_object(builder,"copHumanoBut"));
	copCpuBut = GTK_WIDGET(gtk_builder_get_object(builder,"copCpuBut"));
	startSuffBut = GTK_WIDGET(gtk_builder_get_object(builder,"startSuffBut"));
	starCopBut = GTK_WIDGET(gtk_builder_get_object(builder,"startCopBut"));
	startRandomBut = GTK_WIDGET(gtk_builder_get_object(builder,"startRandomBut"));
	randomPieceBut = GTK_WIDGET(gtk_builder_get_object(builder,"randomPieceBut"));
	randomPieceBut2 = GTK_WIDGET(gtk_builder_get_object(builder,"randomPieceBut2"));
	creditsButton = GTK_WIDGET(gtk_builder_get_object(builder,"creditsButton"));
	rulesButton = GTK_WIDGET(gtk_builder_get_object(builder,"rulesButton"));
	menuButton = GTK_WIDGET(gtk_builder_get_object(builder,"menuButton"));
	continueButton = GTK_WIDGET(gtk_builder_get_object(builder,"continueButton"));
	continueSuffWin = GTK_WIDGET(gtk_builder_get_object(builder,"continueSuffWin"));
	continueCopWin = GTK_WIDGET(gtk_builder_get_object(builder,"continueCopWin"));
	continueRules = GTK_WIDGET(gtk_builder_get_object(builder,"continueRules"));
	continueCredits = GTK_WIDGET(gtk_builder_get_object(builder,"continueCredits"));
	continueStats = GTK_WIDGET(gtk_builder_get_object(builder, "continueStats"));

	gdk_color_parse("gold", &color);
	gtk_widget_modify_bg( GTK_WIDGET(restartButton), GTK_STATE_NORMAL, &color);
	gtk_widget_modify_bg( GTK_WIDGET(menuButton), GTK_STATE_NORMAL, &color);
	gtk_widget_modify_bg( GTK_WIDGET(saveButton), GTK_STATE_NORMAL, &color);
	gtk_widget_modify_bg( GTK_WIDGET(statsBut), GTK_STATE_NORMAL, &color);

	//Ventanas
	statsWindow = GTK_WIDGET(gtk_builder_get_object(builder,"statsWindow"));
	onlineWindow = GTK_WIDGET(gtk_builder_get_object(builder,"onlineWindow"));
	window = GTK_WIDGET(gtk_builder_get_object(builder, "ventana"));
	mainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"ventana1"));
	windowConf = GTK_WIDGET(gtk_builder_get_object(builder,"ventanaConfiguracion"));
	creditsWindow = GTK_WIDGET(gtk_builder_get_object(builder,"creditsWindow"));
	copWinWindow = GTK_WIDGET(gtk_builder_get_object(builder,"copWinWindow"));
	suffWinWindow = GTK_WIDGET(gtk_builder_get_object(builder,"suffWinWindow"));
	rulesWindow = GTK_WIDGET(gtk_builder_get_object(builder,"rulesWindow"));


	//Box donde estara el Tablero
	box_tablero = GTK_WIDGET(gtk_builder_get_object(builder, "box_tablero"));



	//Labels
	statsLabel = GTK_WIDGET(gtk_builder_get_object(builder,"playerStatsLabel"));
	suffLabel = GTK_WIDGET(gtk_builder_get_object(builder, "suffLabel"));
	copLabel = GTK_WIDGET(gtk_builder_get_object(builder, "copLabel"));
	suffJugadas = GTK_WIDGET(gtk_builder_get_object(builder, "suffJugadas"));
	copJugadas = GTK_WIDGET(gtk_builder_get_object(builder, "copJugadas"));
	label_turno = GTK_WIDGET(gtk_builder_get_object(builder, "label_turno"));
	label_estado = GTK_WIDGET(gtk_builder_get_object(builder, "label_estado"));

	//Imagen de la pantalla del menu
	imagenMenu = GTK_WIDGET(gtk_builder_get_object(builder,"imagenMenu"));

	gtk_box_pack_start(GTK_BOX(box_tablero), createBoardGtk(colorTablero,piezaTablero), TRUE, FALSE, 0);
	updateBoardGtk(colorTablero,piezaTablero);
	gdk_color_parse("GRAY 20", &color);//Podemos elegir el color del fondo Gray 20
	gtk_widget_modify_bg( GTK_WIDGET(window), GTK_STATE_NORMAL, &color);
    /* Connect the destroy signal of the window to gtk_main_quit
     * When the window is about to be destroyed we get a notification and
     * stop the main GTK+ loop
     */
	//Signals
	g_signal_connect(statsBut,"clicked",G_CALLBACK(showStatsWindow),NULL);
	g_signal_connect(onlineButton,"clicked",G_CALLBACK(onlineClicked),NULL);
	g_signal_connect(creditsButton, "clicked", G_CALLBACK(creditsBut), NULL);
	g_signal_connect(continueCredits,"clicked", G_CALLBACK(continueCreditsf), NULL);
	g_signal_connect(continueStats, "clicked",G_CALLBACK(continueStatsf), NULL);
	g_signal_connect(rulesButton, "clicked", G_CALLBACK(rulesMessage), NULL);
	g_signal_connect(continueRules,"clicked", G_CALLBACK(continueRulesf), NULL);
	g_signal_connect(startButton, "button-press-event", G_CALLBACK(mainMenuGTK), NULL);
	g_signal_connect(startButton2, "button-press-event", G_CALLBACK(xd2), NULL);
	g_signal_connect(startButton3,"button-press-event",G_CALLBACK(onlineConfig), NULL);
	g_signal_connect(startButton3,"clicked",G_CALLBACK(xd2), NULL);
	g_signal_connect (mainWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL); 
	g_signal_connect (mainWindow, "destroy", G_CALLBACK (stopMusic), NULL);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL); 
	g_signal_connect (window, "destroy", G_CALLBACK (stopMusic), NULL);//Gracias GTK por hacer esto posible :)
	g_signal_connect(restartButton, "button-press-event", G_CALLBACK(restartFunction), NULL);
	g_signal_connect(menuButton, "button-press-event", G_CALLBACK(returnMenu), NULL);
	g_signal_connect(eventbox, "button-press-event", G_CALLBACK(tablero_cb), tablero);

    /* make sure that everything, window and label, are visible */
    //gtk_widget_show_all (window);
	//gtk_window_set_default_size(GTK_WINDOW(mainWindow), 640,780);
	gtk_window_set_default_size(GTK_WINDOW(window), 1400,1000);
	gtk_widget_show_all (mainWindow);
    /* start the main loop, and let it rest there until the application is closed */
    gtk_main ();
	}
    return 0;
}
void showStatsWindow(void){
	gtk_widget_show_all(statsWindow);
	gtk_label_set_text(GTK_LABEL(statsLabel),getText("playerStats"));
}
void continueStatsf(void){
	gtk_widget_hide(statsWindow);
}
void onlineConfig(void){
	
	gtk_widget_hide(GTK_WIDGET(onlineWindow));
	char suffFileName[40],copFileName[40];
	const char *suffNombre= gtk_entry_get_text(GTK_ENTRY(suffEntry));
	const char *copNombre = gtk_entry_get_text(GTK_ENTRY(copEntry));
	sprintf(suffFileName,"%s.txt",suffNombre);

	gtk_label_set_text(GTK_LABEL(suffLabel),suffNombre);
	gtk_label_set_text(GTK_LABEL(copLabel),copNombre);
	gameMode = 4;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(startCopBut1))) startSide = copPiece;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(startSuffBut1))) startSide = suffPiece;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(onlineSuffOpt))) aiPiece = suffPiece;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(onlineSuffOpt))) aiPiece = copPiece;

	printf(ANSI_COLOR_RED"Online! gamemode: %d"ANSI_COLOR_RESET,gameMode);
	moveCounterAi = 1;
	moveCounter = 1;

	g_signal_connect(continueButton,"clicked",G_CALLBACK(contButton),NULL);
	initBoard(colorTablero,piezaTablero);
	updateBoardGtk(colorTablero,piezaTablero);
	fclose(fopen("moveLog.suff", "w"));
	fclose(fopen("moveLog.cop", "w"));
	gtk_widget_show_all (window);
	gtk_widget_hide_on_delete(GTK_WIDGET(windowConf));
	if(startPiece == 0 && aiPiece == suffPiece){
		//if(gameMode!=2 || gameMode == 4)cpuPlay(piezaTablero,colorTablero,aiPiece);
		if(gameMode!=2 || gameMode == 4)aiPlay(piezaTablero,colorTablero,aiPiece);
		updateBoardGtk(colorTablero,piezaTablero);
	}
	if(startPiece == 1 && aiPiece == copPiece){
		//if(gameMode!=2 || gameMode == 4)cpuPlay(piezaTablero,colorTablero,aiPiece);
		if(gameMode!=2 || gameMode == 4)aiPlay(piezaTablero,colorTablero,aiPiece);
		updateBoardGtk(colorTablero,piezaTablero);
	}
}
void closeOnlineWindow(void){
	gtk_widget_hide(onlineWindow);
	gtk_widget_show_all(mainWindow);
}
void onlineClicked (void){
	gtk_widget_hide(mainWindow);
	gtk_widget_show_all(onlineWindow);
	g_signal_connect(onlineExit,"clicked",G_CALLBACK(closeOnlineWindow),NULL);
}
void contButton(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	gtk_widget_show_all (window);
	gtk_widget_hide(mainWindow);
}
void configGame(void){
	int sides[2] = {suffPiece,copPiece};
	//Botones policia
	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(copHumanoBut))){
		isCopAi = false;
		playerPiece = copPiece;
		g_print("isCopAi = false;\n");
	}
	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(copCpuBut))){
		isCopAi = true;
		aiPiece = copPiece;
		g_print("isCopAi = true;\n");
	}
	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(randomPieceBut2))){
		isCopAi = coinFlip(1);
		if(isCopAi == 1) aiPiece = copPiece;
		g_print("isCopAi = coinFlip(1);\n");
	}
	//Botones suffragettes
	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(suffHumanoBut))){
		isSuffAi = false;
		playerPiece = suffPiece;
		g_print("isSuffAi = 0;\n");
	}
	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(suffCpuBut))){
		isSuffAi = true;
		aiPiece = suffPiece;
		g_print("isSuffAi = 0;\n");
	}
	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(randomPieceBut))){
		isSuffAi = coinFlip(1);
		if(isSuffAi == 1) aiPiece = suffPiece;
		g_print("isSuffAi = coinFlip(1);\n");
	}
	if(isSuffAi == 1 && isCopAi == 1) gameMode = 3;
	if(isSuffAi == 0 && isCopAi == 0) gameMode = 2;
	if(isSuffAi != isCopAi) gameMode = 1;

}
int restartFunction(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	if(gameMode != 1 || moveCounterAi <= 1) return 0;
	initBoard(colorTablero,piezaTablero);
	updateBoardGtk(colorTablero,piezaTablero);
	fclose(fopen("moveLog.suff", "w"));
	fclose(fopen("moveLog.cop", "w"));
	gtk_label_set_text(GTK_LABEL(suffJugadas)," ");
	gtk_label_set_text(GTK_LABEL(copJugadas)," ");
	*puntMove = 1;
	*puntMovecpu = 1;
	int *counter = countPieces(piezaTablero,colorTablero);
	if(startPiece == 0 && aiPiece == suffPiece){
		//if(gameMode!=2 || gameMode == 4)cpuPlay(piezaTablero,colorTablero,aiPiece);
		if(gameMode!=2 || gameMode == 4)aiPlay(piezaTablero,colorTablero,aiPiece);
		updateBoardGtk(colorTablero,piezaTablero);
	}
	if(startPiece == 1 && aiPiece == copPiece){
		//if(gameMode!=2 || gameMode == 4)cpuPlay(piezaTablero,colorTablero,aiPiece);
		if(gameMode!=2 || gameMode == 4)aiPlay(piezaTablero,colorTablero,aiPiece);
		updateBoardGtk(colorTablero,piezaTablero);
	}
}
void xd2(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	//system("clear");
	const char *suffNombre= gtk_entry_get_text(GTK_ENTRY(suffEntry));
	const char *copNombre = gtk_entry_get_text(GTK_ENTRY(copEntry));
	gtk_label_set_text(GTK_LABEL(suffLabel),suffNombre);
	gtk_label_set_text(GTK_LABEL(copLabel),copNombre);
	configGame();
	printf(ANSI_COLOR_RED"gamemode: %d"ANSI_COLOR_RESET,gameMode);
	moveCounterAi = 1;
	moveCounter = 1;
	g_signal_connect(continueButton,"clicked",G_CALLBACK(contButton),NULL);
	initBoard(colorTablero,piezaTablero);
	updateBoardGtk(colorTablero,piezaTablero);
	fclose(fopen("moveLog.suff", "w"));
	fclose(fopen("moveLog.cop", "w"));
	gtk_widget_show_all (window);
	gtk_widget_hide_on_delete(GTK_WIDGET(windowConf));
	if(gameMode == 4){
	}else{
	if(startPiece == 0 && aiPiece == suffPiece){
		//if(gameMode!=2)cpuPlay(piezaTablero,colorTablero,aiPiece);
		if(gameMode!=2)aiPlay(piezaTablero,colorTablero,aiPiece);
			updateBoardGtk(colorTablero,piezaTablero);
		}	
		if(startPiece == 1 && aiPiece == copPiece){
			//if(gameMode!=2)cpuPlay(piezaTablero,colorTablero,aiPiece);
			if(gameMode!=2)aiPlay(piezaTablero,colorTablero,aiPiece);
			updateBoardGtk(colorTablero,piezaTablero);
		}
	}
}
void startSuff(void){
	startPiece = 0;
	startSide = suffPiece;
}
void startCop(void){
	startPiece = 1;
	startSide = copPiece;
}
void startRandom(void){
	startPiece = coinFlip(1);
	if(startPiece == 0) startSide = suffPiece;
	if(startPiece == 1) startSide = copPiece;
	
}
void creditsBut(void){
	gtk_widget_show_all (creditsWindow);
}
void rulesMessage(void){
	gtk_widget_hide_on_delete(GTK_WIDGET(window));
	gtk_widget_show_all (rulesWindow);
}
void returnMenu(void){
	gtk_widget_hide_on_delete(GTK_WIDGET(window));
	gtk_widget_show_all (mainWindow);
	g_signal_connect(startButton, "button-press-event", G_CALLBACK(mainMenuGTK), NULL);
}
int getWinnerGtk(int *counter){
    if(counter[0] < 6 || counter[3] >= 6){ //Policias ganan
		initBoard(colorTablero,piezaTablero);
		updateBoardGtk(colorTablero,piezaTablero);
		gtk_widget_show_all(copWinWindow);
		fclose(fopen("moveLog.suff", "w"));
		fclose(fopen("moveLog.cop", "w"));
		getJugadores();
		insertPlayerStat();
		sortPlayerStats();
		printearJugadores();
		return 1;
		}    
        
    if(counter[1] < 6 || counter[2] >= 6){ //suffragettes ganan
		insertPlayerStat();
		gtk_widget_show_all (suffWinWindow);
		initBoard(colorTablero,piezaTablero);
		updateBoardGtk(colorTablero,piezaTablero);
		fclose(fopen("moveLog.suff", "w"));
		fclose(fopen("moveLog.cop", "w"));
		getJugadores();
		insertPlayerStat();
		sortPlayerStats();
		printearJugadores();
		return 1;
		}
	return 0;
}
void mainMenuGTK(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	guint ig,jg;
	ig = (GUINT_FROM_LE(event->y) / squareAssetSize); //las imagenes tienen son 50x50pixeles
	jg = (GUINT_FROM_LE(event->x) / squareAssetSize);
	
	gtk_widget_show_all (windowConf);
	gtk_widget_hide_on_delete(GTK_WIDGET(mainWindow));

	g_signal_connect(startSuffBut,"clicked", G_CALLBACK(startSuff), NULL);
	g_signal_connect(starCopBut,"clicked", G_CALLBACK(startCop), NULL);
	g_signal_connect(startRandomBut,"clicked", G_CALLBACK(startRandom), NULL);

	g_signal_connect(continueSuffWin,"clicked", G_CALLBACK(continueSuffWinf), NULL);
	g_signal_connect(continueCopWin,"clicked", G_CALLBACK(continueCopWinf), NULL);
}
bool marcarPosiblesJugadas(int coordI,int coordJ,int piezaTablero[boardSize][boardSize],char piece,int moveType){	
	int coordPruebaXD[4], tablero_aux[boardSize][boardSize];
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++){
			tablero_aux[i][j] = piezaTablero[i][j];
		}
	}
	tablero_aux[0][1] = 420;
	bool ret = false;
	coordPruebaXD[0] = coordI;
	coordPruebaXD[1] = coordJ;
	int selectI = coordI, selectJ = coordJ;
	
	for(int i = 0; i < boardSize; i++){
			for(int j = 0; j < boardSize; j++){
				coordPruebaXD[2] = i;
				coordPruebaXD[3] = j;
				if(moveType == todos){
					if(checkJugada(coordPruebaXD,tablero_aux,colorTablero,piece) == true && piezaTablero[i][j] == blank){
						gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),"moveMarker.png");
						ret++;
					}
				}
				if(moveType == saltos){
					if(checkJugada(coordPruebaXD,tablero_aux,colorTablero,piece) == true && piezaTablero[i][j] == blank 
					&& isJumpable(tablero_aux,colorTablero,coordPruebaXD,piece)){
						gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),"moveMarker.png");
						ret++;
					}
				}
			}
		}
	ret = (piezaTablero[coordI][coordJ] == blank)? false: true;
	return ret;
}
char *getText(const char *file) {
	static char *text;
    text =  (char *)malloc(21);
	int i=0;
    printf(ANSI_COLOR_RESET);
    FILE * title;
    int c,end;
    int counter = 0;
    title = fopen(file, "r");

    while ((c = fgetc(title)) != EOF){
        if(counter % 20 == 0 && counter != 0) text = (char *)realloc(text, counter+50);
		text[counter] = c;
		counter++;
    }
	text[counter] = '\0';
	//printf("%s",text);
	fclose(title);
	return text;
}
int tablero_cb(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	char bandoMensaje[2][50] = {
		"Turno de los policias!",
		"Turno de las suffragettes!",
	};
	static int countTurn = 0;
	if(gameMode == 1){
		if(playerPiece == copPiece)gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[0]);
		if(playerPiece == suffPiece)gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[1]);
	}
	if(gameMode == 2){
	if(startSide == suffPiece && countTurn == 0){
		gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[(countTurn+1)%2]);
		countTurn++;}
	if(startSide == copPiece && countTurn == 0){
		gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[(countTurn)%2]);
		countTurn++;}}
	if(gameMode == 3||gameMode == 4){
		return 0;
	}
	static int ind = 0;
	static char sides[2];
	if(gameMode == 2 && ind == 0){
		sides[0] = startSide;
		sides[1] = (startSide == suffPiece)? copPiece: suffPiece; 
	}
	if(gameMode == 2) playerPiece = sides[(ind)%2];
	FILE *movePanel = fopen("moveLog.suff","a+");
	char *text;
	guint ig,jg;
	char piece; 
    char *mensaje[]= {
        "Haz clic en la \nficha a seleccionar",
        "Haz clic en la \ncasilla a mover",
		"Salto consecutivo xd \nhay que poner algo aca :v"
    };

	ig = (GUINT_FROM_LE(event->y) / squareAssetSize); //las imagenes tienen son 50x50pixeles
	jg = (GUINT_FROM_LE(event->x) / squareAssetSize);
	
	/*
	-State 0: Seleccion de origen
	-State 1: Seleccion de destino
	-State 2: Seleccion de destino en salto consecutivo
	*/
	
	static int state = 0,coord[4] = {blank}, consecCount = 0, *consecPiece;
	int selectCoord = piezaTablero[ig][jg], c, cpuFlag = 0;

	int *counter = countPieces(piezaTablero,colorTablero);
	puntMove = &moveCounter;
	switch (state){
		case 0:
			marcarPosiblesJugadas(ig,jg,piezaTablero,playerPiece,todos);
			state = tolower(piezaTablero[ig][jg]) == playerPiece && (colorTablero[ig][jg] == red|| 
					colorTablero[ig][jg] == yellow || colorTablero[ig][jg] == albertHall|| colorTablero[ig][jg] == commonHouse);
			coord[0] = ig; coord[1] = jg;
			break;
		case 1:
			state = 0;
			coord[2] = ig; coord[3] = jg;
			int diffI = (coord[2]-coord[0])/2; int diffJ = (coord[3]-coord[1])/2;
    		int midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;

			int moveType = isJumpable(piezaTablero,colorTablero,coord,piezaTablero[coord[0]][coord[1]]);

			if(checkJugada(coord,piezaTablero,colorTablero,playerPiece)){
				c = piezaTablero[coord[0]][coord[1]];
				piezaTablero[coord[0]][coord[1]] = blank;
				piezaTablero[coord[2]][coord[3]] = c;

				fprintf(movePanel,"%c-%d %c-%d ",coord[1]+'A',coord[0]+1,coord[3]+'A',coord[2]+1);
				if(moveType == 2){
					rehab(piezaTablero[midPosicI][midPosicJ],piezaTablero,colorTablero);
					piezaTablero[midPosicI][midPosicJ] = blank;
					counter = countPieces(piezaTablero,colorTablero);
					getWinnerGtk(counter);
				}
				if(moveType > 0 && jumpCounter(piezaTablero,colorTablero,coord,piezaTablero[coord[0]][coord[1]])){
					state = 2;
					updateBoardGtk(colorTablero,piezaTablero);
					marcarPosiblesJugadas(coord[2],coord[3],piezaTablero,playerPiece,saltos);
					consecPiece = &piezaTablero[coord[2]][coord[3]];
				}else{
						fprintf(movePanel,"|%d\n",moveCounter++);
						text = getText("moveLog.suff");
						gtk_label_set_text(GTK_LABEL(suffJugadas),text);
						state=0;
						consecCount = 0;
						cpuFlag = 1;		
					}
			}
			
			break;
		case 2:
			consecCount++;
			coord[0] = coord[2]; coord[1] = coord[3];
			coord[2] = ig; coord[3] = jg;
			
			moveType = isJumpable(piezaTablero,colorTablero,coord,piezaTablero[coord[0]][coord[1]]);
			diffI = (coord[2]-coord[0])/2; diffJ = (coord[3]-coord[1])/2;
    		midPosicI = coord[0] + diffI, midPosicJ = coord[1] + diffJ;

			if(checkJugada(coord,piezaTablero,colorTablero,playerPiece) && isJumpable(piezaTablero,colorTablero,coord,playerPiece)){
				consecPiece = &piezaTablero[coord[2]][coord[3]];
				c = piezaTablero[coord[0]][coord[1]];
				piezaTablero[coord[0]][coord[1]] = blank;
				piezaTablero[coord[2]][coord[3]] = c;
				printBoard(colorTablero,piezaTablero);
				fprintf(movePanel,"%c-%d %c-%d ",coord[1]+'A',coord[0]+1,coord[3]+'A',coord[2]+1);
				if(moveType == 2){
					rehab(piezaTablero[midPosicI][midPosicJ],piezaTablero,colorTablero);
					piezaTablero[midPosicI][midPosicJ] = blank;
					counter = countPieces(piezaTablero,colorTablero);
					getWinnerGtk(counter);
				}
			}else{
				if(&piezaTablero[coord[0]][coord[1]] == &piezaTablero[coord[2]][coord[3]]){
					state = 0;
					consecCount = 0;
					cpuFlag = 1;
				}
			}
			if(consecCount == 2 || marcarPosiblesJugadas(coord[2],coord[3],piezaTablero,playerPiece,saltos) == 0 ||
			   consecPiece != &piezaTablero[coord[2]][coord[3]]){ 
				fprintf(movePanel,"|%d\n",moveCounter++);
				state = 0;
				consecCount = 0;
				cpuFlag = 1;
			}
			updateBoardGtk(colorTablero,piezaTablero);
			marcarPosiblesJugadas(coord[2],coord[3],piezaTablero,playerPiece,saltos);
			break;
	}
	if(cpuFlag == 1){
		//if(gameMode!=2) cpuPlay(piezaTablero,colorTablero,aiPiece);
		if(gameMode!=2) {
			aiPlay(piezaTablero,colorTablero,aiPiece);
			text = getText("moveLog.cop");
			gtk_label_set_text(GTK_LABEL(copJugadas),text);
			}
		counter = countPieces(piezaTablero,colorTablero);
		getWinnerGtk(counter);
		ind++;
		countTurn++;
	}
	if(state == 0){
		updateBoardGtk(colorTablero,piezaTablero);
		counter = countPieces(piezaTablero,colorTablero);
		getWinnerGtk(counter);
		if(gameMode == 2){
		if(countTurn % 2 == 0){
			gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[1]);
		}
		else{
			gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[0]);
		}
	}
	}
	text = getText("moveLog.suff");
	gtk_label_set_text(GTK_LABEL(suffJugadas),text);
	gdk_color_parse("Gold", &color);
	gtk_widget_modify_fg(GTK_WIDGET(label_turno),GTK_STATE_NORMAL,&color);
	gtk_widget_modify_fg(GTK_WIDGET(label_estado),GTK_STATE_NORMAL,&color);
	
	gchar *temp = g_strdup_printf("\n%s\nPresiono en [%c,%d]",mensaje[state], jg+'A', ig+1);
	g_print("J: %c , I: %d",jg+'A',ig+1);
	system("aplay move.wav");
	
	gtk_label_set_text(GTK_LABEL(label_estado), temp);
	//gtk_label_set_text(GTK_LABEL(label_turno),bandoMensaje[cpuFlag]);
	fclose(movePanel);
	
	
	//g_free(temp);
}		
GtkWidget *createBoardGtk(int colorBoard[boardSize][boardSize],int piecesBoard[boardSize][boardSize]){
	int i, j;
	for (i = 0; i < boardSize; i++){
		for(j = 0; j < boardSize; j++){
			gtkImagenes[i][j] = gtk_image_new();
		}
	}
	eventbox = gtk_event_box_new();
	tablero = gtk_grid_new();
	for (i = 0; i < boardSize; i++){
		for(j = 0; j < boardSize; j++){
			gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),"blank.png");
			gtk_grid_attach(GTK_GRID(tablero), GTK_WIDGET(gtkImagenes[i][j]), j, i, 1, 1);
		}
	}

	gtk_container_add(GTK_CONTAINER(eventbox), tablero);

	
	char *text = getText("moveLog.cop");
	gtk_label_set_text(GTK_LABEL(copJugadas),text);
	return eventbox;
}
GtkWidget *updateBoardGtk(int colorBoard[boardSize][boardSize],int piecesBoard[boardSize][boardSize]){
	int i, j;
	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < boardSize; j++) {
				if(piecesBoard[i][j] == blank){//Casilla vacia
                	switch (colorBoard[i][j]){
                    	case red:
							gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[redSpace]);
                        	break;
                    	case yellow:
                        	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[yellowSpace]);
                        	break;
                    	case Hospital:
							gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[hospital]);
							break;
						case Prison:
                    		gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[prison]);
                        	break;
                    	case prisonYard: case hospitalGrounds:
                       		gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[greenSpace]);
                        	break;
                    	case albertHall: 
							gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[albertHallSpace]);
                        	break;
						case commonHouse:
                        	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[houseOfCommonsSpace]);
                        	break;
                	}
				}
				if(piecesBoard[i][j] == suffPiece){//Sufragette
                	switch (colorBoard[i][j]){
                	case red:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffPieceRedSpace]);
						break;
                	case yellow:
                   		gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffPieceYellowSpace]);
                    	break;
                	case Hospital: case Prison:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffPiecePrison]);
                    	break;
                	case prisonYard: case hospitalGrounds:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffPiecePrison]);
                    	break;
                	case albertHall: case commonHouse:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffPieceHouseOfCommons]);
                    	break;
                	}
            	}
            	if(piecesBoard[i][j] == suffLeader){//Lider Suffragette
                	switch (colorBoard[i][j]){
                	case red:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffLeaderRedSpace]);
                    	break;
                	case yellow:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffLeaderYellowSpace]);
                    	break;
                	case Hospital: case Prison:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffLeaderPrison]);
                    	break;
                	case prisonYard: case hospitalGrounds:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffLeaderPrison]);
                    	break;
                	case albertHall: case commonHouse:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[suffLeaderHouseOfCommons]);
                    	break;
                	}
            	}
            	if(piecesBoard[i][j] == copPiece){//Policia
                	switch (colorBoard[i][j]){
                	case red:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copPieceRedSpace]);
                    	break;
                	case yellow:
                   		gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copPieceYellowSpace]);
                    	break;
                	case Hospital: case Prison:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copPieceHospital]);
                    	break;
                	case prisonYard: case hospitalGrounds:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copPieceHospital]);
                    	break;
                	case albertHall: case commonHouse:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copPieceAlbertHall]);
                    	break;
                	}
            	}
            	if(piecesBoard[i][j] == copLeader){//Policia Lider
                	switch (colorBoard[i][j]){
                	case red:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copLeaderRedSpace]);
                    	break;
                	case yellow:
                   		gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copLeaderYellowSpace]);
                    	break;
                	case Hospital: case Prison:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copLeaderHospital]);
                    	break;
                	case prisonYard: case hospitalGrounds:
                    	gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copLeaderHospital]);
                    	break;
                	case albertHall: case commonHouse:
                  		gtk_image_set_from_file(GTK_IMAGE(gtkImagenes[i][j]),imagenes[copLeaderAlbertHall]);
                    	break;
                	}
            	}	
            }
		}
	char piecesBannerString[20];
	char piecesBannerString1[20];
	static int *piecesOnBoard;
	piecesOnBoard = countPieces(piezaTablero,colorTablero);
	sprintf(piecesBannerString,"%d",piecesOnBoard[0]);
	sprintf(piecesBannerString1,"%d",piecesOnBoard[1]);
	//printf("%s\n%s",piecesBannerString,piecesBannerString1);
	gtk_label_set_text(GTK_LABEL(suffCounterLabel),piecesBannerString);
	gtk_label_set_text(GTK_LABEL(copCounterLabel),piecesBannerString1);
	char *text = getText("moveLog.cop");
	gtk_label_set_text(GTK_LABEL(copJugadas),text);
	text = getText("moveLog.cop");
	//free(text);
	gtk_label_set_text(GTK_LABEL(suffJugadas),text);
	return eventbox;

}
void stopMusic(GtkWidget *event_box, GdkEventButton *event, gpointer data){
	fclose(fopen("moveLog.suff", "w"));
	fclose(fopen("moveLog.cop", "w" ));
	system("killall aplay");
	(pid != 0)? kill(pid,SIGKILL):blank;
	//system("killall main");//Esta linea es medio peligrosa lgm
	kill(getpid(),SIGKILL);
}
void initSides(void){
    aiPiece = suffPiece;
    playerPiece = copPiece;
}
void randomSides(void){
    int toss;
    toss = coinFlip(1);
    if(toss == 0){
        playerPiece = suffPiece;
        aiPiece = copPiece;
    }
    else{
        aiPiece = suffPiece;
        playerPiece = copPiece;
    }
}
void continueSuffWinf(void){
	gtk_widget_hide_on_delete(GTK_WIDGET(suffWinWindow));
}
void continueCopWinf(void){
	gtk_widget_hide_on_delete(GTK_WIDGET(copWinWindow));
}
void continueRulesf(void){
	gtk_widget_hide_on_delete(GTK_WIDGET(rulesWindow));
}
void continueCreditsf(void){
	gtk_widget_hide_on_delete(GTK_WIDGET(creditsWindow));
}