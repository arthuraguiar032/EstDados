#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/*Nó, que vai servir de base para todas as estruturas*/
typedef struct no{
    int v;
    struct no *prox;
}No;

/*Implementação de Grafo e suas funções*/
typedef struct grafo{
    int vertices;
    int arestas;
    No **adj;
}Grafo;

Grafo* initGrafo(int n){
    int m= n+1;
    Grafo *g = (Grafo*) malloc(sizeof(struct grafo));
    if(g!=NULL){
        g->vertices=n;
        g->arestas=0;
        g->adj= malloc((m)*sizeof(No*));
        for(int i =1; i<m; i++){
            g->adj[i]=NULL;
        }
    }else{
        exit(1);
    }
    return g;
}

void freeGrafo(Grafo *gr){
    int m = gr->vertices +1;
    No *aux;
    for(int i=1; i<m; i++){
        aux = gr->adj[i];
        while(aux!=NULL){
            gr->adj[i]=aux;
            aux=aux->prox;
            free(gr->adj[i]);
        }
    }
    free(gr->adj);
    free(gr);
}

void insereAresta(Grafo *g, int v1, int v2){
    No *aux;
    for(aux=g->adj[v1]; aux!=NULL; aux=aux->prox){
        if(aux->v==v2){
            return;//aresta já existe
        }
    }
    //aresta nao existe
    No* n = malloc(sizeof(No));
    n->v=v2;
    n->prox=g->adj[v1];
    g->adj[v1]=n;
    g->arestas++;
}

void printGrafo(Grafo g){
    No *aux;
    int m = g.vertices +1;
    printf("%d %d\n", g.vertices, g.arestas);
    for(int i =1; i<m; i++){
        printf("%d: ", i);
        for(aux=g.adj[i]; aux!=NULL; aux=aux->prox){
            printf("%d ", aux->v);;
        }
        printf("\n");
    }
}

/*Implementação de Fila e suas funções*/
typedef struct fila{
    No *inicio;
    No *fim;
}Fila;

Fila* initFila(){
    Fila *f = (Fila*) malloc(sizeof(struct fila));
    f->inicio=NULL;
    f->fim=NULL;

    return f;
}

void freeFila(Fila *f){
    No *aux;

    if(f->inicio!=NULL){
        aux=f->inicio;
        while(aux!=NULL){
            f->inicio=aux->prox;
            free(aux);
            aux=f->inicio;
        }
        free(f);
    }
}

void pushFila(Fila *f, int dado){
    No *elem;
    elem=malloc(sizeof(struct no));

    elem->v=dado;
    elem->prox=NULL;

    if(f->inicio==NULL){
        f->inicio=elem;
    } else{
        f->fim->prox=elem;
    }

    f->fim=elem;
}

int popFila(Fila *f){
    No *aux;

    if(f->inicio==NULL){
        return -1;
    }

    aux = f->inicio;
    f->inicio = aux->prox;
    if(f->inicio==NULL){
        f->fim=NULL;
    }

    int n = aux->v;
    free(aux);
    return n;
}

int isEmptyFila(Fila *f){
    return(f->inicio==NULL);
}

void printFila(Fila *f){
    No *aux;
    aux = f->inicio;
    while(aux!=NULL){
        printf("%d ", aux->v);
        aux=aux->prox;
    }
}

/*Implementação de Pilha Dinamica*/
typedef struct pilha{
    No *topo;
} Pilha;

Pilha* initPilha(){
    Pilha *p = (Pilha*) malloc(sizeof(struct pilha));
    p->topo=NULL;
    return p;
}

void freePilha(Pilha *pi){
    No *aux;
    No *aux2 = pi->topo;
    while(aux2!=NULL){
        aux = aux2;
        aux2 = aux2->prox;
        free(aux);
    }
    free(pi);
}

void pushPilha(Pilha *pi, int dado){
    No *elem;
    elem = malloc(sizeof(struct no));

    elem->v=dado;
    elem->prox = pi->topo;
    pi->topo = elem;
}

int popPilha(Pilha *pi){
    if(pi->topo==NULL) return -1;

    int n = pi->topo->v;
    No *aux = pi->topo;
    pi->topo=pi->topo->prox;
    free(aux);
    return n;
}

int isEmptyPilha(Pilha *pi){
    return (pi->topo==NULL);
}

void printPilha(Pilha *pi){
    No *aux;
    aux = pi->topo;
    printf("%d", aux->v);

    while(aux->prox!=NULL){
        printf(" -> ");
        aux=aux->prox;
        printf("%d", aux->v);
    }
}

/*Ordenação Topologica, usando algoritmo de Khan, usando pilha para armazenar os vertices com grau de entrada 0, e fila para armazenar os vértices já ordenados para impressão*/
/*L - fila dos elementos ordenados
  S - pilha de vertices que com grau de entrada 0
  I - vetor dinamico com os graus de entrada
*/
void OrdenacaoTopologica(Grafo *g){
    Fila *L;
    L = initFila();
    Pilha *S;
    S = initPilha();

    //calculando graus de entrada
    int n = g->vertices +1;
    int *I;
    I = (int*) calloc(n, sizeof(int));
    for(int i=1; i<n; i++){
        No *aux;
        for(aux=g->adj[i]; aux!=NULL; aux=aux->prox){
            I[aux->v]++;
        }
    }

    //verficando se o calculo deu certo
    /*for(int i =1;i<n;i++){
        printf("\n%d: %d", i, I[i]);
    }*/

    //inserindo graus de entrada 0 na pilha
    for(int i =1; i<n; i++){
        if(I[i]==0){
            pushPilha(S, i);
        }
    }

    printf("\n");

    while(!isEmptyPilha(S)){
        int v = popPilha(S);
        pushFila(L, v);
        I[v]=-1;
        No *aux;
        for(aux=g->adj[v]; aux!=NULL; aux=aux->prox){
            //remover as arestas que partem de v
            I[aux->v]--;
            g->arestas--;
            if(I[aux->v]==0){
                pushPilha(S, aux->v);
            }
        }
    }

    freePilha(S);
    free(I);
    if(g->arestas!=0){
        //grafo possui ciclo
        printf("ERRO! O grafo é ciclíco. Ainda possui %d arestas.", g->arestas);
    }else {
        printFila(L);
        freeFila(L);
    }
}

int countDigits(int num){
    if(num ==0){
        return 1;
    } else{
        return (ceil(log10(abs(num)+1)));
    }
}

void limpaBuffer(){
    char c;
    while ( (c = getchar()) != '\n')
        c = getchar();
}

int main(int argc, char *argv[]){
    int v,a;
    scanf("%d %d", &v, &a);
    limpaBuffer();

    Grafo *gr;
    gr = initGrafo(v);

    int digitos = countDigits(v);
    printf("%d\n", digitos);
    int contLinhas = 1;
    int contArestas = 0;

    char str[digitos];
    strcpy(str, "");
    printf("%s\n", str);

    char c = getchar();
    while(contArestas<a){
        if(c=='\n'){
            contLinhas++;
        }else{
            if(isdigit(c)){
                while(isdigit(c)){
                    strcat(str,(char) c);
                    c=getchar();
                }
                int num;
                sscanf(str, "%d", &num);
                insereAresta(gr, contLinhas, num);
            } else{
                c=getchar();
            }
        }
    }

    if(a!=gr->arestas){
        exit(-1);//ERRO
    }

    OrdenacaoTopologica(gr);
    freeGrafo(gr);

    return 0;
}
