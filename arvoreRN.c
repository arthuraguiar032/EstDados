#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct no{
    int chave;
    int cor;
    struct no *esq;
    struct no *dir;
    struct no *pai;
}No;

No* initArvRN(){
    return NULL;
}

void freeArvRN(No *ptraiz){
    if(ptraiz!=NULL){
        freeArvRN(ptraiz->esq);
        freeArvRN(ptraiz->dir);
        free(ptraiz);
    }
}

void printPreOrdem(No *ptraiz){
    if(ptraiz!=NULL){
        printf("%d", ptraiz->chave);
        if(ptraiz->cor==RED){
            printf("R ");
        }else if(ptraiz->cor==BLACK){
            printf("N ");
        }
        printPreOrdem(ptraiz->esq);
        printPreOrdem(ptraiz->dir);
    }
}

/*Rotações*/
void rotacaoEsq(No *ptraiz){
    struct no *aux;
    aux = ptraiz->dir;
    ptraiz->dir = aux->esq;
    aux->esq->pai = ptraiz;

    if(ptraiz->pai==NULL){
        aux->pai=NULL;
    }else if(ptraiz==ptraiz->pai->esq){
        ptraiz->pai->esq = aux;
    }else if(ptraiz==ptraiz->pai->dir){
        ptraiz->pai->dir = aux;
    }

    aux->esq = ptraiz;
    ptraiz->pai = aux;
}

void rotacaoDir(No *ptraiz){
    struct no *aux;
    aux = ptraiz->esq;
    ptraiz->esq = aux->dir;
    aux->dir->pai = ptraiz;

    if(ptraiz->pai==NULL){
        aux->pai=NULL;
    }else if(ptraiz==ptraiz->pai->esq){
        ptraiz->pai->esq = aux;
    }else if(ptraiz==ptraiz->pai->dir){
        ptraiz->pai->dir = aux;
    }

    aux->dir = ptraiz;
    ptraiz->pai = aux;

}

void inverteCor(No *ptraiz){
    ptraiz->cor = !ptraiz->cor;

    if(ptraiz->esq!=NULL){
        ptraiz->esq->cor = !ptraiz->esq->cor;
    }
    if(ptraiz->dir!=NULL){
        ptraiz->dir->cor = !ptraiz->dir->cor;
    }
}

//retorna o avô de um determinado nó passado
No* avo(No *ptraiz){
    if(ptraiz!=NULL && ptraiz->pai!=NULL){
        return ptraiz->pai->pai;
    } else {
        return NULL;
    }
}

//retorna o tio de um determinado nó passado
No* tio(No *ptraiz){
    No *aux = avo(ptraiz);
    if(aux==NULL){
        return NULL;
    }
    if(ptraiz->pai == aux->esq){
        return aux->dir;
    }else if(ptraiz->pai == aux->dir){
        return aux->esq;
    }
}

No* insereArvRN(No *ptraiz, int valor){

    if(ptraiz==NULL){
        No *novo = (No*) malloc(sizeof(struct no));
        novo->chave=valor;
        novo->esq=NULL;
        novo->dir=NULL;
        novo->cor=RED;

        //caso 1: nó na raiz
        if(ptraiz->pai==NULL){
            novo->pai=NULL;
            return novo;
        }else{
            novo->pai=ptraiz;
            if(ptraiz->cor==BLACK){//caso 2: pai preto
            }else if(ptraiz->cor==RED&&tio(novo)!=NULL&&tio(novo)->cor==RED){//caso 3: pai e tio vermelhos
                inverteCor(avo(novo));
            }else if(ptraiz->cor==RED&&tio(novo)==BLACK){ //caso 4: pai preto e tio vermelho, e novo é filho da direita do ptraiz, e ptraiz filho à esquerda de seu pai
                if(novo == novo->pai->dir && novo->pai == avo(novo)->esq){
                    rotacaoEsq(novo->pai);
                    novo=novo->esq;
                }else if(novo==novo->pai->esq && novo->pai == avo(novo)->dir){
                    rotacaoDir(novo->pai);
                    novo=novo->dir;
                }
                ptraiz->cor=BLACK;
                avo(novo)->cor=RED;
                if(novo==novo->pai->esq && novo->pai == avo(novo)->esq){
                    rotacaoDir(avo(novo));
                }else{
                    rotacaoEsq(avo(novo));
                }

            }else if(ptraiz->cor==RED&&tio(novo)==BLACK){ //caso 5: pai vermelho e tio preto
                ptraiz->cor=BLACK;
                avo(novo)->cor=RED;
                if(novo==novo->pai->esq && novo->pai == avo(novo)->esq){
                    rotacaoDir(avo(novo));
                }else{
                    rotacaoEsq(avo(novo));
                }
            }
            return novo;
        }
    }else{
        if(valor<ptraiz->chave){
            ptraiz->esq = insereArvRN(ptraiz->esq, valor);
        }else if(valor>ptraiz->chave){
            ptraiz->dir = insereArvRN(ptraiz->dir, valor);
        }
    }
}

int main(){

    No *raiz = initArvRN();

     while(!feof(stdin)){
        int var;
        scanf("%d", &var);
        raiz = insereArvRN(raiz, var);
    }

    printPreOrdem(raiz);
    freeArvRN(raiz);


    return 0;
}
