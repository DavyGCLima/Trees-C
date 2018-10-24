#include "lista.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

//inicia a estrutura de lista
void inicializaLista(Lista *L){
    L->primeiro = NULL;
    L->ultimo = NULL;
    L->total = 0;
}

//insere em uma lista, ao final, dada uma estrutra de cidade não nula
void inserir(Lista *L, Cidade *cid){

    Elemento *no = (Elemento*)malloc(sizeof(Elemento));
    no->conteudo = cid;
    no->ant = NULL;
    no->prox = NULL;
    if(L->primeiro == NULL){
        L->primeiro = no;
        L->ultimo = no;

    }else{
        L->ultimo->prox = no;
        no->ant = L->ultimo;
        L->ultimo = no;
    }
     L->total++;
}

//realiza uma busca na lista, dado um nome
Cidade* buscarPorNome(Lista *L, char* nome){
   Elemento *cursor = buscarElementoPorNome(L, nome);
   if(cursor != NULL)
        return cursor->conteudo;
    else
        return NULL;
}

//realiza uma busca na lista dado um codigo de cidade
Cidade* buscarPorCodigo(Lista *L, int cod){
    Elemento *cursor = buscarElementoPorCodigo(L, cod);
    if(cursor != NULL)
        return cursor->conteudo;
    else
        return NULL;
}

//retorna o ponteiro do elemento contendo a primeira estrutura correspondente ao nome encontrada
Elemento* buscarElementoPorNome(Lista *L, char* nome){
    Elemento *cursor = L->primeiro;
    int cont = 0;
    if(L->primeiro == NULL)
        printf("\n\n\t Lista vazia ======");
    while((cursor != NULL) && (strcmp(cursor->conteudo->nome, nome) != 0)){
        cont++;
        if(cursor->prox == NULL){
            cursor = NULL;
            return NULL;
        }
        else{
            cursor = cursor->prox;
        }
    }
    return cursor;
}

//retorna o ponteiro para o elemento contendo a cidade para o primeiro elemento encotrado
Elemento* buscarElementoPorCodigo(Lista *L, int cod){
      Elemento *cursor = L->primeiro;
    int cont = 0;
    if(L->primeiro == NULL)
        printf("\n\n\t Lista vazia ======");
    while(cursor != NULL && cursor->conteudo->numero != cod){
        cont++;
        if(cursor->prox == NULL){
            cursor = NULL;
            return NULL;
        }
        else{
            cursor = cursor->prox;
        }
    }
    return cursor;
}

//apenas exibe as informações de uma estura de cidade
void exibirNomeDesordenado(Cidade *cid){
    printf("\n\t Cidade: %s", cid->nome);
    printf("\n\t Numero: %d", cid->numero);
    printf("\n\t Populacao: %d", cid->populacao);
    printf("\n");
}

//gera o arquivo de saida de lista
void gerarListasOrdenadas(Lista *L, Lista *LOrdCod, Lista *LOrdNom){
    printf("\n\t Preparando listas");

    clock_t inic1 = clock();
    gerarListaOrdCod(L, LOrdCod);
    clock_t fim1 = clock();

    double res1 = (double)(fim1 - inic1)/CLOCKS_PER_SEC;
    printf("\n\t Tempos L Ordenada Cod: inic %f, fim %f, total %f\n", (float)inic1/CLOCKS_PER_SEC,
            (float)fim1/CLOCKS_PER_SEC, res1);
    system("CLS");

    clock_t inic2 = clock();
    gerarListaOrdNom(L, LOrdNom);
    clock_t fim2 = clock();

    double res2 = (double)(fim2 - inic2)/CLOCKS_PER_SEC;
    printf("\n\t Tempos L Ordenada por Nome: inic %f, fim %f, total %f\n", (float)inic2/CLOCKS_PER_SEC,
           (float)fim2/CLOCKS_PER_SEC, res2);
    system("CLS");

    gerarArquivo(LOrdCod, "saidaOrdCod.txt");
    gerarArquivo(LOrdNom, "saidOrdNome.txt");
}

//varre uma lista e exibe todos os seus elementos
void exibirLista(Lista *L){
    Elemento *cursor = L->primeiro;
    system("CLS");

    while(cursor != NULL){
        printf("\n\t Cidade: %s, Cod: %d, Populacao: %d \n", cursor->conteudo->nome,
               cursor->conteudo->numero, cursor->conteudo->populacao);
        cursor = cursor->prox;
    }
}

