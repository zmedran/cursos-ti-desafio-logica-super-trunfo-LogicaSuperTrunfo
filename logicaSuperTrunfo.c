#include <stdio.h>
#include <stdbool.h>

// Definicao da estrutura da carta
typedef struct {
    char Estado[50];
    char CharCarta[3];
    char Codigocarta[5];
    char Cidade[50];
    unsigned long int Populacao;
    int Pontos_turisticos, Numcarta;
    float Area, Densidadepopu, PIB_percap, SuperPoder;
    double PIB;
} Carta;

// Enum para os atributos das cartas
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    DENSIDADE_POPULACIONAL,
    PIB_PERCAPITA
} Atributo;

// Funcao para entrada de dados da carta
void EntradaDados(Carta *carta) {
    printf("\nDigite o Estado da carta: ");
    scanf(" %49[^\n]", carta->Estado);
    
    printf("Digite uma letra de (A-H) para carta: ");
    scanf(" %2s", carta->CharCarta);
    
    printf("Digite o numero da carta (01 a 04): ");
    scanf("%d", &carta->Numcarta);
    carta->Numcarta = ((carta->Numcarta - 1) % 4) + 1;
    
    sprintf(carta->Codigocarta, "%s%02d", carta->CharCarta, carta->Numcarta);
    
    printf("Digite a cidade da carta: ");
    scanf(" %49[^\n]", carta->Cidade);
    
    printf("Digite a populacao: ");
    scanf("%lu", &carta->Populacao);
    
    printf("Digite a area em km: ");
    scanf("%f", &carta->Area);
    
    printf("Digite o PIB (em bilhoes): ");
    scanf("%lf", &carta->PIB);
    
    printf("Digite a quantidade de pontos turisticos: ");
    scanf("%d", &carta->Pontos_turisticos);
}

// Funcao para calcular valores derivados
void CalculoVariavel(Carta *carta) {
    carta->Densidadepopu = carta->Populacao / carta->Area;
    carta->PIB_percap = (carta->PIB * 1e9) / carta->Populacao;
    carta->SuperPoder = carta->Populacao + carta->Area + carta->PIB +
                        carta->Pontos_turisticos + carta->PIB_percap +
                        (carta->Area / carta->Populacao);
}

// Funcao para comparar cartas
int Comparar_Cartas(Carta carta1, Carta carta2, Atributo atributo) {
    float valor1, valor2;
    int vencedor = 0;

    switch (atributo) {
        case POPULACAO:
            valor1 = carta1.Populacao;
            valor2 = carta2.Populacao;
            break;
        case AREA:
            valor1 = carta1.Area;
            valor2 = carta2.Area;
            break;
        case PIB:
            valor1 = carta1.PIB;
            valor2 = carta2.PIB;
            break;
        case DENSIDADE_POPULACIONAL:
            valor1 = carta1.Densidadepopu;
            valor2 = carta2.Densidadepopu;
            break;
        case PIB_PERCAPITA:
            valor1 = carta1.PIB_percap;
            valor2 = carta2.PIB_percap;
            break;
        default:
            printf("Atributo invalido!\n");
            return 0;
    }

    printf("\nComparacao do atributo %d:\n", atributo);
    printf("Carta 1 (%s): %.2f\n", carta1.Cidade, valor1);
    printf("Carta 2 (%s): %.2f\n", carta2.Cidade, valor2);

    if (atributo == DENSIDADE_POPULACIONAL) {
        if (valor1 < valor2) vencedor = 1;
        else if (valor1 > valor2) vencedor = 2;
    } else {
        if (valor1 > valor2) vencedor = 1;
        else if (valor1 < valor2) vencedor = 2;
    }

    if (vencedor == 1) 
        printf("Resultado: Carta 1 (%s) venceu!\n", carta1.Cidade);
    else if (vencedor == 2) 
        printf("Resultado: Carta 2 (%s) venceu!\n", carta2.Cidade);
    else 
        printf("Resultado: Empate!\n");

    return vencedor;
}

int main() {
    Carta carta1, carta2;
    int pontos1 = 0, pontos2 = 0;
    bool atributosUsados[5] = {false, false, false, false, false};
    int rodadas = 0;

    printf("Insira os dados da primeira carta:\n");
    EntradaDados(&carta1);
    printf("Insira os dados da segunda carta:\n");
    EntradaDados(&carta2);

    CalculoVariavel(&carta1);
    CalculoVariavel(&carta2);

    while (rodadas < 5) {
        int escolha;

        printf("\nEscolha um atributo para a rodada:\n");
        if (!atributosUsados[0]) printf("1 - Populacao\n");
        if (!atributosUsados[1]) printf("2 - Area\n");
        if (!atributosUsados[2]) printf("3 - PIB\n");
        if (!atributosUsados[3]) printf("4 - Densidade Populacional\n");
        if (!atributosUsados[4]) printf("5 - PIB per capita\n");

        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > 5 || atributosUsados[escolha - 1]) {
            printf("Atributo invalido ou ja utilizado!\n");
            continue;
        }

        atributosUsados[escolha - 1] = true;
        rodadas++;

        int resultado = Comparar_Cartas(carta1, carta2, (Atributo)escolha);
        if (resultado == 1) pontos1++;
        else if (resultado == 2) pontos2++;
    }

    printf("\nPlacar final:\n");
    printf("Carta 1: %d pontos\n", pontos1);
    printf("Carta 2: %d pontos\n", pontos2);

    if (pontos1 > pontos2)
        printf("\nVencedor final: Carta 1 (%s)!\n", carta1.Cidade);
    else if (pontos2 > pontos1)
        printf("\nVencedor final: Carta 2 (%s)!\n", carta2.Cidade);
    else
        printf("\nEmpate geral!\n");

    return 0;
}