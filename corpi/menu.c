#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "snakelib.h"

char menuPrincipale(User* utente){
    int scelta, c = 0;
    
    system("clear");

    printf("\n\n\n\n");
    printf("\t\t╔════════════════════ \e[92mSNAKE\e[0m ════════════════════╗\n");
    printf("\t\t╠                                               ╣\n");
    printf("\t\t╠  \e[5mBenvenuto\e[0m \e[96m%-15s\e[0m            \e[93mLV. %-2d\e[0m  ╣        \n", utente -> username , calcolaLivello(utente -> xp));
    printf("\t\t╠                                               ╣\n");
    printf("\t\t╠  Best SCORE:                       GIOCA [1]  ╣\n");
    printf("\t\t╠  Mele Mangiate -> \e[33m%-3d\e[0m         CLASSIFICA [2]  ╣\n", utente -> bestScore);
    printf("\t\t╠  Mele GOLD Mangiate -> \e[33m%-3d\e[0m          ESCI [0]  ╣\n", utente -> bestScoreGold);
    printf("\t\t╠                                               ╣\n");
    printf("\t\t╚═══════════════════════════════════════════════╝\n");
    
    salvaUtenteSuFile(*utente);

    terminaleBloccante();
    while(c != '1' && c != '2' && c != '0'){
        c = getchar();
    }
    ripristinaTerminale();

    return c;
}

    void menuFinePartita(int meleMangiate, int meleDoroMangiate, int xp, int bestScore, int bestScoreGold){

        system("clear");
        
        printf("\n\n\n\n");
        printf("\t\t╔══════════════════════════ \e[92mSNAKE\e[0m ══════════════════════════╗\n");
        printf("\t\t╠                                                           ╣\n");
        printf("\t\t╠                         \e[5;91mGAME OVER\e[0m                         ╣\n");
        if(bestScore < meleMangiate){
            printf("\t\t╠                                                           ╣\n");
            printf("\t\t╠  \e[5mBravo hai superato il tuo record di mele mangiate\e[0m        ╣\n");
        }
        if(bestScoreGold < meleDoroMangiate){
            printf("\t\t╠                                                           ╣\n");
            printf("\t\t╠  \e[5mBravo hai superato il tuo record di mele d'oro mangiate\e[0m  ╣\n");
        }
        printf("\t\t╠                                                           ╣\n");
        printf("\t\t╠  %-4d XP al prossimo livello                              ╣\n", xpPerProssimoLivello(calcolaLivello(xp)));
        printf("\t\t╠  Mele Mangiate -> \e[33m%-3d\e[0m                                     ╣\n", meleMangiate);
        printf("\t\t╠  Mele GOLD Mangiate -> \e[33m%-3d\e[0m                                ╣\n", meleDoroMangiate);
        printf("\t\t╠                                                           ╣\n");
        printf("\t\t╚═══════════════════════════════════════════════════════════╝\n");

        ripristinaTerminale();
        while (getchar() != '\n');

    }