#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
typedef struct Node{
	int key;
	int alt;
	struct Node *esq;
	struct Node *dir;
}node;

node *inicia(){
	node *raiz = (node*)malloc(sizeof(node));
	raiz = NULL;
	return raiz;
}

int alt_No(node *no){
   
    int esq, dir;
   
    if ( no == NULL ) return -1;
   
    esq = alt_No ( no->esq );
    dir = alt_No ( no->dir );
   
    if ( esq > dir )
        return esq + 1;
    else
        return dir + 1;
}

int fat_bal(node *no){
	return alt_No(no->esq) - alt_No(no->dir);
}

void rotacaoLL(node **raiz){
	node *no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->alt = alt_No((*raiz)->dir) - alt_No((*raiz)->esq);
	no->alt = alt_No(no->dir) - alt_No(no->esq);
	*raiz = no;
}

void rotacaoRR(node **raiz){
	node *no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = *raiz;
	(*raiz)->alt = alt_No((*raiz)->dir) - alt_No((*raiz)->esq);
	no->alt = alt_No(no->dir) - alt_No(no->esq);
	*raiz = no;
}

void rotacaoLR(node **raiz){
	rotacaoRR(&(*raiz)->esq);
	rotacaoLL(raiz);	
}

void rotacaoRL(node **raiz){
	rotacaoLL(&(*raiz)->dir);
	rotacaoRR(raiz);
}

int insere(node **raiz, int key){
	if(*raiz == NULL){
		node *novo = (node*)malloc(sizeof(node));
		if(novo == NULL) return 0;
		novo->key = key;
		novo->alt = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return 1;
	}
	node *atual = *raiz;
	if( key < atual->key ){
			insere(&(atual->esq), key);
				if (fat_bal(atual) == 2 ){
					if(fat_bal(atual->esq) == 1 ) rotacaoLL(raiz);
					else rotacaoLR(raiz);
				}
		
	}
	else{
			insere(&(atual->dir), key);
				if(fat_bal(atual) == -2){
					if( fat_bal(atual->dir) == -1 ) rotacaoRR(raiz);
					else rotacaoRL(raiz);
				}
			
	}
	atual->alt = fat_bal(atual);
	return 1;
}

void EPD(node *no, int *v, int *pos, int *a, int *res, int key){
	if(no != NULL){
		*a = *a + 1;
		if(no->key == key) *res = *a;
		EPD(no->esq,v,pos,a,res,key);
		printf("-%d",no->key);
		v[*pos] = no->key;
		*pos = *pos + 1;
		EPD(no->dir,v,pos,a,res,key);
		*a = *a - 1;
	}
}

int main(int argc, char* argv[]){
	node* raiz = inicia();
	int n,i,x;
		scanf("%d",&n);
		for(i=0;i<n;i++){
			scanf("%d",&x);
			insere(&raiz,x);
		}
		
	
	int *pos;
	int npos = 0;
	pos = &npos;
	int v[200];
	
	int altura = -1;
	int *a = &altura;
	
	int resposta = -1;
	int *res = &resposta; 
	
	int key;
	while(1){
		scanf("%d",&key);
		
		EPD(raiz,v,pos,a,res,key);
		
		
		if(resposta == -1) printf("\nNAO ESTA NA ARVORE\nAltura: %d\n",resposta);
		else printf("\nESTA NA ARVORE\nAltura: %d\n",resposta);
	}
	
	return 0;
}
