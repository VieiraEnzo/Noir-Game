//Chama todas as estrturas utilizadas pelo projeto
#include "estruturas.c"
//limpa o terminal
void cleanTerminal(){
    system("cls");
}
//pega a janela do terminal
HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}
//função que prepara a janela e printa o menu inicial
void initGame(){
    //pega o handler
    HWND hWnd=GetConsoleWindowNT();
    //define os valores para a janela e posição
    MoveWindow(hWnd,240,28,1440,1024,TRUE);
    //impede o redimensionamento
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    //limpa o terminal
    cleanTerminal();
    //constante que corresponde ao num. de caracteres
    const int sz = 255;
    //cria a string
    char str[sz];
    //cria um ponteiro para do tipo FILE, para manusear o arquivo
    FILE *fp;
    //abre o arquivo especifica com a logo, o "r" especifica que o arquivo sera usado para entrada
    fp = fopen("noir_logo.txt","r");
    if(fp == NULL){
        // opening the file failed ... handle it
    }
    while (fgets(str,sz,fp)!=NULL){
        wprintf(L"%s",str);
    };
    fclose(fp);
}

//função para compra de carta
Card buyCard(Card *deck){
    //pega a carta do topo do deck
    Card c = deck[indexDeck];
    //printf("%s", deck[indexDeck].name);
    //realoca a memória pra quantidade de cartas -1
    deck = (Card *)realloc(deck, sizeof(Card)*(indexDeck));
    //diminui uma carta na variavel
    indexDeck--;
    return c;

}


void printScreen(char screen[11]){
    cleanTerminal();
    const int sz = 255;
    char str[sz];
    FILE *fp;
    fp = fopen(screen,"r");
    if(fp == NULL){
        // opening the file failed ... handle it
    }
    while (fgets(str,sz,fp)!=NULL){
        wprintf(L"%s",str);
    };
    fclose(fp);
    printf ("\033[0;37m");
}

int checkRange(int pY, int pX, Player player){
    int aux = 0;
    if((player.positionY != pY) || ((player.positionX != pX))){
        if((pY >= (player.positionY-1)) && (pY <= (player.positionY+1))){
            if((pX >= (player.positionX - 1)) && (pX <= (player.positionX + 1))){
                aux = 1;
            }
        }
    }

    return aux;
}

