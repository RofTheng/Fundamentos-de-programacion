#include <stdio.h>

// Declaraciones de funciones para permitir una mayor modularización del programa.
int createMenu();
int startGame();
int openTable();
int exitGame();
int backMenu();


// Función principal del programa.
int main(){

    createMenu();
}

// Función que crea el menú principal.
int createMenu(){

    int option;

    //Le decimos al jugador que debe de elegir entre: Jugar, Ver tabla de puntuación y Salir.
    printf("Elgir opción del menú principal: Jugar = 1, Abrir Tabla = 2 o Salir = 3. \n");
    scanf("%d, ", &option);

    while (option != 1 && option != 2 && option != 3){

        printf("Carácter inválido. Por favor, inténtalo de nuevo. \n");
        scanf(" %d, ", &option);
    }

    //Bifurcamos el flujo de ejecución en función de la opción elegida.
    if (option == 1){

        startGame();

    } else if (option == 2){

        openTable();

    } else if (option == 3){

        exitGame();
    }

}

// Función para volver al menú, escribiendo 0 en consola. Si se escribe otro número, el programa lo detecta como inválido y permite reintentarlo.
int backMenu(){

    int backMenu;

    printf("Inserta '0' para volver al menú. \n");
    scanf("%d, ", &backMenu);
    
   while (backMenu != 0){

        printf("Carácter inválido. Por favor, inténtalo de nuevo. \n");
        scanf("%d, ", &backMenu);
    }

   createMenu();

}

// Función que inicia el juego y crea el tablero de los jugadores.
int startGame(){

    printf("El juego ha comenzado. \nEste es tu tablero: \n");
    
    // Creación de la matriz del tablero.
    int m[12][12] = {0};

    // Asigna la posición del portaviones en la matriz.
    for (int k = 0; k < 5; k++){

        m[0 + k][2] = 1;
    }

    // Asigna la posición de los cruceros en la matriz.
    for (int k = 0; k < 3; k++){

        m[5][6 + k] = 1;

        for (int k = 0; k < 3; k++){

            m[8 + k][4] = 1;
        }
    }

    // Asigna la posición de los patrulleros en la matriz
    for (int k = 0; k < 2; k++){

        m[8][6 + k] = 1;

        for(int k = 0; k < 2; k++){

            m[2][7 + k] = 1;

            for (int k= 0; k < 2; k++){

                m[10 + k][10] = 1;
            }
        }
    }

    // Imprime el tablero.
    for (int i = 0; i < 12; i++){

        for (int j = 0; j < 12; j++){

            printf("%d, ", m[i][j]);

        }

        printf("\n");
    }
    
    backMenu();
}

// Función que abre la tabla de mejores puntuaciones (Sin funcionalidad).
int openTable(){

    printf("Has abierto la tabla de mejores puntuaciones. \n");
    backMenu();
    
}

// Función que cierra el juego.
int exitGame(){

    printf("Has cerrado el juego");

}

