#include "suffragetto.h"
#include <stdio.h>
#include <string.h>
int colorTablero[boardSize][boardSize];
int piezaTablero[boardSize][boardSize];
/*
struct jugador{
    char nombre[40];
    int partidasJugadas;
    int partidasGanadas;
    int partidasPerdidas;
};
struct jugador jugadores[1000];*/
void insertPlayerStat(void){
    int i,j;
    int suffWin = 0,copWin = 1;
    if(getWinner(countPieces(piezaTablero,colorTablero))){
        suffWin = 1;
        copWin = 0;
    }
    const char *suffNombre= gtk_entry_get_text(GTK_ENTRY(suffEntry));
	const char *copNombre = gtk_entry_get_text(GTK_ENTRY(copEntry));

    for(i = 0;jugadores[i].partidasGanadas;i++){
        if(strcmp(suffNombre,jugadores[i].nombre) == 0) break;
    }
    for(j = 0;jugadores[j].partidasGanadas;j++){
        if(strcmp(copNombre,jugadores[j].nombre) == 0) break;
    }
    sprintf(jugadores[i].nombre,"%s",suffNombre);
    jugadores[i].partidasJugadas++;
    jugadores[i].partidasGanadas += suffWin;
    jugadores[i].partidasPerdidas += copWin;
    
    sprintf(jugadores[j].nombre,"%s",copNombre);
    jugadores[j].partidasJugadas++;
    jugadores[j].partidasGanadas += copWin;
    jugadores[j].partidasGanadas += suffWin;
}
void printearJugadores(void){
    fclose(fopen("playerStats", "w"));
    sortPlayerStats();
    FILE* archivo = fopen("playerStats", "a+");
    for(int i = 0;jugadores[i].partidasJugadas;i++){
        g_print("%s %d %d %d\n",jugadores[i].nombre,jugadores[i].partidasGanadas,jugadores[i].partidasPerdidas,jugadores[i].partidasJugadas);
        fprintf(archivo,"%s %d %d %d\n",jugadores[i].nombre,jugadores[i].partidasGanadas,jugadores[i].partidasPerdidas,jugadores[i].partidasJugadas);
    }
    fclose(archivo);
}
struct jugador *getJugadores(){
    /*FILE* archivo =fopen("playerStats","a+");
    fprintf(archivo,"\n");
    fclose(archivo);*/
        
    char *text = getText("playerStats");
    char nombre[100];

    int jugadas,ganadas,perdidas,temp,lineCounter = -1,i = 0;
    
    while(text[i] != '\0'){
        if(text[i] == '\n') 
            lineCounter++; 
        i++;
    }
    i = 0;
    do{
        temp = sscanf(text,"%s %d %d %d",jugadores[i].nombre,&jugadores[i].partidasGanadas,&jugadores[i].partidasPerdidas,&jugadores[i].partidasJugadas);
        //printf("%s %d %d %d\n",jugadores[i].nombre,jugadores-> partidasGanadas,jugadores->partidasPerdidas,jugadores->partidasJugadas);
        while((*text)!='\n'||(*text) <= '\0')text++;
        text++;
        i++;
    }while(lineCounter--);
    temp = sscanf(text,"%s %d %d %d",jugadores[i].nombre,&jugadores[i].partidasGanadas,&jugadores[i].partidasPerdidas,&jugadores[i].partidasJugadas);;
    //printf("%s %d %d %d\n",jugadores[i].nombre,jugadores-> partidasGanadas,jugadores->partidasPerdidas,jugadores->partidasJugadas);;   
}
void initPlayerStats(void){
    for(int i = 0; i < 1000;i++){
        jugadores[i].nombre[0] = '\0';
        jugadores[i].partidasPerdidas = 0;
        jugadores[i].partidasGanadas = 0;
        jugadores[i].partidasJugadas = 0;
    }
}
void sortPlayerStats(void){
    struct jugador aux;
    for(int i = 0; i < 1000;i++){
        for(int j = i+1; j<1000;j++){
            if(jugadores[i].partidasGanadas < jugadores[j].partidasGanadas){
                aux = jugadores[j];
                jugadores[j] = jugadores[i];
                jugadores[i] = aux;
            }
        }
    }

}