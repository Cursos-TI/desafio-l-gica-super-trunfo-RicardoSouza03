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

struct CartaCidade *buscarCidadePorCodigo(const char *codigo) {
    struct No *atual = listaDeNo;
    while (atual != NULL) {
        if (strcmp(atual->cidade.codigo, codigo) == 0) {
            return &(atual->cidade);
        }
        atual = atual->proximaCidade;
    }
    return NULL;
}

typedef enum {
    CAMPO_POPULACAO = 1,
    CAMPO_AREA = 2,
    CAMPO_PIB = 3,
    CAMPO_PONTOS_TURISTICOS = 4
} CampoComparacao;

struct CartaCidade *buscarECompararCidadePorCampo(struct CartaCidade *primeiraCidade, struct CartaCidade *segundaCidade, const CampoComparacao campoComparacao) {
    switch (campoComparacao) {
        case CAMPO_POPULACAO:
            if (primeiraCidade->populacao > segundaCidade->populacao) return primeiraCidade;
            if (primeiraCidade->populacao < segundaCidade->populacao) return segundaCidade;
            break;
        case CAMPO_AREA:
            if (primeiraCidade->area > segundaCidade->area) return primeiraCidade;
            if (primeiraCidade->area < segundaCidade->area) return segundaCidade;
            break;
        case CAMPO_PIB:
            if (primeiraCidade->PIB > segundaCidade->PIB) return primeiraCidade;
            if (primeiraCidade->PIB < segundaCidade->PIB) return segundaCidade;
            break;
        case CAMPO_PONTOS_TURISTICOS:
            if (primeiraCidade->quantidadePontosTuristicos > segundaCidade->quantidadePontosTuristicos) return primeiraCidade;
            if (primeiraCidade->quantidadePontosTuristicos < segundaCidade->quantidadePontosTuristicos) return segundaCidade;
            break;
        default:
            printf("Campo inválido!\n");
            return NULL;
    }
    return NULL;
}

void recebeInputCodigoCidadesECampoComparacaoUsuario() {
    struct CartaCidade *primeiraCidade = NULL;
    struct CartaCidade *segundaCidade = NULL;
    struct CartaCidade *cartaVencedora = NULL;
    int opcaoCampoComparacao;

    while (primeiraCidade == NULL) {
        char codigoCidade[10];
        lerValorChar("Digite o código da primeira cidade que deseja comparar: ", codigoCidade, 10);
        primeiraCidade = buscarCidadePorCodigo(codigoCidade);
        if (primeiraCidade == NULL) {
            printf("A cidade informada não existe. Tente novamente.\n");
        }
    }

    while (segundaCidade == NULL) {
        char codigoCidade[10];
        lerValorChar("Digite o código da segunda cidade que deseja comparar: ", codigoCidade, 10);
        segundaCidade = buscarCidadePorCodigo(codigoCidade);
        if (segundaCidade == NULL) {
            printf("A cidade informada não existe. Tente novamente.\n");
        }
    }

    do {
        printf("\nEscolha o campo de comparação:\n");
        printf("1. População\n");
        printf("2. Área\n");
        printf("3. PIB\n");
        printf("4. Quantidade de pontos turísticos\n");
        printf("5. Voltar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcaoCampoComparacao);
        while (getchar() != '\n');

        if (opcaoCampoComparacao >= CAMPO_POPULACAO && opcaoCampoComparacao <= CAMPO_PONTOS_TURISTICOS) {
            cartaVencedora = buscarECompararCidadePorCampo(primeiraCidade, segundaCidade, (CampoComparacao)opcaoCampoComparacao);
            if (cartaVencedora != NULL) {
                limparTerminal();
                printf("A cidade vencedora é \n");
                exibirDadosCidade(cartaVencedora);
                break;
            } else {
                printf("As cidades têm valores iguais no campo escolhido.\n");
            }
        } else if (opcaoCampoComparacao == 5) {
            limparTerminal();
            break;
        } else {
            printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcaoCampoComparacao != 5);
}

void geraMenuDeEscolha() {
    int opcaoMenu;
    struct CartaCidade novaCartaCidade;
    do {
        printf("\nMenu:\n");
        printf("1. Adicionar cidade\n");
        printf("2. Exibir cidades\n");
        printf("3. Comparar cidades\n");
        printf("4. Sair\n");
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
            limparTerminal();
            recebeInputCodigoCidadesECampoComparacaoUsuario();
            aguardarEnterParaVoltarAoMenu();
            break;
        case 4:
            printf("Encerrando... \n");
            break;
        default:
            printf("Opcao inválida!");
            break;
        }
    } while (opcaoMenu != 4);
    
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
