#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "snakelib.h"

void accesso(User* user){
    int scelta, c = 0;

    system("clear");
    
    printf("\n\n\n\n");
    printf("\t\t╔════════════════ ACCESSO ════════════════╗ \n");
    printf("\t\t╠                                         ╣ \n");
    printf("\t\t╠  ACCEDI                             [1] ╣ \n");
    printf("\t\t╠  REGISTRATI se non hai un account   [2] ╣ \n");
    printf("\t\t╠                                         ╣ \n");
    printf("\t\t╚═════════════════════════════════════════╝ \n");

    terminaleBloccante();
    while(c != '1' && c != '2'){
        c = getchar();
    }
    ripristinaTerminale();  

    switch(c){
        case '1': accedi(user); break;
        case '2': registrati(user); break;
    }
}

bool registrati(User* user){
    char* usernameInserito; 
    char passwordInserita[MAX_PASS_LEN];
    bool primoTentativo = false;
    User accountTemporaneo;

    do{
        system("clear");
        printf("\n\n\n\n");
        printf("\t\t-----═════════════ REGISTRATI ═══════════----- \n\n");

        if(primoTentativo){
            printf("\t\t   ⚠️  Username già utilizzato ⚠️             \n");
            printf("\t\t   Se vuoi accedere al tuo account premi [1]  \n");
            printf("\t\t                                              \n");
        }

        printf("\t\t   Inserisci un [USERNAME]: ");
        usernameInserito = richiestaUsername();
        

        if(strcmp(usernameInserito,"1") == 0){  
            free(usernameInserito);
            return accedi(user);
        }    
        primoTentativo = true;
    }while(isUserInFile(usernameInserito));
    
    strcpy(accountTemporaneo.username,usernameInserito);
    free(usernameInserito);
    
    printf("\t\t   Inserici una [PASSWORD]: ");
    scanf("%[^\n]", passwordInserita);
    getchar();
    
    
    strcpy(accountTemporaneo.password,passwordInserita);
    accountTemporaneo.bestScore = 0;
    accountTemporaneo.bestScoreGold = 0;
    accountTemporaneo.xp = 0;

    if(salvaUtenteSuFile(accountTemporaneo)){
        printf("\t\t✅ Registrazione completata!\n");
        *user = accountTemporaneo;
        return true;
    }else{
        printf("\t\t❌ Registrazione fallita!\n");
        return false;
    }   
}

bool accedi(User* user){
    char usernameInserito[MAX_NAME_LEN];
    char passwordInserita[MAX_PASS_LEN];
    bool primoTentativo = false;
    int i;
    User accountLetto, accountTemporaneo;
    FILE *puntaFile;


    do{
        system("clear");
        printf("\n\n\n\n");
        printf("\t\t-----═══════════ ACCEDI ═══════════-----\n\n");

        if(primoTentativo){
            printf("\t\t  ⚠️  Account inesistente ⚠️\n");
            printf("\t\t  Se vuoi creare un account nuovo premi [1] \n\n");
        }

        printf("\t\t  Inserisci il tuo [USERNAME]: ");
        scanf("%[^\n]", usernameInserito);
        getchar();

        if(strcmp(usernameInserito,"1") == 0){
            return registrati(user);
        }

        primoTentativo = true;

    }while(!isUserInFile(usernameInserito));

    primoTentativo = false;
    do{
        system("clear");
        printf("\n\n\n\n");
        printf("\t\t-----═══════════ ACCEDI ═══════════-----\n\n");
        
        if(primoTentativo){
            printf("\t\t  ⚠️  Password sbagliata ⚠️\n\n");
        }
        
        printf("\t\t  Username: %s\n", usernameInserito);
        printf("\t\t  Inserisci la [PASSWORD]: ");
        scanf("%[^\n]", passwordInserita);
        getchar();
        
        primoTentativo = true;

    }while(!passwordCorretta(usernameInserito, passwordInserita));

    puntaFile = fopen("./data/utenti.dat","rb"); 
    if(puntaFile == NULL){
        perror("Errore nell'apertura del file in lettura ^isUserInFile^");
        return false;
    }
    while(fread(&accountLetto,sizeof(User),1,puntaFile) == 1){
        if(strcmp(accountLetto.username,usernameInserito) == 0){
            *user = accountLetto;
            fclose(puntaFile);
            return true;
        }
    }
    fclose(puntaFile);
    return false;
}

bool isUserInFile(char* usernameInserito){
    FILE *puntaFile;
    User accountLetto;

    puntaFile = fopen("./data/utenti.dat","rb");
    if(puntaFile == NULL){
        perror("Errore nell'apertura del file in lettura ^isUserInFile^");
        return false;
    }
    while(fread(&accountLetto,sizeof(User),1,puntaFile) == 1){
        if(strcmp(accountLetto.username,usernameInserito) == 0){
            fclose(puntaFile);
            return true;
        }
    }
    fclose(puntaFile);

    return false;
}

bool salvaUtenteSuFile(User accountTemporaneo){
    User utenteCorrente;
    FILE *puntaFile = fopen("./data/utenti.dat", "rb+");

    if(puntaFile == NULL){      
        perror("Errore nell'apertura del file in scrittura ^salvaUtenteSuFile^");
        return false;
    }

    while(fread(&utenteCorrente, sizeof(User), 1, puntaFile) == 1){
        if(strcmp(utenteCorrente.username, accountTemporaneo.username) == 0){  
            fseek(puntaFile, -sizeof(User), SEEK_CUR); // Trovato utente: sovrascrivi
            fwrite(&accountTemporaneo, sizeof(User), 1, puntaFile);
            fclose(puntaFile);
            return true;
        }
    }

    fwrite(&accountTemporaneo, sizeof(User), 1, puntaFile); // Non trovato: aggiungi in fondo
    fclose(puntaFile);
    return true;
}

bool passwordCorretta(char* username, char* password){
    FILE* puntaFile = fopen("./data/utenti.dat", "rb");
    User accountLetto;

    if(puntaFile == NULL){
        perror("Errore nell'apertura del file in lettura ^passwordCorretta^");
        return false;
    }

    while(fread(&accountLetto, sizeof(User), 1, puntaFile) == 1){
        if (strcmp(accountLetto.username, username) == 0 &&
            strcmp(accountLetto.password, password) == 0) {
            fclose(puntaFile);
            return true;
        }
    }

    fclose(puntaFile);
    return false;
}

int cercaBestScore(char* username){
    FILE* puntaFile = fopen("./data/utenti.dat", "rb");
    User accountLetto;

    if(puntaFile == NULL){
        perror("Errore nell'apertura del file in lettura ^cercaBestScore^");
        return -1;
    }

    while(fread(&accountLetto, sizeof(User), 1, puntaFile) == 1){
        if(strcmp(accountLetto.username, username) == 0){
            fclose(puntaFile);
            return accountLetto.bestScore;
        }
    }

    fclose(puntaFile);
    return -1;
}

char* richiestaUsername(){
    char username[MAX_NAME_LEN + 1];
    bool flag = false;
    char* malUser;
    int result;


    do{
        result = scanf("%[^\n]", username);
        getchar();

        if(result != 1 || strlen(username) == 0 || strlen(username) > MAX_NAME_LEN){
            printf("⚠️ Username non valido. Riprova (max %d caratteri)\n", MAX_NAME_LEN);
        }
    }while(strlen(username) > MAX_NAME_LEN || strlen(username) == 0 || result != 1);

    malUser = malloc(sizeof(char)*(strlen(username)+1));
    strcpy(malUser,username);
 
    return malUser;
}