#include <stdio.h>
#include <stdlib.h>

// usar valores booleanos de boa, com true ou false
typedef int bool;
#define true 1
#define false 0

#define linhas 4
#define colunas 4
#define jogadasMinimas 3

#define X 'X'
#define O 'O'

void printarTabuleiro();
void limparTela();
bool ocuparPosicaoTabuleiro(int x,int y,char tabuleiro[linhas][colunas], int jogador);
bool posicaoOcupada(int x,int y,char tabuleiro[linhas][colunas]);
bool alguemGanhou(char tab[linhas][colunas]);

int main() {
    char tabuleiro[linhas][colunas] ={
        '0', '1', '2', '3',    /*matriz 4 X 4*/
        '1', '.', '.', '.',
        '2', '.', '.', '.',
        '3', '.', '.', '.'};
        
    printf(" ");
    limparTela();
    printarTabuleiro(tabuleiro);

    int jogadorAtual;
    int j=0;
    while(j<jogadasMinimas||alguemGanhou(tabuleiro)==false) {
        if(j%2==0)
            jogadorAtual = 1;
        else
            jogadorAtual = 2;

        int x;
        int y;
        printf("\nPlayer %d, digite a posicao a ser marcada(x,y), ex \"3 2\": ",jogadorAtual);
        while(true) {
            scanf("%d %d",&x,&y);
            if(ocuparPosicaoTabuleiro(x,y,tabuleiro,jogadorAtual) == true)
                break;

            // limparTela();
            printarTabuleiro(tabuleiro);
            printf("A posição (%d,%d) já está ocupada ('%c'), ou não é valida. Insira novamente...\n",
                x,y,tabuleiro[y][x]);
        }
        j++;
        // limparTela();
        printarTabuleiro(tabuleiro);
    }
    // for(int j=0;j<jogadasMinimas||alguemGanhou()==false;j++) {
    //     if(j%2==0)
    //         jogadorAtual = 1;
    //     else
    //         jogadorAtual = 2;

    //     int x;
    //     int y;
    //     printf("\nPlayer %d,Digite a posicao a ser marcada(x,y), ex \"3 2\": ",jogadorAtual);
    //     while(true) {
    //         scanf("%d %d",&x,&y);
    //         if(ocuparPosicaoTabuleiro(x,y,tabuleiro,jogadorAtual) == false) {
    //             limparTela();
    //             printarTabuleiro(tabuleiro);
    //             printf("A posição (%d,%d) já está ocupada ('%c'), ou não é valida. Insira novamente...\n",
    //                 x,y,tabuleiro[y][x]);
    //             continue;
    //         }
    //         break;
    //     }
    //     limparTela();
    //     printarTabuleiro(tabuleiro);
    // }

    printf("Parabéns, o jogador %d venceu!!",jogadorAtual);
    return 0;
}

bool ocuparPosicaoTabuleiro(int x,int y,char tabuleiro[linhas][colunas], int jogador) {
    if(posicaoOcupada(x,y,tabuleiro)==true)
        return false;
    
    char charJogador = jogador==1? X : O;

    tabuleiro[y][x] = charJogador;
    return true;
}

bool alguemGanhou(char tab[linhas][colunas]) {
    // checar consecutivos na vertical
    if((tab[1][1] == X || tab[1][1] == O) && tab[1][1] == tab[2][1]
        && tab[2][1] == tab[3][1]) {
        printf("\nconsecY\n");
        printf("1 1: %2c",tab[1][1]);
        return true;
    }

    if((tab[1][2] == X || tab[1][2] == O) && tab[1][2] == tab[2][2]
        && tab[2][2] == tab[3][2]) {
        printf("\nconsecY\n");
        return true;
    }
    
    if((tab[1][3] == X || tab[1][3] == O) && tab[1][3] == tab[2][3]
        && tab[2][3] == tab[3][3]) {    
        printf("\nconsecY\n");
        return true;
    }

    // checar consecutivos na diagonal
    if((tab[1][1] == X || tab[1][1] == O)&&tab[1][1] == tab[2][2]
        && tab[2][2] == tab[3][3])
        return true;

    if((tab[1][3] == X || tab[1][3] == O)&&tab[1][3] == tab[2][2]
        && tab[2][2] == tab[3][1])
        return true;

    // checar consecutivos na horizontal
    for(int r=1;r<linhas;r++) {
        int consecutivosX = 1;
        for(int c=1;c<colunas;c++) {
            if((tab[r][c] == X || tab[r][c] == O) && tab[r][c] == tab[r][c-1]) 
                consecutivosX++;

            if (consecutivosX == 3) {
                printf("\nconsecX na linha %d\n",r);
                return true;
            }
        }
        printf("\nconsecX na linha %d: %d\n",r,consecutivosX);
    }
    return false;
}

void printarTabuleiro(char tab[linhas][colunas]) {
    for(int l=0;l<linhas;l++) {
        printf("\t");
        for(int c=0;c<colunas;c++)
            printf("%c  ",tab[l][c]);
        printf("\n");
    }
    printf("\n");
}

bool posicaoOcupada(int x,int y,char tabuleiro[linhas][colunas]) {
    if(x >= colunas || y >= linhas
        || x < 1 || y < 1)
        return true;
    return (tabuleiro[y][x] == X || tabuleiro[y][x] == O);
}

void limparTela() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}