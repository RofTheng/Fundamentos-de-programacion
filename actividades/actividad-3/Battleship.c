#include <stdio.h> //librería básica//
#include <stdbool.h> //para hacer booleanos//
#include <time.h> //para hacer randoms//
#include <stdlib.h> //para el srand//
#include <string.h>

                //Dimensiones del grid//
#define Filas 12
#define Columnas 12

                //Path del folder//
#define Folder_Enemy_Map "Folder\\EnemyMap_Battleship.txt"
#define Folder_Player_Map "Folder\\PlayerMap_Battleship.txt"




//Declaraciones de funciones//
void PMap(char PlayerMap[Filas][Columnas], int nABoats);
void showPlayerMap(char PlayerMap[Filas][Columnas]);
void enemyRandomMap(char Map[Filas][Columnas], int nBoats);
void showEnemyMap();
void attackFunction(char Map[Filas][Columnas], int filaElegida, int columnaElegida, char attackerName[50]);
void enemyTurn();
void playerTurn();
void winnerMessage(char winnerName[50]);
int playAgain();
int showMainMenu();
void startNewGame();
void resetGame();



//Estructura de datos de la flota del jugador y del enemigo//


        //Matriz del mapa del jugador//
       char playerMap[Filas][Columnas]; 

        //Estructura de datos del jugador//
       struct playerFloat{
                char plname[50];
                int length;
       };

       //Estructura de los barcos aliados//

       struct playerFloat allyBoats[] = {
        {"Portaviones", 4},
        {"Crucero01", 3},
        {"Crucero02", 3},
        {"Patrullero01", 2},
        {"Patrullero02", 2},
        {"Patrullero03", 2}

        };



        // Natriz del mapa del enemigo//
       char enemyMap[Filas][Columnas]; 

        //Estructura de datos del enemigo//
        struct enemyFloat {   
                char nombre[50];
                int length;
        };

        //Estructura de los barcos enemigos//
        struct enemyFloat enemyBoats[] = { 
        {"PortavionesEnemigo", 4},
        {"CruceroEnemigo01", 3},
        {"CruceroEnemigo02", 3},
        {"PatrulleroEnemigo01", 2},
        {"PatrulleroEnemigo02", 2},
        {"PatrulleroEnemigo03", 2}
        };



        //Definición de los contadores de impactos//
        int enemyHits = 0;
        int playerHits = 0;

