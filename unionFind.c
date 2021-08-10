#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dsu{
    int *pai;
    int *tamanho;
}DSU;

DSU* initDSU(int n){
    DSU *c = (DSU*) malloc(sizeof(struct dsu));
    c->pai = (int *)malloc((n+1)*sizeof(int));
    c->tamanho = (int *)malloc((n+1)*sizeof(int));

    for(int i =1;i<n+1;i++){
        c->pai[i] = i;
        c->tamanho[i] = 1;
    }

    return c;
}

void freeDSU(DSU *c){
    free(c->pai);
    free(c);
}

void swap(int *x, int *y){
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;
}

int find(DSU *c, int p){
    if(c->pai[p]==p){
        return p;
    }else {
        c->pai[p] = find(c, c->pai[p]);
        return c->pai[p];
    }
}

void unionn(DSU *c, int p, int q){
    p = find(c, p);
    q = find(c, q);

    if(p==q){
        return; //ja fazem parte do mesmo conjunto
    }else{
        if(c->tamanho[p]>c->tamanho[q]){
            swap(&p, &q);
        } ////p sempre vai ser menor, para juntar a arvore menor na maior
        c->pai[p] = q;
        c->tamanho[q] += c->tamanho[q];
    }
}

int main(){

    DSU *conjuntos;
    int n,m;
    char res[50]; //mesnagem printada na tela no final
    res[0] = '\0';
    int contador =0;
    scanf("%d %d", &n, &m);

    while(n!=0&&m!=0){
        contador++;
        conjuntos = initDSU(n);

        for(int i =0; i<m; i++){//fazendo as unioes
            int x,y;
            scanf("%d %d", &x, &y);
            unionn(conjuntos, x, y);
        }

        //contando quantas religioes existem para esse caso
        int religioes =0;
        for(int i =1; i<n+1; i++){
            if(conjuntos->pai[i]==i){
                religioes++;
            }
        }


        //adicionando a quantidade de religoes a string que vai ser printada
        if(strlen(res)==0){
            snprintf(res, 50, "Case %d: %d\n", contador, religioes);
        }else {
            char aux[12];
            aux[0]='\0';
            snprintf(aux, 12, "Case %d: %d\n", contador, religioes);
            strcat(res, aux);
        }

        freeDSU(conjuntos);
        scanf("%d %d",&n,&m);
    }

    printf("%s", res);
    return 0;
}
