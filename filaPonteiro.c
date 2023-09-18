#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elementoLista {
    char *dado;
    struct elementoLista *seguinte;
} elemento;

typedef struct filaponteiro {
    elemento *primeiro;
    elemento *ultimo;
    int tamanho;
} Fila;

void inicializacao(Fila *sequencia)
{
    sequencia->primeiro = NULL;
    sequencia->ultimo = NULL;
    sequencia->tamanho = 0;
}

int enqueue (Fila *sequencia, elemento *atual, char *info)
{
    elemento *novo_elemento;
    if((novo_elemento = (elemento*)malloc(sizeof(elemento))) == NULL)
        return -1;
    if((novo_elemento->dado = (char *) malloc(50 * sizeof(char))) == NULL)
        return -1;
    strcpy(novo_elemento->dado, info);

    if(atual == NULL){
        if(sequencia->tamanho == 0)
            sequencia->ultimo = novo_elemento;
        novo_elemento->seguinte = sequencia->primeiro;
        sequencia->primeiro = novo_elemento;
    }
    else {
        if(atual->seguinte == NULL)
            sequencia->ultimo = novo_elemento;
        novo_elemento->seguinte = atual->seguinte;
        atual->seguinte = novo_elemento;
    }
    sequencia->tamanho++;
    return 0;
}

int dequeue (Fila *sequencia)
{
    elemento *antigo_elemento;
    if(sequencia->tamanho == 0)
        return -1;
    antigo_elemento = sequencia->primeiro;
    sequencia->primeiro = sequencia->primeiro->seguinte;
    free(antigo_elemento->dado);
    free(antigo_elemento);
    sequencia->tamanho--;
    return 0;
}

void list(Fila *sequencia)
{
    elemento *atual;
    int i;
    atual = sequencia->primeiro;

    for(i = 0; i < sequencia->tamanho; i++){
        printf("Valor = %s\n", atual->dado);
        atual = atual->seguinte;
    }
}

void main()
{
    char op;
    Fila *sequencia;
    char *aux;

    if ((sequencia = (Fila*) malloc(sizeof(Fila))) == NULL)
        return -1;
    if((aux = (char*) malloc(50*sizeof(char))) == NULL)
        return -1;

    inicializacao(sequencia);

    while (op != 'X')
    {
        printf("Digite a letra da funcao desejada\n");
        printf("A - Adicionar elementos na fila\n");
        printf("R - Remover elementos da fila\n");
        printf("L - Listar os elementos da fila\n");
        //printf("E - Examinar o elemento da cabeca\n");
        //printf("C - Limpar a fila\n");
        printf("T - Tamanho da fila\n");
        printf("X - Sair do programa\n");
        fflush(stdin);
        scanf("%c", &op);
        if(op == 'A')
        {
            printf("Digite o string a ser inserido\n");
            scanf("%s", aux);
            if(enqueue(sequencia, sequencia->ultimo, aux) == 0)
                printf("Elemento inserido com sucesso\n");
            else
                printf("Elemento não removido com sucesso\n");
        }
        else if (op == 'R')
        {
            if(dequeue(sequencia) == 0)
                printf("Elemento removido com sucesso\n");
            else
                printf("Elemento não removido com sucesso\n");
        }
        else if (op == 'L')
        {
            printf("\nValor dentro da lista:\n\n");
            list(sequencia);
        }
        /*else if (op == 'E')
            printf("O valor examinado = %d\n", peek());
        else if (op == 'C')
        {
            clear();
            printf("Limpeza executada\n");
        }*/
        else if (op == 'T')
            printf("O tamanho da fila = %d\n", sequencia->tamanho);
        else if (op == 'X')
            printf("Tchau\n");
        else
            printf("Funcao invalida\n");
    }  
}
