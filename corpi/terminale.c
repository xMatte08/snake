#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include "snakelib.h"

void terminaleBloccante(){
    struct termios t;

    tcgetattr(STDIN_FILENO, &t); // Legge le impostazioni attuali del terminale
    t.c_lflag &= ~(ICANON | ECHO); // Disattiva modalità canonica ed echo

    // Imposta VMIN e VTIME per lettura bloccante
    t.c_cc[VMIN] = 1;   // Attende almeno 1 carattere
    t.c_cc[VTIME] = 0;  // Nessun timeout
    
    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Applica le modifiche immediatamente
}

void terminaleNonBloccante(){
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO); // disattiva modalità canonica ed eco
    t.c_cc[VMIN] = 1;              // opzionale: minimo 1 carattere per read
    t.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    // Aggiunge O_NONBLOCK ai flag già presenti
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void ripristinaTerminale(){
    struct termios t;
   
    tcgetattr(STDIN_FILENO, &t); // Legge le impostazioni correnti
    t.c_lflag |= (ICANON | ECHO); // Riattiva modalità canonica ed echo

    // Valori standard per input canonico
    t.c_cc[VMIN] = 1;
    t.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &t); // Applica immediatamente le modifiche

    // Rimuove il flag O_NONBLOCK (lettura bloccante)
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    flags &= ~O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);
}