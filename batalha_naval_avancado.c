#include <stdio.h>
#include <ctype.h>

int main (){
int tentativas = 10;
int tiros_usados = 0;
int acertos = 0;
int total_barcos = 6; // 2 barcos de 3 posições
int tiros[10][10] = {0};
char * mapa[10][10]={

{"a","b","c","d","e","f","g","h","i","j"},
{"1","0","0","0","0","0","0","0","0","0"},
{"2","0","0","0","0","0","0","0","0","0"},
{"3","0","0","0","0","0","0","0","0","0"},
{"4","0","0","0","0","0","0","0","0","0"},
{"5","0","0","0","0","0","0","0","0","0"},
{"6","0","0","0","0","0","0","0","0","0"},
{"7","0","0","0","0","0","0","0","0","0"},
{"8","0","0","0","0","0","0","0","0","0"},
{"9","0","0","0","0","0","0","0","0","0"}
};

int barco1_linhas[3] = {4,4,4};
int barco1_colunas[3] = {4,5,6};

int barco2_linhas[3]= {4,5,6};
int barco2_colunas[3]={8,8,8};

int cone[4][3] = {0};
int cruz[5][3] = {0};
int octaedro[3][3] = {0};

// CONE
cone[0][1]=1;
cone[1][0]=1; cone[1][1]=1; cone[1][2]=1;
cone[2][0]=1; cone[2][1]=1; cone[2][2]=1;
cone[3][0]=1; cone[3][1]=1; cone[3][2]=1;

// CRUZ
cruz[0][1]=1;
cruz[1][1]=1;
cruz[2][0]=1; cruz[2][1]=1; cruz[2][2]=1;
cruz[3][1]=1;
cruz[4][1]=1;

// OCTAEDRO
octaedro[0][1]=1;
octaedro[1][0]=1; octaedro[1][1]=1; octaedro[1][2]=1;
octaedro[2][1]=1;

// CONE aplicação
int origem_linha = 2;
int origem_coluna = 7;

for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {

        int l = origem_linha + i - 2;
        int c = origem_coluna + j - 1;

        if (l>=0 && l<10 && c>=0 && c<10) {
            if (cone[i][j]==1 && mapa[l][c][0]=='0') {
                mapa[l][c] = "5";
            }
        }
    }
}

// BARCOS
for (int i = 0; i < 3; i++) {
    mapa[barco1_linhas[i]][barco1_colunas[i]] = "3";
    mapa[barco2_linhas[i]][barco2_colunas[i]] = "3";
}

// PRINT
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {

        if (i == 0 || j == 0) {
            printf("%s\t", mapa[i][j]);
        } else {
            printf("~\t");
        }

    }
    printf("\n");
}

while (1) {

    char coluna_char;
    int linha;

    printf("\nDigite coordenada (A5) ou S para sair: ");
    scanf(" %c", &coluna_char);
    tiros_usados++;

    // SAIR DO JOGO
    if (toupper(coluna_char) == 'S') {
        printf("Saindo do jogo...\n");
        break;
    }

    scanf("%d", &linha);

    coluna_char = toupper(coluna_char);
    int coluna = coluna_char - 'A';

    // VALIDAÇÃO
    if (coluna < 0 || coluna >= 10 || linha < 0 || linha >= 10) {
        printf("Coordenada invalida!\n");
        continue;
    }

    // RESULTADO
    if (tiros[linha][coluna] == 1) {
    printf("Voce ja atirou aqui!\n");
    continue;
}
//marcar o tiro
tiros[linha][coluna] = 1;
    if (mapa[linha][coluna][0] == '3') {
    printf(" Acertou um barco!\n");
    acertos++;
    }else if (mapa[linha][coluna][0] == '5') {
    printf(" Area especial! Voce ganhou +2 tiros!\n");
    tentativas += 2;
    } else {
        printf("Agua!\n");
    }
//sistema de vitoria
    if (acertos == total_barcos) {
    printf("\n VOCE VENCEU! Todos os barcos foram destruidos!\n");
    break;
}
//sistema de derrota
if (tiros_usados == tentativas) {
    printf("\n Fim de jogo! Acabaram suas tentativas.\n");
    break;
}

    // PRINT MAPA
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {

        if (i == 0 || j == 0) {
            // cabeçalho
            printf("%s\t", mapa[i][j]);
        }
        else if (tiros[i][j] == 1) {

            if (mapa[i][j][0] == '3' || mapa[i][j][0] == '5') {
                printf("*\t"); // acerto
            } else {
                printf("X\t"); // erro
            }

        } else {
            printf("~\t"); // ainda não atirou
        }
    }
    printf("\n");
}
}
}
