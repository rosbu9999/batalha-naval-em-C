#include <stdio.h>
#include <ctype.h>

int main (){
int tentativas = 10;
int tiros_usados = 0;
int acertos = 0;
int total_barcos = 6;

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

// cone
cone[0][1]=1;
cone[1][0]=1; cone[1][1]=1; cone[1][2]=1;
cone[2][0]=1; cone[2][1]=1; cone[2][2]=1;
cone[3][0]=1; cone[3][1]=1; cone[3][2]=1;

int cone_linha = 5;
int cone_coluna = 5;

// colocar o cone no mapa
for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {

        int l = cone_linha + i - 2;
        int c = cone_coluna + j - 1;

        if (l >= 0 && l < 10 && c >= 0 && c < 10) {
            if (cone[i][j] == 1 && mapa[l][c][0] == '0') {
                mapa[l][c] = "6"; // cone
            }
        }
    }
}
//Area especial
mapa[2][2] = "5";
mapa[2][3] = "5";
mapa[2][4] = "5";
mapa[3][2] = "5";
mapa[3][3] = "5";
mapa[3][4] = "5";
mapa[4][2] = "5";
mapa[4][3] = "5";
mapa[4][4] = "5";
// Barcos
for (int i = 0; i < 3; i++) {
    mapa[barco1_linhas[i]][barco1_colunas[i]] = "3";
    mapa[barco2_linhas[i]][barco2_colunas[i]] = "3";
}

// Print do inicio
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        if (i == 0 || j == 0)
            printf("%s\t", mapa[i][j]);
        else
            printf("~\t");
    }
    printf("\n");
}

while (1) {

    char coluna_char;
    int linha;

    printf("\nTentativas: %d/%d\n", tiros_usados, tentativas);
    printf("Digite coordenada (A5) ou S para sair: ");

    scanf(" %c", &coluna_char);

    if (toupper(coluna_char) == 'S') {
        printf("Saindo...\n");
        break;
    }

    scanf("%d", &linha);

    coluna_char = toupper(coluna_char);
    int coluna = coluna_char - 'A';

    // validação
    if (coluna < 0 || coluna >= 10 || linha < 0 || linha >= 10) {
        printf("Coordenada invalida!\n");
        continue;
    }

    if (tiros[linha][coluna] == 1) {
        printf("Ja atirou aqui!\n");
        continue;
    }

    tiros[linha][coluna] = 1;
    tiros_usados++;

    // resultado
    if (mapa[linha][coluna][0] == '3') {
        printf("Acertou barco!\n");
        acertos++;
    } 
    else if (mapa[linha][coluna][0] == '6') {
        printf("acertou o cone, perdeu +1 tentativa!\n");
        tiros_usados++; // penalidade do cone
    } else if(mapa[linha][coluna] == "5"){
        printf("Parabéns, você acertou a aréa especial, ganhou +2 tentativas\n");
        tentativas += 3;
    }
    else {
        printf("Agua!\n");
    }

    // vitória
    if (acertos == total_barcos) {
        printf("\nParabéns! você venceu o jogo\n");
        break;
    }

    // derrota
    if (tiros_usados >= tentativas) {
        printf("\nPerdeu! Acabaram as tentativas\n");
        break;
    }

    // PRINT
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {

            if (i == 0 || j == 0) {
                printf("%s\t", mapa[i][j]);
            }
            else if (tiros[i][j] == 1) {

                if (mapa[i][j][0] == '3')
                    printf("*\t"); // barco
                else if (mapa[i][j][0] == '6')
                    printf("C\t"); // cone
                else if(mapa[i][j][0] == '5'){
                    printf("S\t");//aréa especial
                }
                else
                    printf("X\t"); // erro

            } else {
                printf("~\t");
            }
        }
        printf("\n");
    }
}

return 0;
}
