#include "funcoes.c"

int main()
{
    setlocale(LC_ALL, "Portuguese");
    initGame();
    srand(time(NULL));
    //variável auxiliar
    char *temp;
    temp = malloc (10 * sizeof (char));
    //https://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
    Card *deck;
    deck = malloc(25 * sizeof(Card));
    for(int i = 0; i <= 24; i++){
        strcpy(deck[i].name, card[i]);
        //printf("\n%d - Nome: %s", i, deck[i].name);
    }
    printf("\n");
    //https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    //Viewmodel (*table)[5][5] = malloc(sizeof *table);
    //printf("----------------------------------------\n");
    //printf("%d\n", (*table));
    //printf("----------------------------------------\n");

    Viewmodel board[5][5];
    for(int row = 0, k = 0; row <= 4; row++){
        for(int col = 0; col <= 4; col++){
            strcpy(board[row][col].name, card[k]);
            board[row][col].state = (int)unknonw;
            //printf("%d.%d - Nome: %s / ", row,col, (*board)[row][col].name);
            //printf("Estado: %d\n", (*board)[row][col].state);
            k++;
        }
    }
    //printf("\n randomizei");
    //embaralhar deck
    for (int i = 0, tempA, tempB; i <= 24; i++){
            tempA = rand() % 25;
            tempB = rand() % 25;

            if (tempA != tempB) {
                strcpy(temp, deck[tempA].name);
                strcpy(deck[tempA].name, deck[tempB].name);
                strcpy(deck[tempB].name, temp);
            }
    }
    //embaralhar viewmodels
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            int r = rand() % 25;
            strcpy(temp, board[r / 5][r % 5].name);
            strcpy(board[r / 5][r % 5].name, board[i][j].name);
            strcpy(board[i][j].name, temp);
        }
    }
    int mode = 0;
    scanf("%d", &mode);
    if(mode == 1){
        Player *player;
        player = malloc(2 * sizeof(Player));
            if(playMode1(board, deck, player, mode) == 1){
                system("COLOR C0");
                printScreen("assas2.txt");
            }else{
                system("COLOR B0");
                printScreen("inspe2.txt");
            }
    }else{
        printf("VOCÊ ESTRAGOU!");
    };
    
}