//gera arquivo de saida ordenando por codigo de uma cidade
void gerarListaOrdCod(Lista *L, Lista *LOrdCod){
    printf("\n\t Gerando lista Ordenada por codigo");
    Elemento *cursor = L->primeiro;
    while(cursor != NULL){
       inserirOrdCod(LOrdCod, cursor->conteudo);
       cursor = cursor->prox;
    }
    printf("\n\t Lista de Nome gerada");
}

//insere na lista ordenando pelo codigo da cidade
void inserirOrdCod(Lista *LOrdCod, Cidade *cid){
    Elemento *cursor  = LOrdCod->primeiro;
    Elemento *anterior = NULL;
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->conteudo = cid;
    novo->ant = NULL;
    novo->prox = NULL;

    if(cursor == NULL){
        LOrdCod->primeiro = novo;
        LOrdCod->ultimo = novo;
        LOrdCod->total = 1;
    }else{
        while(cursor != NULL && cursor->conteudo->numero < novo->conteudo->numero){
            anterior = cursor;
            cursor = cursor->prox;
        }
        novo->prox = cursor;
        if(anterior == NULL){
            LOrdCod->primeiro = novo;
        }else{
            anterior->prox = novo;
        }

    }
}

//varre a lista exibindo todos os elementos
void gerarListaOrdNom(Lista *L, Lista *LOrdNom){
    printf("\n\t Gerando lista Ordenada por Nome");
    Elemento *cursor = L->primeiro;
    while(cursor != NULL){
        inserirOrdNom(LOrdNom, cursor->conteudo);
        cursor = cursor->prox;
    }
}

void inserirOrdNom(Lista *L, Cidade *cid){

    Elemento *cursor  = L->primeiro;
    Elemento *anterior = NULL;
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->conteudo = cid;
    novo->ant = NULL;
    novo->prox = NULL;

    if(cursor == NULL){
        L->primeiro = novo;
        L->ultimo = novo;
        L->total = 1;
    }else{
        while(cursor != NULL && strcmp(cursor->conteudo->nome, novo->conteudo->nome) < 0){
            anterior = cursor;
            cursor = cursor->prox;
        }
        novo->prox = cursor;
        if(anterior == NULL){
            L->primeiro = novo;
        }else{
            anterior->prox = novo;
        }
    }
}

void gerarArquivo(Lista *listaGen, char* nomeArq){
    FILE *arquivo = fopen(nomeArq,"wt");
    printf("\n\n");
    int res;
    if(arquivo == NULL)
        printf("\n\t Erro ao criar arquivo");
    else{
        Elemento *cursor = listaGen->primeiro;
        while(cursor->prox != NULL){
            printf("\n\t Gravando: %d %s %d %p prox: %s", cursor->conteudo->numero,
                    cursor->conteudo->nome, cursor->conteudo->populacao, cursor->conteudo,
                    cursor->prox->conteudo->nome);
            res = fprintf(arquivo, "%d;%s;%d;%p\n", cursor->conteudo->numero,
                    cursor->conteudo->nome, cursor->conteudo->populacao, cursor->conteudo);
            if(res == EOF)
                printf("\n\t Erro ao escrever no arquivo");
            cursor = cursor->prox;
        }
    }
    fclose(arquivo);
}

int excluirPorNome(Lista *L, char* nome){
    int excluido = 1;
    Elemento *elemento = NULL;
    elemento = buscarElementoPorNome(L, nome);
    if(elemento != NULL){
         if(elemento->ant != NULL)
            elemento->ant->prox = elemento->prox;
        else
            L->primeiro = elemento->prox;
        if(elemento->prox != NULL)
            elemento->prox->ant = elemento->ant;
        else
            L->ultimo = elemento->ant;
        free(elemento);
        excluido = 0;
    }
    return excluido;
}

int excluirPorCodigo(Lista *L, int cod){
    int excluido = 1;
    Elemento *elemento = NULL;
    elemento = buscarElementoPorCodigo(L, cod);
    if(elemento != NULL){
        if(elemento->ant != NULL)
            elemento->ant->prox = elemento->prox;
        else
            L->primeiro = elemento->prox;
        if(elemento->prox != NULL)
            elemento->prox->ant = elemento->ant;
        else
            L->ultimo = elemento->ant;
        free(elemento);
        excluido = 0;
    }
    return excluido;
}

