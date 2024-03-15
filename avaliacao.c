#include <stdio.h>
#include <stdlib.h>

typedef struct data{
    int dia;
    int mes;
    int ano;
} Date;

typedef struct ingresso{
   char cpf[11];
   char comprador[50];
   Date date;
   struct Ingresso *prox;
} Ingresso;

typedef struct QueueController{
    Ingresso *inicio;
    Ingresso *fim;
    int count;
} QueueController;




int main()
{
    printf("Oiii");
    return 0;
}