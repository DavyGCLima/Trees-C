#ifndef fila
#define fila
#include "lista.h"

typedef struct no{
    Cidade *conteudo;
    struct no *dir, *esq;
    int fator;
    int balanceamento;
}TNo;

typedef struct elo{
    TNo *no;
    int nivel;
    struct elo *prox;
}Elo;

typedef struct fila{
    Elo *primeiro;
    Elo *ultimo;
    int tamanho;
}Fila;

Fila *inicializaFila(Fila *f);
Elo *geraElo(TNo *no);
void insereFila(Fila *f, Elo *el);
int filaVazia(Fila *f);
Elo *removeFila(Fila *f);

#endif // fila