int playMode1(Viewmodel board[5][5], Card *deck, Player *player, int mode){
    //variaveis auxiliares
    int gameOver = 0;
    int acao = 0;
    int check;
    char auxS[255];
    int auxX;
    int auxY;
    Viewmodel auxc;
    int auxInt;
    int aux2 = 0;
    //compra a carta do assasino e deposita em sua mão
    player[0].handCard[0] = buyCard(deck);
    //define o receptáculo do player
    strcpy(player[0].name, player[0].handCard[0].name);
    //printf("%s", player[0].handCard[0].name);
    //strcpy(player[0].name, buyCard(deck).name);
    //define o player como assassino
    player[0].id = (int)assassin;
    //define o player como detective
    player[1].id = (int)detective;
    //compra 3 cartas do deck e deposita na mão do detective
    for(int i = 0; i <= 3; i++){
        player[1].handCard[i] = buyCard(deck);
    }
    //looping de jogo
    while(gameOver == 0){
        if(contDeath == 16){
            return 1;
        }
        //variável auxiliar
        auxX = 6;
        auxY = 6;
        check = 0;
        //if que verifica se é o turno do assassino ou detective
        if((contTurn == 0) || (contTurn%2 == 0)){
            //se turno do assassino
            //muda a cor para vermelho
            printf ("\033[0;31m");
            //printa tela do assassin
            printScreen("assas1.txt");
            //pause
            fflush(stdin);
            getchar();
            //limpa terminal
            cleanTerminal();
            //pega as posições dos players
            for(int z = 0; z <= 1; z++){
                for(int i = 0; i <= 4; i++){
                    for(int j = 0; j<= 4; j++){
                        if(strcmp(player[z].name, board[i][j].name) == 0){
                            player[z].positionY = i;
                            player[z].positionX = j;
                            //printf("%s, (%d, %d)", player[z].name, player[z].positionY, player[z].positionX);
                        }
                    }
                }
            }
            //imprime board
            for(int i = 0; i <= 4; i++){
                for(int j = 0; j<= 4; j++){
                    if(board[i][j].state == (int)diceased){
                        printf ("\033[0;31m");
                    }else if(board[i][j].state == (int)inocent){
                        printf ("\033[0;32m");
                    }
                    printf("| %s |", board[i][j].name);
                    printf ("\033[0;37m");
                }
                printf("\n");
            }
            //entra no looping de acao
            while(check == 0){
                //printa as informações do assassino
                printf("\n");
                printf("SUA IDENTIDADE ATUAL É: %s", player[0].name);
                printf("\n");
                printf("\n");
                printf("ESCOLHA SUA AÇÃO:\n");
                printf("1. MATAR\n");
                printf("2. DISFARCE\n");
                printf("3. SHIFT\n");
                scanf("%d", &acao);
                fflush(stdin);
                //switch de açoes
                switch (acao)
                {
                //caso acao 1
                case 1:
                    printf("ESCOLHA SEU ALVO.\n");
                    scanf("%s", &auxS);
                    for(int i = 0; i <= 4; i++){
                        for(int j = 0; j <= 4; j++){
                            if(strcmp(auxS, board[i][j].name) == 0){
                                auxY = i;
                                auxX = j;
                            }
                        }
                    }
                    //printf("POSICAO DO ALVO: (%d, %d) \n", auxY, auxX);
                    //printf("MINHA POSICAO: (%d, %d) \n", player[0].positionY, player[0].positionX);
                    //verifica as distâncias
                    if(checkRange(auxY, auxX, player[0]) == 0){
                        printf("ALVO INVÁLIDO! INFORME UM ALVO QUE ESTEJA A SUA VOLTA.\n");
                    }else if((auxY == player[1].positionY)&&(auxX == player[1].positionX)){
                        check = 1;
                        return 1;
                    }else if(board[auxY][auxX].state == (int)diceased){
                        printf("O ALVO ESCOLHIDO ESTÁ MORTO.\n");
                        printf("ESCOLHA UM ALVO VÁLIDO.\n");
                    }else{
                        //altera o state de viewModel
                        contDeath++;
                        board[auxY][auxX].state = (int)diceased;
                        printf("PARABÉNS VOCÊ MATOU COM SUCESSO\n");
                        //altera o valor de check para sair do while
                        check = 1;
                        fflush(stdin);
                        getchar();
                    }
                    break;

                case 2:
                    //compra uma carta e a deposita na mão do assassino
                    player[0].handCard[1] = buyCard(deck);
                    //pega a posição da carta comprada
                    for(int i = 0; i <= 4; i++){
                        for(int j = 0; j <= 4; j++){
                            if(strcmp(player[0].handCard[1].name, board[i][j].name) == 0){
                                auxY = i;
                                auxX = j;
                            }
                        }
                    }
                    //verifica se a carta esta viva
                    if(board[auxY][auxX].state == (int)diceased){
                        //se o viewmodel correspondente a carta estiver morto, o jogador perde a vez
                        printf("A CARTA QUE VOCE COMPROU CORRESPONDE A UM PERSONAGEM MORTO!\n");
                        printf("VOCE PERDEU A VEZ!\n");
                        check = 1;
                        fflush(stdin);
                        getchar();
                    }else{
                        //se a carta corresponder a um viewmodel vivo, o jogador toma uma decisão
                        //looping para decisão
                        while(check == 0){
                            printf("SEU DISFARCE ATUAL É: %s\n", player[0].name);
                            printf("DESEJA ALTERAR PARA: %s? \n", player[0].handCard[1].name);
                            printf("Digite 'sim' ou 'nao'.");
                            scanf("%s", &auxS);
                            if(strcmp(auxS, "nao") == 0){
                                //altera o estado do viewmodel correspondente a carta retirada
                                board[auxY][auxX].state = (int)diceased;
                                //mantem o disfarce antigo
                                printf("AÇÃO COMPUTADA \n");
                                printf("SEU DISFARCE ATUAL É: %s\n", player[0].name);
                                check = 1;
                                fflush(stdin);
                                getchar();
                            }else if(strcmp(auxS, "sim") == 0){
                                //atualiza o disfarce do assassino
                                strcpy(player[0].name, player[0].handCard[1].name);
                                //muda o status do disfarce passado para morto
                                board[player[0].positionY][player[0].positionX].state = (int)diceased;
                                printf("AÇÃO COMPUTADA \n");
                                printf("SEU DISFARCE ATUAL É: %s\n", player[0].name);
                                check = 1;
                                fflush(stdin);
                                getchar();
                            }else{
                                printf("AÇÃO INVÁLIDA!");
                            }
                        }
                    }
                    break;

                case 3:
                    printf("VOCÊ DESEJA UTILIZAR O 'SHIFT' NA COLUNA OU LINHA? RESPONDA COM 'linha' ou  'coluna'.\n");
                    scanf("%s", &auxS);
                    if(strcmp(auxS, "linha") == 0){
                        printf("ESCOLHA O SENTIDO: 'direita' ou 'esquerda'.\n");
                        scanf("%s", &auxS);
                        if(strcmp(auxS, "esquerda") == 0){
                            printf("ESCOLHA QUAL 'LINHA' IRÁ RECEBER O SHIFT\n");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[auxInt][0];
                            for(int i = 0; i < 4; i++){
                                board[auxInt][i] = board[auxInt][i+1]; 
                            }
                            board[auxInt][4] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else if(strcmp(auxS, "direita") == 0){
                            printf("ESCOLHA QUAL 'LINHA' IRÁ RECEBER O SHIFT\n");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[auxInt][4];
                            for(int i = 4; i > 0; i--){
                                board[auxInt][i] = board[auxInt][i-1]; 
                            }
                            board[auxInt][0] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else{
                            printf("VALOR INVÁLIDO");
                        }
                    }else if(strcmp(auxS, "coluna") == 0){
                        printf("ESCOLHA O SENTIDO: 'subir' ou 'descer'.");
                        scanf("%s", &auxS);
                        if(strcmp(auxS, "subir") == 0){
                            printf("ESCOLHA QUAL 'COLUNA' IRÁ RECEBER O SHIFT");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[0][auxInt];
                            for(int i = 0; i < 4; i++){
                                board[i][auxInt] = board[i+1][auxInt]; 
                            }
                            board[4][auxInt] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else if(strcmp(auxS, "descer") == 0){
                            printf("ESCOLHA QUAL 'COLUNA' IRA RECEBER O SHIFT");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[4][auxInt];
                            for(int i = 4; i > 0; i--){
                                board[i][auxInt] = board[i-1][auxInt]; 
                            }
                            board[0][auxInt] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else{
                            printf("VALOR INVÁLIDO");
                        }
                    }else{
                        printf("VALOR INVÁLIDO\n");
                    }

                    break;

                default:
                    printf("ESCOLHA UMA AÇÃO VÁLIDA\n");
                    break;
                }
            }

        }else{
            //se turno do detective
            //printa tela do detective
            printScreen("inspe1.txt");
            //pause
            fflush(stdin);
            getchar();
            //limpa terminal
            cleanTerminal();
            //imprime board
            for(int i = 0; i <= 4; i++){
                for(int j = 0; j<= 4; j++){
                    if(board[i][j].state == (int)diceased){
                        printf ("\033[0;31m");
                    }else if(board[i][j].state == (int)inocent){
                        printf ("\033[0;32m");
                    }
                    printf("| %s |", board[i][j].name);
                    printf ("\033[0;37m");
                }
                printf("\n");
            }
            //detecta o primeiro turno do detective
            if(contTurn == 1){
                while(aux2 == 0){
                    printf("\n");
                    printf("ESCOLHA SUA IDENTIDADE (utilize os números para escolher):\n");
                    printf("\n");
                    //printa as cartas da mão do detective
                    for(int i = 0; i <= 3; i++){
                        printf(" - %s (%d)", player[1].handCard[i].name, i);
                    }
                    printf("\n");
                    //recebe a carta escolhida
                    scanf("%d", &auxInt);
                    fflush(stdin);
                    for(int i = 0; i <= 4; i++){
                        for(int j = 0; j <= 4; j++){
                            if(strcmp(player[1].handCard[auxInt].name, board[i][j].name) == 0){
                                auxY = i;
                                auxX = j;
                            }
                        }
                    }
                    //printf("%s", board[auxY][auxX].name);
                    //printf("%d", board[auxY][auxX].state);
                    if(board[auxY][auxX].state != (int)diceased){
                        aux2 = 1;
                    }else{
                        printf("ESTÁ IDENTIDADE ESTÁ MORTA.\n");
                        printf("ESCOLHA UMA IDENTIDADE VÁLIDA.\n");
                    }
                }
                //define a identidade do detective
                strcpy(player[1].name, player[1].handCard[auxInt].name);
                //transporta a carta escolhida para a última posição da mão do detective
                player[1].handCard[4] = player[1].handCard[auxInt];
                //move todas as cartas a direita da escolhida para a esquerda
                for(int i = auxInt; i <= 3; i++){
                    player[1].handCard[i] = player[1].handCard[i+1];
                }
                printf("IDENTIDADE DEFINIDA COM SUCESSO");
            }
            //pega as posições dos players
            for(int z = 0; z <= 1; z++){
                for(int i = 0; i <= 4; i++){
                    for(int j = 0; j<= 4; j++){
                        if(strcmp(player[z].name, board[i][j].name) == 0){
                            player[z].positionY = i;
                            player[z].positionX = j;
                            //printf("%s, (%d, %d)", player[z].name, player[z].positionY, player[z].positionX);
                        }
                    }
                }
            }
            //printa as informações do detective
            printf("\n");
            printf("SUA IDENTIDADE ATUAL E: %s", player[1].name);
            printf("\n");
            printf("ESCOLHA SUA ACAO:\n");
            printf("1. INSPECIONAR\n");
            printf("2. COMPRAR UMA CARTA\n");
            printf("3. SHIFT\n");
            scanf("%d", &acao);
            //entra no looping de acao
            while(check == 0){
                switch (acao)
                {
                case 1:
                    for(int i = 0; i <= 2; i++){
                        printf("%s (%d) -", player[1].handCard[i].name, i);
                    }
                    printf("\n");
                    printf("ESCOLHA SEU ALVO.\n");
                    scanf("%s", &auxS);
                    for(int i = 0; i <= 4; i++){
                        for(int j = 0; j <= 4; j++){
                            if(strcmp(auxS, board[i][j].name) == 0){
                                auxY = i;
                                auxX = j;
                            }
                        }
                    }
                    if(checkRange(auxY, auxX, player[1]) == 0){
                        printf("ALVO INVALIDO! INFORME UM ALVO QUE ESTEJA A SUA VOLTA.\n");
                    }else if(board[auxY][auxX].state == (int)diceased){
                        printf("SELECIONE UM ALVO QUE NAO ESTEJA MORTO.\n");
                        //altera o valor de check para sair do while
                    }else if(strcmp(board[auxY][auxX].name, player[0].name) == 0){
                        return 2;
                    }else{
                        printf("O ALVO SELECIONADO NAO E O ASSASSINO. \n");
                        check = 1;
                        fflush(stdin);
                        getchar();
                    }
                    break;

                case 2:
                    printf("\n");
                    //compra uma carta e aloca no quarto slot da mão do detective
                    player[1].handCard[3] = buyCard(deck);
                    for(int i = 0; i <= 3; i++){
                        //printa todas as cartas
                        printf(" - %s (%d)", player[1].handCard[i].name, i);
                    }
                    printf("\n");
                    printf("ESCOLHA QUAL CARTA IRA DESCARTAR (utilize os números):\n");
                    scanf("%d", &auxInt);
                    //pega a posição da carta descartada na mesa
                    for(int i = 0; i <= 4; i++){
                        for(int j = 0; j <= 4; j++){  
                            if(strcmp(player[1].handCard[auxInt].name, board[i][j].name) == 0){
                                auxY = i;
                                auxX = j;
                            }
                        }
                    }
                    //verifica se a carta descartada não corresponde a um personagem morto
                    if(board[auxY][auxX].state == (int)diceased){
                        printf("A CARTA DESCARTADA CORRESPONDE A UM PERSONAGEM MORTO\n");
                        check = 1;
                    }else{
                        printf("CARTA DESCARTADA COM SUCESSO\n");
                        //muda o status do viewmodel correspondente a carta para inocente
                        board[auxY][auxX].state = (int)inocent;
                        check = 1;
                    }
                    //reposiciona as cartas na mão do detective
                    for(int i = auxInt; i <= 3; i++){
                        player[1].handCard[i] = player[1].handCard[i+1];
                    }
                    fflush(stdin);
                    getchar();
                    break;

                case 3:
                    printf("VOCE DESEJA UTILIZAR O 'SHIFT' NA COLUNA OU LINHA? RESPONDA COM 'linha' ou  'coluna'.\n");
                    scanf("%s", &auxS);
                    if(strcmp(auxS, "linha") == 0){
                        printf("ESCOLHA O SENTIDO: 'direita' ou 'esquerda'.\n");
                        scanf("%s", &auxS);
                        if(strcmp(auxS, "esquerda") == 0){
                            printf("ESCOLHA QUAL 'LINHA' IRÁ RECEBER O SHIFT\n");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[auxInt][0];
                            for(int i = 0; i < 4; i++){
                                board[auxInt][i] = board[auxInt][i+1]; 
                            }
                            board[auxInt][4] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else if(strcmp(auxS, "direita") == 0){
                            printf("ESCOLHA QUAL 'LINHA' IRÁ RECEBER O SHIFT\n");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[auxInt][4];
                            for(int i = 4; i > 0; i--){
                                board[auxInt][i] = board[auxInt][i-1]; 
                            }
                            board[auxInt][0] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else{
                            printf("VALOR INVALIDO");
                        }
                    }else if(strcmp(auxS, "coluna") == 0){
                        printf("ESCOLHA O SENTIDO: 'subir' ou 'descer'.");
                        scanf("%s", &auxS);
                        if(strcmp(auxS, "subir") == 0){
                            printf("ESCOLHA QUAL 'COLUNA' IRÁ RECEBER O SHIFT");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[0][auxInt];
                            for(int i = 0; i < 4; i++){
                                board[i][auxInt] = board[i+1][auxInt]; 
                            }
                            board[4][auxInt] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else if(strcmp(auxS, "descer") == 0){
                            printf("ESCOLHA QUAL 'COLUNA' IRÁ RECEBER O SHIFT");
                            scanf("%d", &auxInt);
                            auxInt = auxInt - 1;
                            auxc = board[4][auxInt];
                            for(int i = 4; i > 0; i--){
                                board[i][auxInt] = board[i-1][auxInt]; 
                            }
                            board[0][auxInt] = auxc;
                            printf("SHIFT FEITO COM SUCESSO\n");
                            check = 1;
                            fflush(stdin);
                            getchar();
                        }else{
                            printf("VALOR INVALIDO");
                        }
                    }else{
                        printf("VALOR INVALIDO\n");
                    }
                    break;
                default:
                    break;
                }
            }
        }
        contTurn++;
    }
}