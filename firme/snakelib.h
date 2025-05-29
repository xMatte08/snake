#ifndef SNAKELIB_H
#define SNAKELIB_H

#define MAX_NAME_LEN 15
#define MAX_PASS_LEN 20
#define MAX_SCORES 286
#define MAX_TABLE 17
#define MAX_SNAKE_LEN (MAX_TABLE * MAX_TABLE)

struct s_coord {
    int x;
    int y;
};

struct s_user{
    char username[MAX_NAME_LEN];
    char password[MAX_PASS_LEN];
    int bestScore;                  //maggior numero di male mangiate in una partita
    int bestScoreGold;              //maggior numero mele d'oro magiate in una partita
    int xp;                         //xp account
};

struct s_classifica{
    char username[MAX_NAME_LEN];
    int dato;
};

typedef struct s_coord Coord;
typedef struct s_user User;
typedef struct s_classifica Classifica;

// Prototipi
void accesso(User*);
bool registrati(User*);
bool accedi(User*);
bool isUserInFile(char*);
bool salvaUtenteSuFile(User);
bool passwordCorretta(char*, char*);
int cercaBestScore(char*);
char menuPrincipale(User*);
char* richiestaUsername();
void gioco(User*);
void svuotaM(int [][MAX_TABLE]);
void aggiornaMatrice(int [][MAX_TABLE], Coord*, int ); 
void cancellaSnake(int [][MAX_TABLE], Coord*, int );
void stampaTabella(int [][MAX_TABLE],int,int);
void posizionaMela(int [][MAX_TABLE], Coord*, int );
int calcolaLivello(int xp);
int xpPerProssimoLivello(int livelloAttuale);
int calcoloMax(int max, int n);
void menuFinePartita(int, int, int, int, int);

void terminaleBloccante();
void terminaleNonBloccante();
void ripristinaTerminale();

void stampaClassifica();
int caricaClassifiche(Classifica* , Classifica* , Classifica* );
void bSortDecrescente(Classifica* , int );

#endif // SNAKELIB_
