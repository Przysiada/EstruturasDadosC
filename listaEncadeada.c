#include <stdio.h>
#include <stdlib.h>

typedef struct elemento
{
    int valor;
    struct elemento *proximo;
} No;

typedef struct{
    No *inicio;
    No *fim;
    int tamanho;
} Lista;

void inicializa (Lista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tamanho = 0;
}

int inserirInicio(Lista *lista, int valor)
{
    No *novo;
    char *aux;

    if ((novo = (No*) malloc(sizeof(No))) == NULL)
        return -1;
    
    novo->valor = valor;

    if(lista->inicio == NULL){
        novo->proximo = NULL;
        lista->inicio = novo;
        lista->fim = novo;
    }
    else{
        novo->proximo = lista->inicio;
        lista->inicio = novo;
    }
    lista->tamanho++;
    return 0;
}

int inserirFim(Lista *lista, int valor)
{
    No *novo;

    if ((novo = (No*) malloc(sizeof(No))) == NULL)
        return -1;
    
    novo->valor = valor;
    novo->proximo = NULL;

    if(lista->inicio == NULL){
        lista->inicio = novo;
        lista->fim = novo;
    }
    else{
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    lista->tamanho++;
    return 0;
}

void removeInicio(Lista *lista)
{
    if(lista->inicio != NULL){
        No *no = lista->inicio;
        lista->inicio = no->proximo;
        lista->tamanho--;
        if (lista->inicio == NULL)
            lista->fim = NULL;
        free(no);
    }
}

void removeQualquer(Lista *lista, int valor)
{
    No *inicio = lista->inicio;
    No *aRemover = NULL;

    if(inicio != NULL && lista->inicio->valor == valor){
        aRemover = lista->inicio;
        lista->inicio = aRemover->proximo;
        if(lista->inicio == NULL)
            lista->fim = NULL;
    }
    else{
        while (inicio != NULL && inicio->proximo != NULL && inicio->proximo->valor != valor)
            inicio = inicio->proximo;
        if(inicio != NULL && inicio->proximo != NULL){
            aRemover = inicio->proximo;
            inicio->proximo = aRemover->proximo;
            if(inicio->proximo == NULL)
                lista->fim = NULL;
        } 
    }
    if(aRemover)
    {
        free(aRemover);
        lista->tamanho--; 
    }
}

void imprime(Lista *lista)
{
    No *atual = lista->inicio;
    printf("Tamanho atual da lista = %d\n", lista->tamanho);
    while (atual != NULL){
        printf("%d\n", atual->valor);
        atual = atual->proximo;
    }
}

void main()
{
    Lista *lista;
    int valor;
    char op;

    if((lista = (Lista*)malloc(sizeof(Lista))) == NULL)
        return -1;

    inicializa(lista);

    while (op != 'X')
    {
        printf("Digite a letra da funcao desejada\n");
        printf("A - Adicionar elemento no inicio da lista\n");
        printf("B - Adicionar elemento no fim da lista\n");
        printf("R - Remover elemento do inicio da lista\n");
        printf("V - Remover um elemento lista\n");
        printf("L - Imprimir os elementos da lista\n");
        printf("X - Sair do programa\n");
        fflush(stdin);
        scanf("%c", &op);
        if(op == 'A')
        {
            printf("Digite o valor a ser inserido\n");
            scanf("%d", &valor);
            if(inserirInicio(lista, valor) == 0)
                printf("Elemento inserido com sucesso\n");
            else
                printf("Elemento não removido com sucesso\n");
        }
        else if(op == 'B')
        {
            printf("Digite o valor a ser inserido\n");
            scanf("%d", &valor);
            if(inserirFim(lista, valor) == 0)
                printf("Elemento inserido com sucesso\n");
            else
                printf("Elemento não removido com sucesso\n");
        }
        else if (op == 'R')
        {
            removeInicio(lista);
        }
        else if(op == 'V')
        {
            printf("Digite o valor a ser removido\n");
            scanf("%d", &valor);
            removeQualquer(lista,valor);
        }
        else if (op == 'L')
        {
            printf("\nValor dentro da lista:\n\n");
            imprime(lista);
        }
        else if (op == 'X')
            printf("Tchau\n");
        else
            printf("Funcao invalida\n");
    }
}