// Definiones de las funciones//



        //Creacion del mapa del jugador//
        void PMap(char PlayerMap[Filas][Columnas], int nABoats) {
      
        int Boats = 0;

        printf("Coloca tu flota en el tablero. En orden de colocación, se te muestran las naves de las que dispones:\n\n"
                "1 Portaviones (4x1) \n"
                "2 Cruceros (3x1) \n"
                "3 Patrulleras (2x1) \n \n");
        while (Boats < nABoats) {

                bool colocado = false; // Indica si el barco ha sido colocado para pasar al siguiente
                bool puedeColocarse = false; // Indica si las casillas del barco no se salen del tablero
                bool casillaLibre = true; // Indica si una de las casillas del barco está sobre una casilla en uso
                int direccion = 10; // Indica la dirección en la que se va a colocar el barco | 0 -> vertical --- 1 -> horizontal |

                // Bucle que controla y corrige las posiciones de las casillas
                        while(!colocado){ 
                                int fila = 0;
                                int columna = 0;

                                printf("Selecciona la fila (1 a 12)\n");
                                scanf( "%d", &fila);
                                if(fila < 1 || fila > Filas) {
                                        printf("Fila incorrecta.\n");
                                        continue;
                                }
                                fila--;

                                printf("Selecciona la columna (1 a 12)\n");
                                scanf("%d", &columna);
                                if(columna < 1 || columna > Columnas) {
                                        printf("Columna incorrecta.\n");
                                        continue;
                                }
                                columna--;

                                printf("Selecciona la dirección: VERTICAL -> 0 ---- HORIZONTAL -> 1\n");
                                scanf("%d", &direccion);
                                
                                if(fila < 0 || fila >= Filas || columna < 0 || columna >= Columnas) {
                                        printf("Coordenadas fuera de rango. Inténtalo de nuevo\n");
                                        continue;
                                }
                                // Comprobación de que la casilla actual no sobrepasa el borde del tablero (dirección vertical)
                                if(direccion == 0){
                                        if(fila + allyBoats[Boats].length <= Filas){           
                                                puedeColocarse = true;
                                        } else {
                                                printf("El barco no cabe verticalmente. Inténtalo de nuevo\n");
                                                continue;
                                        }
                                // Comprobación de que la casilla actual no sobrepasa el borde del tablero (dirección horizontal)        
                                } 
                                else if(direccion == 1) {
                                        if(columna + allyBoats[Boats].length < Columnas){
                                                puedeColocarse = true;
                                        } else {
                                                printf("El barco no cabe horizontalmente. Inténtalo de nuevo\n");
                                                continue;
                                                }
                                } else {
                                        printf("Dirección inválida (usa 0 o 1)\n");
                                        continue;
                                }

                                // Una vez comprobado que el barco no sobrepasa el borde del tablero, se comprueba que las casillas elegidas no colapsen con barcos ya situados en el tablero
                                if(puedeColocarse == true) {

                                        casillaLibre = true;
                                        for(int i = 0; i < allyBoats[Boats].length; i++){

                                                // Comprobación de los barcos verticales       
                                                if(direccion == 0){
                                       
                                                        if(playerMap[fila + i][columna] == 'X'){
                                                                casillaLibre = false;
                                                                break;
                                                        }
                                
                                                // Comprobación de los barcos horizontales
                                                } else { 

                                                        if(playerMap[fila][columna + i] == 'X'){
                                                                casillaLibre = false;
                                                                break;
                                                        } 
                                                }

                                        }       
                                // En caso de que estén las casillas libres, se coloca el barco en el tablero
                                        if(casillaLibre == true){

                                                // Colocación del barco en el tablero
                                                for(int i = 0; i < allyBoats[Boats].length; i++){

                                                        if(direccion == 0){
                                       
                                                                playerMap[fila + i][columna] = 'X';

                                                        } else {
                                       
                                                                playerMap[fila][columna + i] = 'X';
                                                        }
                                                }

                                                //Texto pasara saber que todo se ha generado correctamente//
                                                printf("Tu %s se ha posicionado como %d (0 -> VERTICAL | 1 -> HORIZONTAL)\n", allyBoats[Boats].plname, direccion);
                                                Boats++;
                                                colocado = true;
                                        } else {
                                                printf("Casilla inctorrecta. Inténtalo de nuevo\n");
                                        }        
                                } else{
                                        printf("Error de entrada. Inténtalo de nuevo\n\n");
                                        break;
                                }
                        
                        }
                }
                 FILE *Folder = fopen(Folder_Player_Map, "w");
                        if (Folder == NULL) {
                                perror("Error al crear el Folder del mapa");
                                exit(1);
                        }

                        for (int i = 0; i < Filas; i++) {
                                for (int j = 0; j < Columnas; j++) {
                                fprintf(Folder, "%c ", PlayerMap[i][j]);
                                }
                                fprintf(Folder, "\n");
                        }

                        fclose(Folder);
                
        }
        

        //Muestra en pantalla el mapa del jugador//
        void showPlayerMap(char PlayerMap[Filas][Columnas]){

                printf("Tu tablero actual es:\n");

                for (int i = 0; i < Filas; i++) {
                        for (int j = 0; j < Columnas; j++){
                                printf("%c ", PlayerMap[i][j]);
                        }
                        printf("\n");
                }
        }        

        //Creación del mapa del enemigo//
        void enemyRandomMap(char Map[Filas][Columnas], int nBoats) {

        // Inicializar el mapa con espacios en blanco
        for (int i = 0; i < Filas; i++) {
                for (int j = 0; j < Columnas; j++) {
                Map[i][j] = '-';
                }
           }     
        
                //Aleatoriedad//



            //Número de barcos//
                int Boats = 0;
                while (Boats < nBoats) {

                        bool colocado = false; // Indica si el barco ha sido colocado para pasar al siguiente
                        bool puedeColocarse = false; // Indica si las casillas del barco no se salen del tablero
                        bool casillaLibre = true; // Indica si una de las casillas del barco está sobre una casilla en uso
                        int direccion = rand() % 2; // Indica la dirección en la que se va a colocar el barco | 0 -> vertical --- 1 -> horizontal |

                        // Bucle que controla y corrige las posiciones de las casillas
                        while(!colocado){                       
                                int fila = rand() % Filas;
                                int columna = rand() % Columnas;
                                

                                // Comprobación de que la casilla actual no sobrepasa el borde del tablero (dirección vertical)
                                if(direccion == 0){
                                        if(fila + enemyBoats[Boats].length < Filas){           
                                                puedeColocarse = true;
                                        } else {
                                                puedeColocarse = false;
                                                continue;
                                        }
                                // Comprobación de que la casilla actual no sobrepasa el borde del tablero (dirección horizontal)        
                                } else {
                                        if(columna + enemyBoats[Boats].length < Columnas){
                                                puedeColocarse = true;
                                        } else {
                                                puedeColocarse = false;
                                                continue;
                                                }
                                }

                                // Una vez comprobado que el barco no sobrepasa el borde del tablero, se comprueba que las casillas elegidas no colapsen con barcos ya situados en el tablero
                                if(puedeColocarse == true) {

                                        casillaLibre = true;
                                        for(int i = 0; i < enemyBoats[Boats].length; i++){

                                                // Comprobación de los barcos verticales       
                                                if(direccion == 0){
                                       
                                                        if(Map[fila + i][columna] == 'O'){
                                                                casillaLibre = false;
                                                                break;
                                                        }
                                
                                                // Comprobación de los barcos horizontales
                                                } else { 

                                                        if(Map[fila][columna + i] == 'O'){
                                                                casillaLibre = false;
                                                                break;
                                                        } 
                                                }

                                        }       
                                // En caso de que estén las casillas libres, se coloca el barco en el tablero
                                        if(casillaLibre == true){

                                                // Colocación del barco en el tablero
                                                for(int i = 0; i < enemyBoats[Boats].length; i++){

                                                 if(direccion == 0){
                                       
                                                        Map[fila + i][columna] = 'O';

                                                 } else {
                                       
                                                         Map[fila][columna + i] = 'O';
                                                        }
                                
                                                 
                                
                                                //Texto pasara saber que todo se ha generado correctamente//
                                                }
                                                printf("The ememy ship %s has been positioned %d \n", enemyBoats[Boats].nombre, direccion);
                                                Boats++;
                                                colocado = true;
                                        }        
                                }
                        }
                }
        

                //Creación del fichero donde estará el mapa enemigo//

                 FILE *Folder = fopen(Folder_Enemy_Map, "w");
                        if (Folder == NULL) {
                                perror("Error al crear el Folder del mapa");
                                exit(1);
                        }

                        for (int i = 0; i < Filas; i++) {
                                for (int j = 0; j < Columnas; j++) {
                                fprintf(Folder, "%c ", Map[i][j]);
                                }
                                fprintf(Folder, "\n");
                        }

                        fclose(Folder);

        }

        //Muestra el mapa del enemigo en blanco (sin mostrar barcos enemigos, hundidos o tocados)//
        void showEnemyMap() {
               
                printf("El tablero actual del enemigo es:\n");
                
                for (int i = 0; i < Filas; i++) {
                        for (int j = 0; j < Columnas; j++){

                                char c = enemyMap[i][j];

                                if(c == 'X'){
                                        printf("X ");
                                }else if(c == 'A'){
                                        printf("A ");
                                }else {
                                        printf("- ");
                                }
                                        
                        }
                        printf("\n");
                }                
                
        }       
        

        //Muestra el mensaje de quien ha ganado//
        void winnerMessage(char winnerName[50]){
                  if(strcmp(winnerName, "player") == 0){
                        printf("¡Felicidades, has ganado la partida!\n");

                } else if(strcmp(winnerName, "enemy") == 0){
                        printf("¡Lo sentimos! Has sido vencido por el rival\n");
                }
        }

        

              
        //Función de ataque general//
        void attackFunction(char Map[Filas][Columnas], int filaElegida, int columnaElegida, char attackerName[50]){     
              printf("Ataque lanzado con éxito\n");

              bool turnCompleted = false;
              bool hit = false;
              


                while(turnCompleted == false){

                        //Turno del jugador//
                        if(strcmp(attackerName, "player") == 0){

                                printf("El jugador ha atacado al enemigo.\n");

                                //Caso 1: la casilla marcada ya se eligió anteriormente//
                                if(Map[filaElegida][columnaElegida] == 'A' || 
                                   Map[filaElegida][columnaElegida] == 'X') {
                                        printf("Esta casilla ya ha sido utilizada anteriormente. Intentalo de nuevo.\n");
                                        showEnemyMap();
                                        playerTurn();
                                        return;
                                }

                                //Caso 2: la casilla marcada es un impacto. El jugador repite turno//
                                if(Map[filaElegida][columnaElegida] == 'O'){
                                        printf("Flota del enemigo tocada.\n");
                                        Map[filaElegida][columnaElegida] = 'X';
                                        showEnemyMap();
                                        hit = true;
                                        turnCompleted = true;
                                        playerHits++;
                                        if(playerHits == 16){
                                                winnerMessage(attackerName);
                                                int again = playAgain();
                                                if(again == 1){
                                                        startNewGame();
                                                        
                                                }
                                                return;
                                                
                                        } else {
                                                printf("Repites turno\n");
                                                playerTurn();
                                                return;
                                        }
                                        
                                     

                                //Caso 3: la casilla elegida es agua. Turno del rival//
                                } else {
                                        Map[filaElegida][columnaElegida] = 'A';
                                        showEnemyMap();
                                        printf("Agua. Turno del rival.\n");
                                        enemyTurn();
                                        return;
                                }

                                
                               
                                
                                if(hit){
                                        playerTurn();
                                        return;
                                } else {
                                        enemyTurn();
                                        return;
                                }

        
                
                
                        //Turno del enemigo//
                        } else if(strcmp(attackerName, "enemy") == 0){

                                printf("El enemigo ha atacado al jugador\n");

                                if(Map[filaElegida][columnaElegida] == 'X'){
                                        printf("Flota aliada tocada en %d, %d. El enemigo vuelve a atacar.\n", filaElegida, columnaElegida);
                                        Map[filaElegida][columnaElegida] = '*';
                                        enemyHits++;
                                        if(enemyHits == 16){
                                                winnerMessage(attackerName);
                                                int again = playAgain();
                                                if(again == 1) {
                                                        startNewGame();
                                                }
                                                return;
                                        } else {
                                                printf("El rival repite turno\n");
                                                showPlayerMap(playerMap);
                                                enemyTurn();
                                                return;
                                        }       
                                        
                                        
                                }

                                if(Map[filaElegida][columnaElegida] == '-'){
                                        printf("El rival ha atacado en %d, %d. No ha alcanzado ninguna flota aliada.\n", filaElegida, columnaElegida);
                                        Map[filaElegida][columnaElegida] = 'A';
                                        showPlayerMap(playerMap);
                                        playerTurn();
                                        return;
                                } 
                        }
                }
        }


        //Turno del jugador//
        void playerTurn(){


                int filaEnemigaElegida;
                int columnaEnemigaElegida;
                bool filaElegidaValida = false;
                bool columnaElegidaValida = false;
                char playerName[50] = "player";
                


                printf("¡Es tu turno de atacar!\n");

                //Bucle donde el jugador elige las casillas enemigas. Estas son validadas (no se sale del tablero ni se trata de otro tipo de caracteres)//
                while(!(filaElegidaValida && columnaElegidaValida)){
                        
                        printf("Selecciona una fila enemiga.\n");
                        if(scanf("%d", &filaEnemigaElegida) != 1){
                                int c;
                                while((c = getchar()) != '\n' && c != EOF) {}
                                printf("Entrada inválida.\n");
                                continue;
                        }

                        filaEnemigaElegida--;

                        if(filaEnemigaElegida < 0 || filaEnemigaElegida >= Filas){
                                printf("Fila incorrecta.\n");
                        } else {
                                filaElegidaValida = true;
                        }

                         printf("Selecciona una columna enemiga.\n");
                        if(scanf("%d", &columnaEnemigaElegida) != 1){
                                int c;
                                while((c = getchar()) != '\n' && c != EOF) {}
                                printf("Entrada inválida.\n");
                                continue;
                        }

                        columnaEnemigaElegida--;

                        if (columnaEnemigaElegida < 0 || columnaEnemigaElegida >= Columnas){
                                printf("Columna incorrecta.\n");
                        } else {
                                columnaElegidaValida = true;
                        }
                
                        if(filaElegidaValida && columnaElegidaValida){
                                attackFunction(enemyMap, filaEnemigaElegida, columnaEnemigaElegida, playerName);
                                return;
                        } else {
                                printf("Datos incorrectos. Inténtalo de nuevo\n");
                        }
                
                }
                
                




        }


        //Turno del enemigo//
        void enemyTurn(){
        
                int filaAliadaElegida = rand() % Filas;
                int columnaAliadaElegida = rand() % Columnas;
                char enemyName[50] = "enemy";

                printf("¡Es turno del enemigo!\n");

                attackFunction(playerMap, filaAliadaElegida, columnaAliadaElegida, enemyName);


}     


        //Función que reinicia los tableros y aciertos//
        void resetGame(){

        //Numero de barcos aliados//
        int nABoats = 6;

       //Numero de barcos enemigos//
        int nBoats = 6;
        
        //Para contar el número de barcos hundidos//
        int Boats= 0;

                // Inicializar el mapa con espacios en blanco
        for (int i = 0; i < Filas; i++) {
                for (int j = 0; j < Columnas; j++) {
                playerMap[i][j] = '-';
                }
         }

         for (int i = 0; i < Filas; i++) {
                for (int j = 0; j < Columnas; j++) {
                enemyMap[i][j] = '-';
                }
         }

                playerHits = 0;
                enemyHits = 0;

                PMap(playerMap, nABoats);
                enemyRandomMap(enemyMap, nBoats);
        }


        //Función de empezar nueva partida//
        void startNewGame(){
                resetGame();
                showPlayerMap(playerMap);
                showEnemyMap();
                playerTurn();
                return;
        }


        //Pregunta al jugador si quiere jugar de nuevo o volver al menú//
        int playAgain(){

                int playNewGame;

                for(;;) {

                        printf("¿Deseas comenzar una nueva partida? \n\n COMENZAR NUEVA PARTIDA -> 1 | REGRESAR AL MENÚ PRINCIPAL -> 0\n");

                        if(scanf("%d", &playNewGame) != 1){

                                int c;
                                while((c = getchar()) != '\n' && c != EOF) {}
                                printf("Entrada inválida.\n");
                                continue;
                        }

                        if(playNewGame == 0 || playNewGame == 1){
                                return playNewGame;
                
                        }
                }
        }  


        //Muestra el menú principal//
        int showMainMenu(){

                char name[50];
                int menu;

                printf("¡Bienvenido a HUNDIR LA FLOTA!\n\n");

                printf("Por favor, escribe tu nombre (no más de 10 caracteres):\n");

                scanf("%49s", name);

                printf("Gracias, continuemos %s.\n", name);

                printf("¿Qué quieres hacer?\n\n", name);

                for(;;) {
                                
                        printf("-----------  1  Jugar   -----------\n");
                        printf("-----------  2  Marcador -----------\n");
                        printf("-----------  3  Salir   -----------\n");

                        if(scanf("%d", &menu) != 1) {

                                int c;

                                while((c = getchar()) != '\n' && c != EOF) {

                                        printf("Entrada inválida\n");
                                        continue;
                                }
                        }

                        if(menu >= 1 && menu <= 3) {

                                return menu;
                        }

                        printf("Opción incorrecta. Inténtalo de nuevo\n");
                }          
        }


        // Función principal del programa     
        int main(){
        
                //Establece la semilla al inciarse el programa//
                srand(time(NULL));

                for(;;){
                       int option = showMainMenu();
    
                        switch (option)
                        {
                        case 1:
                                startNewGame();
                                break;
                
                                
                        case 2: 
                                printf("¡Veamos quién es el mejor!\n");
                                break;

                        case 3:
                                printf("Gracias por jugar. ¡Nos vemos pronto!");
                                return 0;
                        } 
                } 
        }       