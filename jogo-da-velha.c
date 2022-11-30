#include <stdio.h>
#include <stdlib.h>
#include<locale.h>

// usar valores booleanos de boa, com true ou false
typedef int bool;
#define true 1
#define false 0

#define linhas 4
#define colunas 4

#define X 'X'
#define O 'O'

void printarTabuleiro();
void limparTela();
void setarUtf8eLocale();
bool ocuparPosicaoTabuleiro(int x,int y,char tabuleiro[linhas][colunas], int jogador);
bool posicaoOcupada(int x,int y,char tabuleiro[linhas][colunas]);
bool alguemGanhou(char tab[linhas][colunas]);
void persistirVencedor(int jogador);

int main() {
    setarUtf8eLocale();
    char tabuleiro[linhas][colunas] ={
        '0', '1', '2', '3',    /*matriz 4 X 4*/
        '1', '.', '.', '.',
        '2', '.', '.', '.',
        '3', '.', '.', '.'};
        
    limparTela();
    printarTabuleiro(tabuleiro);

    int jogadorAtual;
    int j=0;
    while(alguemGanhou(tabuleiro)==false) {
        jogadorAtual = j%2==0? 1 : 2;

        int x;
        int y;
        printf("\nPlayer %d, digite a posição a ser marcada(x,y), ex \"3 2\": ",jogadorAtual);
        while(true) {
            scanf("%d %d",&x,&y);
            if(ocuparPosicaoTabuleiro(x,y,tabuleiro,jogadorAtual) == true)
                break;

            limparTela();
            printarTabuleiro(tabuleiro);
            printf("A posição (%d,%d) já está ocupada ('%c'), ou não é valida. Insira novamente...\n",
                x,y,tabuleiro[y][x]);
        }
        j++;
        limparTela();
        printarTabuleiro(tabuleiro);
        if(j == 9) {
            printf("Deu velha!\n");
            system("pause");
            return 0;
        }
    }

    printf("Parabéns, o jogador %d venceu!!\n",jogadorAtual);
    persistirVencedor(jogadorAtual);

    system("pause");
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
        && tab[2][1] == tab[3][1])
        return true;

    if((tab[1][2] == X || tab[1][2] == O) && tab[1][2] == tab[2][2]
        && tab[2][2] == tab[3][2])
        return true;
    
    if((tab[1][3] == X || tab[1][3] == O) && tab[1][3] == tab[2][3]
        && tab[2][3] == tab[3][3])
        return true;

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

            if (consecutivosX == 3)
                return true;
        }
    }
    return false;
}

void printarTabuleiro(char tab[linhas][colunas]) {
    printf("\n");
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

void persistirVencedor(int jogador) {
    FILE *pt_arquivo = fopen("vencedores_jogo_da_velha.txt","a+");
    if(pt_arquivo == NULL)
        printf("\nDeu merda na hr de criar o arquivo\n");

    fprintf(pt_arquivo,"Jogador %d ganhou!\n",jogador);
}

void limparTela() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
    #endif
}

void setarUtf8eLocale() {
    system("chcp 65001");
    setlocale(LC_ALL, "pt_br");
    limparTela();
}