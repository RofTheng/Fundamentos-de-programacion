#include <stdio.h>
#include <stdlib.h>


void gameLoop(void);

void gameLoop(){
    // Declaración y definición de variables
    int vidaCastillo = 100;

    char indexDefensaElegida = '0';

    int defensaElegida = 0;

    printf("\n---- Bienvenido a DEFENDER EL CASTILLO ----\n");

    // Bucle del juego. Este termina al acabar 5 rondas o cuando el castillo es destruido

    for(int i = 0; i < 5 || vidaCastillo > 0; i++){

        // Inicio de ataque final en 0
        int ataqueFinal = 0;

        // Ataque enemigo
        int ataqueEnemigo = rand() % (30-10+1) + 10;

        // Pedir defensa al player
        printf("\nElige una defensa:\n\n 1--> Muralla (5 de defensa)\n 2--> Arqueros (10 de defensa) \n 3--> Aceite Hirviendo (15 de defensa)\n");
        scanf(" %c", &indexDefensaElegida);

        // Según la elección del jugador, se establece el nivel de la defensa

        if(indexDefensaElegida == '1'){
            defensaElegida = 5;
        } else if (indexDefensaElegida == '2'){
            defensaElegida = 10;
        } else if (indexDefensaElegida == '3'){
            defensaElegida = 15;
        } else {
            printf ("\nError. Vuelva a elegir defensa\n");
            i--;
            continue;

        }

        // Cálculo para resolver el valor del ataque final

        ataqueFinal = defensaElegida - ataqueEnemigo;

        // Verificamos si el ataque a impactado o la defensa a logrado pararlo

        if(ataqueFinal < 0){
            vidaCastillo = vidaCastillo + ataqueFinal;
            printf("\nEl ataque enemigo ha imapctado en el castillo\n");
        } else {
            printf("\nEl ataque enemigo ha sido bloqueado con éxito\n");
        }

        // Mostramos la información de la ronda
        printf("\n-----INFORMACIÓN DE LA RONDA-----\n");
        printf("\nEl ataque enemigo fue %d\n", ataqueEnemigo);
        printf("\nLa defensa elegida fue %d\n", defensaElegida);
        printf("\nEl daño recibido fue %d\n", ataqueFinal);
        printf("\nLa vida del castillo es %d\n", vidaCastillo);

    }

    // Verificamos el estado del final, si el castillo ha aguantado o ha caído
    if (vidaCastillo <= 0){
        printf("\nEl castillo ha sido destruido\n");
    } else {
        printf("\nEl castillo ha resistido\n");
    }
}

int main() {

    gameLoop();

    char eleccionPartidaNueva = '0';

    printf("\nDeseas empezar una partida nueva?\n s--> sí --- n--> no\n");
    scanf(" %c", &eleccionPartidaNueva);

    if(eleccionPartidaNueva == 's'){
        gameLoop();
    } else {
        return 0;
    }

}

