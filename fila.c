#include "fila.h"

//cria uma estrutura inicial para armazenar uma fila
Fila *inicializaFila(Fila *f){
    f = (Fila*)malloc(sizeof(Fila));
    f->primeiro = NULL;
    f->ultimo = NULL;
    f->tamanho = 0;
    return f;
}

//gera uma estrutura a partir de um nó de arvore, para ser utilizado
Elo *geraElo(TNo *no){
    Elo *elo = (Elo*)malloc(sizeof(Elo));
    elo->no = no;
    elo->prox = NULL;
    elo->nivel = 0;
    return elo;
}

//insere na fila, sempre ao final
void insereFila(Fila *f, Elo *el){
    if(filaVazia(f) == 1){
        f->ultimo = el;
        f->primeiro = el;
    }else{
       Elo *temp = f->ultimo;
       temp->prox = el;
       f->ultimo = el;
    }
    f->tamanho++;
}

//verirfica se a fila não possui elementos
int filaVazia(Fila *f){
    if(f->primeiro == NULL && f->ultimo == NULL)
        return 1;
    else
        return 0;
}

//remove da fila, sempre o primeiro elemento
Elo *removeFila(Fila *f){
    if(filaVazia(f) != 1){
        Elo *retorno = f->primeiro;
        if(f->primeiro == f->ultimo){
            f->primeiro = NULL;
            f->ultimo = NULL;
        }else
            f->primeiro = retorno->prox;
        retorno->prox = NULL;
        f->tamanho--;
        return retorno;
    }
    return NULL;
}


