#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// estrutura tempo
typedef struct time
{
    int hour;
    int minute;
    int second;
} Time;

// estrutura gerenciador de tarefas
typedef struct node
{
    char taskName[30];
    int amountTask;
    Time startTime;
    struct node *next;
} TaskManagement;

// estrutura fila - controlador
typedef struct queue
{
    TaskManagement *start;
    TaskManagement *end;
    int count;
} Queue;

// Inicia as filas, evitando uso de ponteiro para ponteiro
void initQueue(Queue *queue)
{
    queue->start = NULL;
    queue->end = NULL;
    queue->count = 0;
}

// Contador de atividades a executar
int tasksInQueue = 0;

void insertTaskInQueue(Queue *fila)
{
    // Aloca um novo gerenciador de tarefas
    TaskManagement *novo = (TaskManagement *)malloc(sizeof(TaskManagement));

    // sessão de prompts
    printf("\tDigite o nome da tarefa a ser executada: ");
    scanf(" %[^\n]", novo->taskName);
    printf("\tDigite a quantidade de tarefas: ");
    scanf("%d", &novo->amountTask);
    printf("\tDigite a hora de inicio da tarefa no formato hh mm ss com espacos: ");
    scanf("%d%d%d", &novo->startTime.hour, &novo->startTime.minute, &novo->startTime.second);

    // verifica se a lista foi alocada corretamente
    if (novo)
    {
        novo->next = NULL;
        // Verifica se a fila está vazia
        if (fila->start == NULL)
        {
            novo->next = fila->start;
            fila->start = novo;
            fila->end = novo;
        }
        else
        {
            fila->end->next = novo;
            fila->end = novo;
        }
        fila->count++;
    }
    else
    {
        printf("Erro ao alocar memoria\n");
    }
}

void executar(Queue *fila)
{
    TaskManagement *aux = fila->start;

    if (aux == NULL)
    {
        printf("\tFila vazia\n");
        return;
    }
    else
    {
        if (aux->amountTask > 0)
        {
            printf("\tExecutando uma atividade da tarefa %s\n", aux->taskName);
            aux->amountTask--;

            if (aux->amountTask > 0)
            {
                printf("\tRestam %d atividades na tarefa %s.\n", aux->amountTask, aux->taskName);
            }
            else
            {
                printf("\tTarefa %s concluida!\n", aux->taskName);
                fila->start = aux->next;
                free(aux);
                fila->count--;
            }
        }
        else
        {
            printf("\tA tarefa %s ja foi concluida!\n", aux->taskName);
            fila->start = aux->next;
            free(aux);
            fila->count--;
        }
    }
}

void calcular_atividades(Queue *fila)
{
    TaskManagement *atual = fila->start;

    printf("\tAtividades em andamento\n");

    while (atual != NULL)
    {
        printf("\tExistem %d atividades na tarefa %s a serem executadas\n",
               atual->amountTask, atual->taskName);
        atual = atual->next;
    }

    printf("\tTotal de tarefas em andamento: %d\n", fila->count);
}

void tasks_before_time(Queue *fila)
{
    Time search;
    TaskManagement *list = fila->start;

    printf("\tDigite o horario desejado: ");
    scanf("%d%d%d", &search.hour, &search.minute, &search.second);

    // TESTS CASES
    /** Hora é menor e Hora é igual */
    int hourIsSmaller = list->startTime.hour < search.hour,
        hourIsEqual = list->startTime.hour == search.hour;
    /** Minuto é menor e Minuto é igual */
    int minuteIsSmaller = list->startTime.minute < search.minute,
        minuteIsEqual = list->startTime.minute == search.minute;
    /** Segundo é menor*/
    int secondIsSmaller = list->startTime.second < search.second;

    while (list != NULL)
    {
        if (hourIsSmaller)
        {
            tasksInQueue += list->amountTask;
        }
        else if (hourIsEqual && minuteIsSmaller)
        {
            tasksInQueue += list->amountTask;
        }
        else if (hourIsEqual && minuteIsEqual && secondIsSmaller)
        {
            tasksInQueue += list->amountTask;
        }
        list = list->next;
    }

    printf("\tAinda existem %d tarefas a serem executadas", tasksInQueue);
}

void menu()
{
    printf("\n");
    printf("1 - Adicionar tarefa\n");
    printf("2 - Executar Gerenciador de Tarefas\n");
    printf("3 - Calcular atividades\n");
    printf("4 - Pesquisar atividades criandas antes do horario\n");
    printf("5 - Sair\n");
    printf("Digite a opcao desejada: ");
}
int main()
{
    TaskManagement fila;
    initQueue(&fila);
    int option;

    do
    {
        menu();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            insertTaskInQueue(&fila);
            break;
        case 2:
            executar(&fila);
            break;
        case 3:
            calcular_atividades(&fila);
            break;
        case 4:
            tasks_before_time(&fila);
            break;

        default:
            if (option != 5)
            {
                printf("Opcao invalida!\n");
            }

            break;
        }
    } while (option != 5);

    return 0;
}