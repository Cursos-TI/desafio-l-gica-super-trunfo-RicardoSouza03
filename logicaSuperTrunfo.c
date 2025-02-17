#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Desafio Super Trunfo - Países
// Tema 2 - Comparação das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de comparação de cartas de cidades. 
// Siga os comentários para implementar cada parte do desafio.
struct CartaCidade {
    char estado[10];
    char codigo[10];
    char nome[100];
    int populacao;
    float area;
    float PIB;
    int quantidadePontosTuristicos;
};

struct No {
    struct CartaCidade cidade;
    struct No *proximaCidade;
};

struct No *listaDeNo = NULL;

void adicionarCidadeALista(const struct CartaCidade cidade) {
    struct No *novoNo = (struct No *)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    novoNo->cidade = cidade;
    novoNo->proximaCidade = NULL;

    if (listaDeNo == NULL) {
        listaDeNo = novoNo;
    } else {
        struct No *atual = listaDeNo;
        while (atual->proximaCidade != NULL) {
            atual = atual->proximaCidade;
        }
        atual->proximaCidade = novoNo;
    }

    printf("Cidade adicionada com sucesso!\n");
}

void limparTerminal() {
    #ifdef _WIN32
        system("cls"); // Para Windows
    #else
        system("clear"); // Para Linux/Mac
    #endif
}

void exibirDadosCidade(const struct CartaCidade *cartaCidade) {
    printf("===============================================\n");
    printf("Codigo: %s\n", cartaCidade->codigo);
    printf("Nome: %s\n", cartaCidade->nome);
    printf("População: %d\n", cartaCidade->populacao);
    printf("Area: %.2f\n", cartaCidade->area);
    printf("PIB: %.2f\n", cartaCidade->PIB);
    printf("Quantidade de pontos turisticos: %d\n", cartaCidade->quantidadePontosTuristicos);
    printf("================================================\n");
}

int lerValorInteiro(const char *mensagemInstrucao) {
    int valorInteiro;
    printf("%s", mensagemInstrucao);
    while (scanf("%d", &valorInteiro) != 1) {
        printf("Entrada inválida. Digite um número inteiro: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return valorInteiro;
}

float lerValorFloat(const char *mensagemInstrucao) {
    float valorFloat;
    printf("%s", mensagemInstrucao);
    while (scanf("%f", &valorFloat) != 1) {
        printf("Entrada inválida. Digite um número real: ");
        while (getchar() != '\n');
    }
    while (getchar() != '\n');
    return valorFloat;
}

void lerValorChar(const char *mensagem, char *valor, int tamanho) {
    printf("%s", mensagem);
    fgets(valor, tamanho, stdin);
    valor[strcspn(valor, "\n")] = 0;
}

void exibirListaCidades() {
    if (listaDeNo == NULL) {
        printf("Nenhuma cidade foi cadastrada.");
        return;
    }

    struct No *atual = listaDeNo;
    while (atual != NULL) {
        exibirDadosCidade(&atual->cidade);
        atual = atual->proximaCidade;
    }
}

void liberarEspacoEmMemoriaDaListaDeNo() {
    struct No *atual = listaDeNo;
    while (atual != NULL) {
        struct No *proximo = atual->proximaCidade;
        free(atual); 
        atual = proximo;
    }
    listaDeNo = NULL;
}


struct CartaCidade adicionarNovaCidade() {
    struct CartaCidade novaCartaCidade;

    lerValorChar("Digite o estado da cidade: \n", novaCartaCidade.estado, 10);
    lerValorChar("Digite o codigo da cidade: \n", novaCartaCidade.codigo, 10);
    lerValorChar("Digite o nome da cidade: \n", novaCartaCidade.nome, 100);
    novaCartaCidade.area = lerValorFloat("Digite a area da cidade: \n");
    novaCartaCidade.populacao = lerValorInteiro("Digite a populacao da cidade: \n");
    novaCartaCidade.PIB = lerValorFloat("Digite o PIB da cidade: \n");
    novaCartaCidade.quantidadePontosTuristicos = lerValorInteiro("Digite a quantidade de pontos turisticos da cidade: \n");
    
    return novaCartaCidade;
}

void aguardarEnterParaVoltarAoMenu() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n');
    limparTerminal();
}

void geraMenuDeEscolha() {
    int opcaoMenu;
    struct CartaCidade novaCartaCidade;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar cidade\n");
        printf("2. Exibir cidades\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoMenu);
        while (getchar() != '\n');

        switch (opcaoMenu) {
        case 1:
            limparTerminal();
            novaCartaCidade = adicionarNovaCidade();
            adicionarCidadeALista(novaCartaCidade);
            limparTerminal();
            exibirDadosCidade(&novaCartaCidade);
            aguardarEnterParaVoltarAoMenu();
            break;
        case 2:
            limparTerminal();
            exibirListaCidades();
            aguardarEnterParaVoltarAoMenu();
            break;
        case 3:
            printf("Encerrando... \n");
            break;
        default:
            printf("Opcao inválida!");
            break;
        }
    } while (opcaoMenu != 3);
    
    liberarEspacoEmMemoriaDaListaDeNo();
}

int main() {
    geraMenuDeEscolha();
    return 0;
}

// Definição das variáveis para armazenar as propriedades das cidades
// Você pode utilizar o código do primeiro desafio


// Cadastro das Cartas:
// Implemente a lógica para solicitar ao usuário que insira os dados das cidades
// utilizando a função scanf para capturar as entradas.
// utilize o código do primeiro desafio

// Exemplo:
// printf("Digite o código da cidade: ");
// scanf("%s", codigo);
// 
// (Repita para cada propriedade)

// Comparação de Cartas:
// Desenvolva a lógica de comparação entre duas cartas.
// Utilize estruturas de decisão como if, if-else para comparar atributos como população, área, PIB, etc.

// Exemplo:
// if (populacaoA > populacaoB) {
//     printf("Cidade 1 tem maior população.\n");
// } else {
//     printf("Cidade 2 tem maior população.\n");
// }

// Exibição dos Resultados:
// Após realizar as comparações, exiba os resultados para o usuário.
// Certifique-se de que o sistema mostre claramente qual carta venceu e com base em qual atributo.

// Exemplo:
// printf("A cidade vencedora é: %s\n", cidadeVencedora);
