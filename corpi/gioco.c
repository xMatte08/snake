#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "snakelib.h"

void gioco(User* user){
   
    srand(time(NULL));

    terminaleNonBloccante();


    int table[MAX_TABLE][MAX_TABLE];
    Coord snake[MAX_SNAKE_LEN];
    int snakeDim = 3;
    int i, meleMangiate = 0, meleDoroMangiate = 0;
    int direzione = 100, input = 100;
    char c;

    snake[0].x = 8; snake[0].y = 7;   // da dove parte lo snake
    snake[1].x = 7; snake[1].y = 7;
    snake[2].x = 6; snake[2].y = 7;

    svuotaM(table);
    aggiornaMatrice(table, snake, snakeDim);
    posizionaMela(table, snake, snakeDim);
    stampaTabella(table,meleMangiate,meleDoroMangiate);
    
    do{
        input = getchar();

        printf("%c\n", ' ');

        if(input == 100 && direzione != 97){         
            direzione = input;
        }else if(input == 97 && direzione != 100){  
            direzione = input;
        }else if(input == 119 && direzione != 115){ 
            direzione = input;
        }else if(input == 115 && direzione != 119){ 
            direzione = input;
        }

        cancellaSnake(table,snake,snakeDim);

        for(i = snakeDim - 1; i > 0; i--){ //fa seguire il corpo alla testa
            snake[i] = snake[i - 1];
        }
    
        switch (direzione) { // direzione dello snake con i tasti WASD
            case 100: snake[0].x++; break;
            case 97: snake[0].x--; break;
            case 119: snake[0].y--; break;
            case 115: snake[0].y++; break;
        }       
/*
                'w' ASCII: 119
                's' ASCII: 115
                'd' ASCII: 100
                'a' ASCII: 97
*/
                
        if(snake[0].x < 0 || snake[0].x >= MAX_TABLE || snake[0].y < 0 || snake[0].y >= MAX_TABLE){ // 1. Controllo se la testa sbatte contro il muro
            menuFinePartita( meleMangiate,meleDoroMangiate,user -> xp, user -> bestScore, user -> bestScoreGold);
            user -> bestScoreGold = calcoloMax(user -> bestScoreGold,meleDoroMangiate);
            user -> bestScore = calcoloMax(user -> bestScore,meleMangiate);

            return;
        }

        for(int i = 1; i < snakeDim; i++){  // controllo se lo snakone sbatte su se stesso
            if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){
                menuFinePartita( meleMangiate,meleDoroMangiate,user -> xp, user -> bestScore, user -> bestScoreGold);
                user -> bestScore = calcoloMax(user -> bestScore,meleMangiate);
                              user -> bestScoreGold = calcoloMax(user -> bestScoreGold,meleDoroMangiate);                  
                
                return;
            }
        }
          
        if(table[snake[0].y][snake[0].x] == 1 || table[snake[0].y][snake[0].x] == 2){  // Quando mangi mela
            snakeDim++;
            if(table[snake[0].y][snake[0].x] == 1){
                user -> xp += 10; // aumento xp mela 
                meleMangiate++;
            }else{
                user -> xp += 25; // aumento xp mela d'oro
                meleDoroMangiate++;
            }            
            snake[snakeDim - 1] = snake[snakeDim - 2];
            posizionaMela(table, snake, snakeDim);
        }

        if(snakeDim == MAX_SNAKE_LEN){ //se vinci
            menuFinePartita( meleMangiate,meleDoroMangiate,user -> xp, user -> bestScore, user -> bestScoreGold);
            user -> bestScore = calcoloMax(user -> bestScore,meleMangiate);
            user -> bestScoreGold = calcoloMax(user -> bestScoreGold,meleDoroMangiate);  
             
            return;
        }

        aggiornaMatrice(table, snake, snakeDim);
        
        stampaTabella(table,meleMangiate,meleDoroMangiate); 
        usleep(200000);

    }while(1);

}

void svuotaM(int M[][MAX_TABLE]){
    int i, j;
    
    for(i = 0; i < MAX_TABLE; i++){
        for(j = 0; j < MAX_TABLE; j++){
                M[i][j] = 0;
        }
    }
}

void aggiornaMatrice(int M[][MAX_TABLE], Coord* snake, int snakeDim) {
    
    M[snake[0].y][snake[0].x] = 100; // Posiziona la testa

    for(int i = 1; i < snakeDim; i++){ // Posiziona il corpo
        M[snake[i].y][snake[i].x] = 101;
    }
}

void cancellaSnake(int M[][MAX_TABLE], Coord* snake, int snakeDim) {
    for(int i = 0; i < snakeDim; i++){
        M[snake[i].y][snake[i].x] = 0;
    }
}

void stampaTabella(int M[][MAX_TABLE], int meleMangiate, int meleDoroMangiate){
    int i, j;
    
    system("clear");

    printf("\n\n\n");
    
    for(i = 0; i < MAX_TABLE; i++) {
        printf("\t\t\t\t\t\t");
        for(j = 0; j < MAX_TABLE; j++){
            if ((i + j) % 2 == 0) {
                printf("\x1b[42m");  // sfondo verde scuro
            } else {
                printf("\x1b[102m"); // sfondo verde chiaro
            }

            switch(M[i][j]){
                case 0:
                    printf(" "); // cella vuota
                    break;
                case 1:
                    printf("\x1b[31mద\x1b[0m"); // mela rossa
                    break;
                case 2:
                    printf("\x1b[93mద\x1b[0m"); // mela d'oro
                    break;
                case 100:
                    printf("\e[30m0\e[0m"); // testa
                    break;
                case 101:
                    printf("\e[30mo\e[0m"); // coda
                    break;
                default:
                    printf("?");
                    break;
            }

            printf("\x1b[0m");
        }
        if(i == 1){
            printf("  Mele Mangiate -> \e[33m%-3d\e[0m ", meleMangiate);
        }   
        if(i == 2){
            printf("  Mele GOLD Mangiate -> \e[33m%-3d\e[0m ", meleDoroMangiate);
        }
        printf("\n");
    }

}

void posizionaMela(int M[][MAX_TABLE], Coord* snake, int snakeDim){
    int x, y;
    bool occupato;

    srand(time(NULL));

    do{
        occupato = false;
        x = rand() % MAX_TABLE;
        y = rand() % MAX_TABLE;

        for(int i = 0; i < snakeDim; i++){ // Controlla che non sia sopra lo snake
            if(snake[i].x == x && snake[i].y == y){
                occupato = true;
            }
        }

        if(M[y][x] == 1 || M[y][x] == 2){ // Controlla che non ci sia già una mela
            occupato = true;
        }
    }while(occupato);

    if((rand()%10) == 1){
        M[y][x] = 2;
    }else{
        M[y][x] = 1;
    }

}