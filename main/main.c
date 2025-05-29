#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "snakelib.h"

int main(int argc, char** argv){
    User utente;
    char c;

    accesso(&utente);

    do{
        c = menuPrincipale(&utente);
        switch(c){
            case '1':          
                gioco(&utente);
                break;
            
            case '2':               
                stampaClassifica();
                break;
            
            case '0':
                system("clear");
                printf("Arrivederci! \n");  
                break;
        }        
    }while(c != '0');
    
    return 0;
}



