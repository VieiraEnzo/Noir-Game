#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
//variável global para obter a carta do topo do deck
int indexDeck = 24;
//contagem dos turnos
int contTurn = 0;
int contDeath = 0;
//cria um vetor de nomes
char card[25][10] = {"Andre", "Marcos", "Ana", "Gustavo", "Giulia",
"Bernardo", "Pedro", "Miller", "Gabriela", "Alice", "Janot",
"Kaua", "Joao", "Aryck", "Lucas", "Leonardo", "Matheus",
"Rodrigo", "Beatriz", "Eduarda", "Luca", "Rebeca", "Vinicius",
"Camile", "Milena"};
//enumera os possíveis estados de cada viewmodel
enum state{
    unknonw = 1,
    inocent,
    diceased,
    assassin,
    detective
};
//base para o viewmodel(carta que fica a mostra durante o jogo)
typedef struct{
    char name[10];
    int state;
}Viewmodel;
//base para o tipo de carta
typedef struct{
    char name[10];
}Card;
//base para o player
typedef struct{
    char name[10];
    int id;
    Card handCard[5];
    int positionX;
    int positionY;
}Player;