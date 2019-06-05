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

int alt_No(struct Node *no){
	if(no == NULL) return -1;
	else return no->alt;
}

int fat_bal(node *no){
	return labs((alt_No(no->esq)) - (alt_No(no->dir)));
}

int maior(int x, int y){
	if(x > y) return x;
	else return y;
}

void rotacaoLL(node **raiz){
	node *no;
	no = (*raiz)->esq;
	(*raiz)->esq = no->dir;
	no->dir = *raiz;
	(*raiz)->alt = maior(alt_No((*raiz)->esq),alt_No((*raiz)->dir)) + 1;
	no->alt = maior(alt_No(no->esq), (*raiz)->alt) + 1;
	*raiz = no;
}

void rotacaoRR(node **raiz){
	node *no;
	no = (*raiz)->dir;
	(*raiz)->dir = no->esq;
	no->esq = *raiz;
	(*raiz)->alt = maior(alt_No((*raiz)->esq),alt_No((*raiz)->dir)) + 1;
	no->alt = maior(alt_No(no->dir), (*raiz)->alt) + 1;
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
			if(fat_bal(atual) > 1){
				if( key < atual->esq->key ){
					rotacaoLL(raiz);
				}
				else{
					rotacaoLR(raiz);
				}
			}
		
	}
	else{
			insere(&(atual->dir), key);
				if(fat_bal(atual) > 1){
					if( atual->dir->key < key ){
						rotacaoRR(raiz);
					}
					else{
						rotacaoRL(raiz);
					}
				}
			
	}
	atual->alt = maior(alt_No(atual->esq),alt_No(atual->dir)) + 1;
	return 1;
}

/*void busca(node *raiz, char valor[200]){
	node *no = raiz;
	int i;
	if(raiz == NULL){
		fprintf(output,"?:\n");
		fprintf(output,"[-]\n");
		return;
	}
	if(strcmp(valor,no->info) < 0){
		fprintf(output,"%s->",no->info);
		busca(no->esq, valor);
		return;
	}
	if(strcmp(valor,no->info) > 0){
		fprintf(output,"%s->",no->info);
		busca(no->dir, valor);
		return;
	}
	fprintf(output,"%s:\n",no->info);
		fprintf(output,"[");
		for(i=0;i<no->nsin;i++){
			fprintf(output,"%s",no->sin[i]);
			if(i == (no->nsin) - 1) break;
			fprintf(output,", ");
		}
		fprintf(output,"]\n");
	return;
}*/

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
	
	while(1){
		int key;
		scanf("%d",&key);
			EPD(raiz,v,pos,a,res,key);
			altura = -1;
			resposta = -1;
			npos = 0;
			puts("");
	}
	
	
	if(resposta == -1) printf("\nNAO ESTA NA ARVORE\n%d",resposta);
	else printf("\nESTA NA ARVORE\n%d",resposta);
	
	return 0;
}
