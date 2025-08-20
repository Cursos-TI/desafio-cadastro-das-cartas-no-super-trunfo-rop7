#include <stdio.h>
#include <cjson/cJSON.h>
#include "jsonManage.h"

// Desafio Super Trunfo - Países
// Tema 1 - Cadastro das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de cadastro de cartas de cidades.

int main() {

    int codigo;
    char nome[100];
    int populacao;
    int area;
    int pib;
    int pontosTuristicos;

    printf("Digite o codigo da cidade: ");
    scanf("%d", &codigo);
    printf("Digite o nome da cidade: ");
    scanf("%s", nome);
    printf("Digite a populacao da cidade: ");
    scanf("%d", &populacao);
    printf("Digite a area da cidade: ");
    scanf("%d", &area);
    printf("Digite o pib da cidade: ");
    scanf("%d", &pib);
    printf("Digite o numero de pontos turisticos da cidade: ");
    scanf("%d", &pontosTuristicos);

    printf("Cadastrando carta...\n ------------- \n");

    printf("Codigo: %d\n", codigo);
    printf("Nome: %s\n", nome);
    printf("Populacao: %d\n", populacao);
    printf("Area: %d\n", area);
    printf("Pib: %d\n", pib);
    printf("Pontos Turisticos: %d\n", pontosTuristicos);

    printf("Salvando carta...\n ------------- \n");

    ArrayJSON listaDeCartas = jsonFromFile("cartas.json");
    ObjectJSON cartaJsonObject = jsonCreateObject(
        6,
        "pib", 0, pib,
        "nome", 2, nome,
        "area", 0, area,
        "codigo", 0, codigo,
        "populacao", 0, populacao,
        "pontosTuristicos", 0, pontosTuristicos);

    jsonAddObject(listaDeCartas, cartaJsonObject);
    jsonSaveToFile(listaDeCartas, "cartas.json");
    jsonFree(listaDeCartas);

    return 0;
}
