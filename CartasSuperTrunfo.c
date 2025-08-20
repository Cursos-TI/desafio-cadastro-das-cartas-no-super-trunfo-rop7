#include <stdio.h>
#include <cjson/cJSON.h>
#include "jsonManage.h"
#include "Carta.h"

int main() {

    Carta carta;

    printf("Digite o codigo da cidade: ");
    scanf("%d", &carta.codigo);
    printf("Digite o nome da cidade: ");
    scanf("%99s", carta.nome);
    printf("Digite a populacao da cidade: ");
    scanf("%d", &carta.populacao);
    printf("Digite a area da cidade: ");
    scanf("%d", &carta.area);
    printf("Digite o pib da cidade: ");
    scanf("%d", &carta.pib);
    printf("Digite o numero de pontos turisticos da cidade: ");
    scanf("%d", &carta.pontosTuristicos);

    printf("Cadastrando carta...\n ------------- \n");

    printf("Codigo: %d\n", carta.codigo);
    printf("Nome: %s\n", carta.nome);
    printf("Populacao: %d\n", carta.populacao);
    printf("Area: %d\n", carta.area);
    printf("Pib: %d\n", carta.pib);
    printf("Pontos Turisticos: %d\n", carta.pontosTuristicos);

    printf("Salvando carta...\n ------------- \n");

    ArrayJSON listaDeCartas = jsonFromFile("cartas.json");
    ObjectJSON cartaJsonObject = jsonCreateObject(
        6,
        "pib", "int", carta.pib,
        "area", "int", carta.area,
        "nome", "string", carta.nome,
        "codigo", "int", carta.codigo,
        "populacao", "int", carta.populacao,
        "pontosTuristicos", "int", carta.pontosTuristicos);

    jsonAddObject(listaDeCartas, cartaJsonObject);
    jsonSaveToFile(listaDeCartas, "cartas.json");
    jsonFree(listaDeCartas);

    return 0;
}
