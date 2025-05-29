#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include "snakelib.h"

int calcolaLivello(int xp){
    int livello = 1;
    while(livello < 20 && xp >= 50 * pow(livello + 1, 1.5)){
        livello++;
    }
    return livello;
}

int xpPerProssimoLivello(int livelloAttuale){
    return (int)(50 * pow(livelloAttuale + 1, 1.5));
}

int calcoloMax(int max, int n){
    if(n > max) return n;
    else return max;
}

void stampaClassifica(){
    Classifica classMele[100];
    Classifica classOro[100];
    Classifica classLivelli[100];
    
    system("clear");
    
    int nUtenti = caricaClassifiche(classMele,classOro,classLivelli); 
    int max;
    if(nUtenti < 10){
        max = nUtenti;
    }else{
        max = 10;
    }
        
    printf("\n\n\n\n");
    printf("\t\t====== CLASSIFICA MELE NORMALI ======\n");
    for (int i = 0; i < max; i++) {
        printf("\t\t%2d. %-20s | 🍎  %d\n", i + 1, classMele[i].username, classMele[i].dato);
    }

    printf("\n\n\t\t====== CLASSIFICA MELE D'ORO ======\n");
    for (int i = 0; i < max; i++) {
        printf("\t\t%2d. %-20s | 🟡  %d\n", i + 1, classOro[i].username, classOro[i].dato);
    }

    printf("\n\n\t\t====== CLASSIFICA LIVELLI ======\n");
    for (int i = 0; i < max; i++) {
        printf("\t\t%2d. %-20s | 🧱  Livello %d\n", i + 1, classLivelli[i].username, classLivelli[i].dato);
    }
    
    getchar(); 
}

int caricaClassifiche(Classifica* classMele, Classifica* classOro, Classifica* classLivelli){
    FILE* f = fopen("./data/utenti.dat", "rb");
    if(f == NULL){
        perror("Errore apertura file ^caricaUtentiEClassifiche^");
        return 0;
    }

    User utenteLetto;
    int counter = 0;

    while(fread(&utenteLetto, sizeof(User), 1, f) == 1 && counter < 100){
        
        // Mele normali
        strcpy(classMele[counter].username, utenteLetto.username);
        classMele[counter].dato = utenteLetto.bestScore;

        // Mele d'oro
        strcpy(classOro[counter].username, utenteLetto.username);
        classOro[counter].dato = utenteLetto.bestScoreGold;

        // Livelli
        strcpy(classLivelli[counter].username, utenteLetto.username);
        classLivelli[counter].dato = calcolaLivello(utenteLetto.xp);

        counter++;
    }

    fclose(f);

    bSortDecrescente(classMele,counter);
    bSortDecrescente(classOro,counter);
    bSortDecrescente(classLivelli,counter);

    return counter; // numero di utenti caricati e ordinati
}

void bSortDecrescente(Classifica* lista, int n){
    int i, j;
    Classifica t;
    
    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            if(lista[j].dato < lista[j + 1].dato){
                t = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = t;
            }
        }
    }
}