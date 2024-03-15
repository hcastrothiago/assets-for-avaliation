#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de nó da lista encadeada
struct Node {
    int data;
    struct Node* next;
};

// Função para criar um novo nó
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Função para imprimir a lista encadeada
void printList(struct Node *node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

// Bubble Sort para lista encadeada
void bubbleSort(struct Node *start) {
    int swapped;
    struct Node *ptr1;
    struct Node *lptr = NULL;

    if (start == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = start;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Selection Sort para lista encadeada
void selectionSort(struct Node *start) {
    struct Node *ptr1, *ptr2;
    int temp;

    ptr1 = start;

    while (ptr1 != NULL) {
        ptr2 = ptr1->next;

        while (ptr2 != NULL) {
            if (ptr1->data > ptr2->data) {
                temp = ptr1->data;
                ptr1->data = ptr2->data;
                ptr2->data = temp;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

// Insertion Sort para lista encadeada
void insertionSort(struct Node *start) {
    struct Node *sorted = NULL;
    struct Node *current = start;

    while (current != NULL) {
        struct Node *next = current->next;
        struct Node *prev = NULL;

        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            prev = sorted;
            while (prev->next != NULL && prev->next->data < current->data) {
                prev = prev->next;
            }
            current->next = prev->next;
            prev->next = current;
        }

        current = next;
    }

    start = sorted;
}

// Função de partição para Quick Sort
struct Node* partition(struct Node *start, struct Node *end, struct Node **newStart, struct Node **newEnd) {
    struct Node *pivot = end;
    struct Node *prev = NULL, *cur = start, *tail = pivot;

    while (cur != pivot) {
        if (cur->data < pivot->data) {
            if ((*newStart) == NULL)
                (*newStart) = cur;
            prev = cur;
            cur = cur->next;
        } else {
            if (prev)
                prev->next = cur->next;
            struct Node *temp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if ((*newStart) == NULL)
        (*newStart) = pivot;

    (*newEnd) = tail;

    return pivot;
}

// Função principal de Quick Sort para lista encadeada
struct Node* quickSortRecur(struct Node *start, struct Node *end) {
    if (!start || start == end)
        return start;

    struct Node *newStart = NULL, *newEnd = NULL;
    struct Node *pivot = partition(start, end, &newStart, &newEnd);

    if (newStart != pivot) {
        struct Node *temp = newStart;
        while (temp->next != pivot)
            temp = temp->next;
        temp->next = NULL;

        newStart = quickSortRecur(newStart, temp);

        temp = getTail(newStart);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newStart;
}

// Função de utilidade para Quick Sort
void quickSort(struct Node **headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

// Função de mesclagem para Merge Sort
struct Node* merge(struct Node *first, struct Node *second) {
    if (!first)
        return second;
    if (!second)
        return first;

    if (first->data < second->data) {
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}

// Função principal de Merge Sort para lista encadeada
struct Node* mergeSort(struct Node *head) {
    if (!head || !head->next)
        return head;

    struct Node *slow = head, *fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    struct Node *second = slow->next;
    slow->next = NULL;

    return merge(mergeSort(head), mergeSort(second));
}

// Shell Sort para lista encadeada
void shellSort(struct Node *start) {
    int n = 0;
    struct Node *temp = start;
    while (temp != NULL) {
        n++;
        temp = temp->next;
    }

    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int tempData;
            struct Node *ptr1 = start;
            for (int j = 0; j < i; j++) {
                ptr1 = ptr1->next;
            }
            tempData = ptr1->data;

            struct Node *ptr2 = start;
            for (int j = 0; j < i - gap; j++) {
                ptr2 = ptr2->next;
            }
            ptr1->data = ptr2->data;

            ptr2 = start;
            for (int j = 0; j < i - gap; j++) {
                ptr2 = ptr2->next;
            }
            ptr2->data = tempData;
        }
    }
}

// Função para adicionar um nó no final da lista encadeada
void append(struct Node** headRef, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *headRef;
    newNode->data = data;
    newNode->next = NULL;
    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

// Função para liberar a memória alocada para a lista encadeada
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Node* head = NULL;

    // Adicionando elementos à lista encadeada
    append(&head, 64);
    append(&head, 34);
    append(&head, 25);
    append(&head, 12);
    append(&head, 22);
    append(&head, 11);
    append(&head, 90);

    printf("Lista original:\n");
    printList(head);

    // Ordenando a lista encadeada usando diferentes métodos de ordenação
    bubbleSort(head);
    // selectionSort(head);
    // insertionSort(head);
    // quickSort(&head);
    // head = mergeSort(head);
    // shellSort(head);

    printf("\nLista ordenada:\n");
    printList(head);

    // Liberando a memória alocada para a lista encadeada
    freeList(head);

    return 0;
}
