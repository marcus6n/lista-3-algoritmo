#include <stdio.h>
#include <string.h>

#define MAX_FABRICANTES 5
#define MAX_PRODUTOS 50

// Structs

typedef struct
{
    char marca[50];
    char site[50];
    char telefone[20];
    char uf[3];
} Fabricante;

typedef struct
{
    char descricao[50];
    float peso;
    float valorCompra;
    float valorVenda;
    float valorLucro;
    float percentualLucro;
    Fabricante fabricante;
} Produto;

// Funções auxiliares

void leValidaString(char *str, int maxLen)
{
    fgets(str, maxLen, stdin);
    str[strcspn(str, "\n")] = '\0'; // remove o caractere de nova linha
}

float leValidaFloat()
{
    float num;
    scanf("%f", &num);
    getchar(); // remove o caractere de nova linha deixado pelo scanf
    return num;
}

void cadastrarFabricante(Fabricante *fabricante)
{
    printf("\n--- Cadastro de Fabricante ---\n");

    printf("Marca: ");
    leValidaString(fabricante->marca, sizeof(fabricante->marca));

    printf("Site: ");
    leValidaString(fabricante->site, sizeof(fabricante->site));

    printf("Telefone: ");
    leValidaString(fabricante->telefone, sizeof(fabricante->telefone));

    printf("UF: ");
    leValidaString(fabricante->uf, sizeof(fabricante->uf));
}

void cadastrarProduto(Produto *produto, Fabricante *fabricantes, int numFabricantes)
{
    printf("\n--- Cadastro de Produto ---\n");

    printf("Descrição: ");
    leValidaString(produto->descricao, sizeof(produto->descricao));

    printf("Peso: ");
    produto->peso = leValidaFloat();

    printf("Valor de Compra: ");
    produto->valorCompra = leValidaFloat();

    printf("Valor de Venda: ");
    produto->valorVenda = leValidaFloat();

    printf("Fabricante: ");
    int opcao;
    for (int i = 0; i < numFabricantes; i++)
    {
        printf("\n%d. %s", i + 1, fabricantes[i].marca);
    }
    printf("\nDigite o número correspondente ao fabricante: ");
    opcao = leValidaFloat();

    if (opcao >= 1 && opcao <= numFabricantes)
    {
        produto->fabricante = fabricantes[opcao - 1];
        produto->valorLucro = produto->valorVenda - produto->valorCompra;
        produto->percentualLucro = (produto->valorLucro / produto->valorCompra) * 100.0;

        printf("Produto cadastrado com sucesso!\n");
    }
    else
    {
        printf("Opção inválida!\n");
    }
}

void emitirRelatorioFabricantes(Fabricante *fabricantes, int numFabricantes)
{
    printf("\n--- Relatório de Fabricantes ---\n");
    printf("|   Marca   |   Site   |   Telefone   |   UF   |\n");

    for (int i = 0; i < numFabricantes; i++)
    {
        printf("| %-9s | %-7s | %-11s | %-3s |\n",
               fabricantes[i].marca, fabricantes[i].site, fabricantes[i].telefone, fabricantes[i].uf);
    }
}

void emitirRelatorioProdutos(Produto *produtos, int numProdutos)
{
    printf("\n--- Relatório de Produtos ---\n");
    printf("|   Descrição   |   Peso   |   Valor de Compra   |   Valor de Venda   |   Valor do Lucro   |   Percentual do Lucro   |   Fabricante   |\n");

    for (int i = 0; i < numProdutos; i++)
    {
        printf("| %-13s | %-7.2f | %-19.2f | %-18.2f | %-18.2f | %-23.2f | %-14s |\n",
               produtos[i].descricao, produtos[i].peso, produtos[i].valorCompra,
               produtos[i].valorVenda, produtos[i].valorLucro, produtos[i].percentualLucro,
               produtos[i].fabricante.marca);
    }
}

// Função principal

int main()
{
    Fabricante fabricantes[MAX_FABRICANTES];
    Produto produtos[MAX_PRODUTOS];
    int numFabricantes = 0;
    int numProdutos = 0;
    int opcao;

    do
    {
        printf("\n--- Menu ---\n");
        printf("1. Cadastrar Fabricante\n");
        printf("2. Cadastrar Produto\n");
        printf("3. Emitir Relatório de Fabricantes\n");
        printf("4. Emitir Relatório de Produtos\n");
        printf("0. Sair\n");
        printf("Digite a opção desejada: ");
        opcao = leValidaFloat();

        switch (opcao)
        {
        case 1:
            if (numFabricantes >= MAX_FABRICANTES)
            {
                printf("Número máximo de fabricantes atingido!\n");
            }
            else
            {
                cadastrarFabricante(&fabricantes[numFabricantes]);
                numFabricantes++;
            }
            break;
        case 2:
            if (numProdutos >= MAX_PRODUTOS)
            {
                printf("Número máximo de produtos atingido!\n");
            }
            else if (numFabricantes < 2)
            {
                printf("É necessário cadastrar pelo menos 2 fabricantes primeiro!\n");
            }
            else
            {
                cadastrarProduto(&produtos[numProdutos], fabricantes, numFabricantes);
                numProdutos++;
            }
            break;
        case 3:
            emitirRelatorioFabricantes(fabricantes, numFabricantes);
            break;
        case 4:
            emitirRelatorioProdutos(produtos, numProdutos);
            break;
        case 0:
            printf("Programa encerrado.\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}