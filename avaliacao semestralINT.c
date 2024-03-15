#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Ingresso
{
    int cpf;
    char nome[50];
    int data;
    struct Ingresso *prox;
} Ingresso;

void inserirIngresso(Ingresso **lista, int cpf, char nome[], int data)
{
    Ingresso *aux = *lista;
    while (aux != NULL)
    {
        if (aux->cpf == cpf && aux->data == data)
        {
            printf("\nExiste um ingresso cadastrado para este CPF nesta data.\n");
            return;
        }
        aux = aux->prox;
    }

    Ingresso *novo = (Ingresso *)malloc(sizeof(Ingresso));
    novo->cpf = cpf;
    strcpy(novo->nome, nome);
    novo->data = data;
    novo->prox = *lista;

    Ingresso *atual = novo;
    Ingresso *ordenado = NULL;

    while (atual != NULL)
    {
        Ingresso *prox = atual->prox;
        if (ordenado == NULL || atual->cpf < ordenado->cpf)
        {
            atual->prox = ordenado;
            ordenado = atual;
        }
        else
        {
            Ingresso *aux = ordenado;
            while (aux->prox != NULL && atual->cpf > aux->prox->cpf)
            {
                aux = aux->prox;
            }
            atual->prox = aux->prox;
            aux->prox = atual;
        }
        atual = prox;
    }

    *lista = ordenado;
}

void buscarPorCPF(Ingresso *lista, int cpf)
{
    Ingresso *aux = lista;
    int encontrado = 0;
    while (aux != NULL)
    {
        if (aux->cpf == cpf)
        {
            printf("--------------------\n");
            printf("Nome: %s | Data: %d\n", aux->nome, aux->data);
            encontrado = 1;
        }
        aux = aux->prox;
    }
    if (!encontrado)
    {
        printf("\nNenhum ingresso encontrado para o CPF fornecido.\n");
    }
}


void quickSort(Ingresso **lista)
{
    if (*lista == NULL || (*lista)->prox == NULL)
    {
        return;
    }

    int pivo = (*lista)->data;
    Ingresso *menor = NULL;
    Ingresso *igual = NULL;
    Ingresso *maior = NULL;
    Ingresso *aux = *lista;

    while (aux != NULL)
    {
        Ingresso *prox = aux->prox;
        if (aux->data < pivo)
        {
            aux->prox = menor;
            menor = aux;
        }
        else if (aux->data == pivo)
        {
            aux->prox = igual;
            igual = aux;
        }
        else
        {
            aux->prox = maior;
            maior = aux;
        }
        aux = prox;
    }

    quickSort(&menor);
    quickSort(&maior);

    *lista = menor;
    while (menor != NULL && menor->prox != NULL)
    {
        menor = menor->prox;
    }
    if (menor != NULL)
    {
        menor->prox = igual;
    }
    else
    {
        *lista = igual;
    }
    while (igual != NULL && igual->prox != NULL)
    {
        igual = igual->prox;
    }
    if (igual != NULL)
    {
        igual->prox = maior;
    }
}

void imprimirLista(Ingresso *lista)
{
    printf("Lista de ingressos:\n");
    while (lista != NULL)
    {
        printf("--------------------\n");
        printf("Nome: %s | CPF: %d | Data: %d\n", lista->nome, lista->cpf, lista->data);
        lista = lista->prox;
    }
}

int main()
{
    Ingresso *lista = NULL;

    int opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1. Inserir novo ingresso (Insertion Sort)\n");
        printf("2. Buscar ingressos por CPF\n");
        printf("3. Ordenar ingressos pela data do evento (Quick Sort)\n");
        printf("4. Imprimir lista de ingressos\n");
        printf("5. Sair\n");
        printf("--------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
        {
            int cpf;
            char nome[50];
            int data;
            printf("--------------------\n");
            printf("Digite o CPF do comprador: ");
            scanf("%d", &cpf);
            printf("Digite o nome do comprador: ");
            scanf("%s", nome);
            printf("Digite a data do evento: ");
            scanf("%d", &data);
            printf("--------------------\n");
            inserirIngresso(&lista, cpf, nome, data);
            break;
        }
        case 2:
        {
            int cpf;
            printf("--------------------\n");
            printf("Digite o CPF para buscar os ingressos: ");
            scanf("%d", &cpf);
            buscarPorCPF(lista, cpf);
            break;
        }
        case 3:
        {
            quickSort(&lista);
            printf("Ingressos ordenados pela data do evento (Quick Sort):\n");
            printf("\n");
            imprimirLista(lista);
            break;
        }
        case 4:
        {
            imprimirLista(lista);
            break;
        }
        case 5:
        {
            printf("Saindo...\n");
            break;
        }
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    while (lista != NULL)
    {
        Ingresso *aux = lista;
        lista = lista->prox;
        free(aux);
    }

    return 0;
}