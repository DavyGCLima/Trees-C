#include "arvore.h"

//inicializa uma arvore
void inicializaArvore(TNo *R){
    R = NULL;
}

//aloca o nó e inicializa os ponteiros
TNo* inicializaNo(TNo *R){
    R = (TNo*)malloc(sizeof(TNo));
    R->conteudo = NULL;
    R->dir = NULL;
    R->esq = NULL;
    R->fator = 0;
    return R;
}

//adiciona a cidade ao no e insere na arvore
void preInsercao(TNo *R, TNo *no, Cidade *cid){
    inicializaNo(no);
    R->conteudo = cid;
}

//insere na aravore, decide apenas se colocará na raiz ou não
TNo* insereArvore(TNo *R, TNo *no){
    if(R != NULL){
        //inserção recursiva
        insereRecursivo(R, no);
    }else{
        R = no;
    }
    return R;
}

//insere um elemento em uma arvore, depois verifica a necessidade de balanceamento,
//caso sim realiza as rotações necessarias
TNo* insereArvoreAvl(TNo *R, TNo *no){
    int fatorBal, fatorBalDir, fatorBalEsq, fatorBalFilho;
    R = insereArvore(R, no);

    //após inserir verificar a necessidade de valancear a arvore
    if(!verificaBalanceamento(R)){
        fatorBal = obterFatorBalanceamento(R);
        fatorBalDir = obterFatorBalanceamento(R->dir);
        fatorBalEsq = obterFatorBalanceamento(R->esq);


        if(no->conteudo->numero > R->conteudo->numero){
            fatorBalFilho = fatorBalDir;

            if((fatorBal == 2)&&(fatorBalFilho >= 1)){
                //rotação simples a esquerda
                rotacaoAEsquerda(R);
            }
            if((fatorBal == 2)&&(fatorBalFilho <= -1)){
                //rotação dupla direita_esquerda
                rotacaoDireitaEsquerda(R);
            }
        }else{
            fatorBalFilho = fatorBalEsq;

            if((fatorBal == -2) && (fatorBalFilho <= -1)){
                //rotação simples a direita
                rotacaoADireita(R);
            }//if

            if((fatorBal == -2) && (fatorBalFilho >= 1)){
                //rotacao dupla esquerda_direita
                rotacaoEsquerdaDireita(R);
            }//if
        }
    }
    return R;
}

//insere o elemento na aravore percorrendo ela
void insereRecursivo(TNo *rAtual, TNo *novo){
    if ( novo->conteudo->numero < rAtual->conteudo->numero) {
        //desce pela direita da arvore
        if (rAtual->esq == NULL) {
            rAtual->esq = novo;
        }
        else {
            //chamada recursiva
            insereRecursivo(rAtual->esq, novo);
        }
    }
    else {
        //desce pela esquerda da arvore
        if (rAtual->dir == NULL) {
            rAtual->dir = novo;
        }
        else {
            //chamada recursiva
            insereRecursivo(rAtual->dir, novo);
        }
    }
}

//gera um no baseado na cidade
TNo* geraNo(Cidade *cid){
    TNo *novo = NULL; //= (TNo*)malloc(sizeof(TNo));
    novo = inicializaNo(novo);
    novo->conteudo = cid;
    return novo;
}

//busca um nó a partir de um codigo
TNo* buscaNo(TNo *R, int cod, int *cont) {
    *cont += 1;
	if (R != NULL) {
		printf("no atual: %d ,%s\n", R->conteudo->numero, R->conteudo->nome);
		if (R->conteudo->numero == cod) {
			//RETIRAR O PRINT
			printf("\n\n No encontrado %d, %s\n",R->conteudo->numero, R->conteudo->nome);
			return R;
		}
		else {
			if (cod > R->conteudo->numero) {
                printf("Descendo pela direita do no\n");
                R = buscaNo(R->dir, cod, cont);
			}
			else {
                printf("Descendo pela esquerda do no\n");
                R = buscaNo(R->esq, cod, cont);
			}
		}//fim if
	}else{
        printf("Arvore nula\n");
        return NULL;
	}
	return R;
}

int obterAlturaArvore(TNo *R){
    //Obtem a altura da arvore
    int dir = 0 ,esq = 0;
    if (R == NULL)	{
        return 0;
    }else{
        dir = obterAlturaArvore(R->dir);
        esq = obterAlturaArvore(R->esq);
        if (dir > esq){
            return dir + 1;
        }else{
            return esq + 1;
        }
    }
}

//verifica a necessidade de balancear uma arvore ou sub arvore
int verificaBalanceamento(TNo *R){
    //Verifica se a áavore está balanceada.
    int fatorBalanceamento = obterFatorBalanceamento(R);
    int resultado;
    if(fatorBalanceamento > 1){
        resultado = 0;
    }else if(fatorBalanceamento < -1){
        resultado = 0;
    }else{
        resultado = 1;
    }
    return resultado;
}

//calcula o balancemaneto de uma arvore ou sub arvore
int obterFatorBalanceamento(TNo *R){
    if (R == NULL){
    	return 0;
	}else {
        int alturaDir = obterAlturaArvore(R->dir);
	    int alturaEsq = obterAlturaArvore(R->esq);
	    int fatorBalanceamento = alturaDir - alturaEsq;

	    return fatorBalanceamento;
	}

}

void rotacaoAEsquerda(TNo *R){
	TNo *filho, *temp;
	filho = R->dir;
	temp = filho->esq;
	filho->esq = R;
	R->dir = temp;
	R = filho;
}

void rotacaoADireita(TNo *R){
	TNo *filho, *temp;

	filho = R->esq;
	temp = filho->dir;
	filho->dir = R;

	R->esq = temp;
	R = filho;
}

void rotacaoDireitaEsquerda(TNo *R){
    rotacaoADireita(R->dir);
    rotacaoAEsquerda(R);
}

void rotacaoEsquerdaDireita(TNo *R){
	rotacaoAEsquerda(R->esq);
	rotacaoADireita(R);
}

//caminah por nivel, e escreve o arquivo
//esta função deveria estar nos arquivos de arvore, mas como estou reaproveitando estruturas sem redefinilas com outroas
//nomes, está aqui, além disso, não posso incluir fila em arvore e arvore em fila pois gerararia um loop infinito
// mesmo utilizando o ifndef
//a função utiliza uma fila que armazena todos os nos de um nivel, depois retira eles os informando quais são
void caminhaEmNivel(TNo **R, char *nomeArq){
    FILE *arq = fopen(nomeArq, "w");
    if(!arq)
         printf("\n\t Erro ao criar arquivo %s ", nomeArq);
    else{
        Elo *el = geraElo(*R);
        Elo *n;
        Fila *f = NULL;
        int cont;
        if(R != NULL){
            f = inicializaFila(f);
            insereFila(f, el);
            while(filaVazia(f) != 1){
                n = removeFila(f);
                if(n->no->esq != NULL){
                    Elo *nElo = geraElo(n->no->esq);
                    nElo->nivel = n->nivel + 1;
                    insereFila(f, nElo);
                }
                if(n->no->dir != NULL){
                    Elo *nElo = geraElo(n->no->dir);
                    nElo->nivel = n->nivel + 1;
                    insereFila(f, nElo);
                }
                cont++;
                fprintf(arq, "%d;%d;%s;%d;%p\n", n->nivel,
                        n->no->conteudo->numero, n->no->conteudo->nome, n->no->conteudo->populacao
                        , n->no->conteudo);
            }
        }
    }
    fclose(arq);
}

