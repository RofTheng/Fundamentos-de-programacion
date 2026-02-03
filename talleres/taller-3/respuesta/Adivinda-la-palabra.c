#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
        char nombre[50];
        int puntuacion;
    }playerInfo;

int main(){

    char *animales[4] = {"gato", "perro", "pajaro", "caballo"};

    playerInfo *players = NULL;
    int playersNum = 0;

    srand(time(NULL));
    /*do{
        players = realloc(players, (playersNum +1) * sizeof(playerInfo));
        scanf("%d", players[playersNum].nombre);
    }

    printf("Bienvenido a ¡¡Adivina la Palabra!!\n");

    printf("\nInserta el número de jugadores (máximo 4)\n");

    scanf(" %d", &playersNum);

    for(int i = 1; i == playersNum; i++){

        int actualPlayer = 1;

    }*/
    
    
  
}
