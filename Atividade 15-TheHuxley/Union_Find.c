#include <stdio.h>
#include <stdlib.h>

typedef struct Amigo{
	int key;
	int tam;
	struct Amigo* prox;
	struct Amigo* raiz;
}amigo;

amigo* raiz(amigo* a){
	amigo* aux = a->raiz;
	while(aux->raiz->key != aux->key){
		aux = aux->raiz;
	}
	return aux;
}

void insere(amigo* raiz, amigo* new){
	amigo* aux = raiz->prox;
	while(aux != NULL){
		aux = aux->prox;
	}
	aux->prox = new;
	new->raiz = aux;
}

int main(int argc, char **argv){
	int ntestes, npessoas, npares, index, i, x, y;
	scanf("%d",&ntestes);
	int maior[ntestes];
	for(index=0;index<ntestes;index++){
		scanf("%d %d",&npessoas, &npares);
		npessoas++;
		amigo* amizade = (amigo*)malloc(npessoas*sizeof(amigo));
		for(i=1;i<(npessoas+1);i++){
			amizade[i].key = i;
			amizade[i].tam = 1;
			amizade[i].prox = NULL;
			amizade[i].raiz = &amizade[i];
		}
		amigo* aux;
		//int root;
		for(i=0;i<npares;i++){
			scanf("%d %d",&x, &y);
			aux = raiz(&amizade[y]);
			insere(aux,&amizade[x]);
			//amizade[x].raiz = aux;
			//root = aux->key;
			//(amizade[root].tam)++;
			//printf("X = %d\nRaiz de X = %d\n",x , amizade[x].raiz->key);
		}
		maior[index] = amizade[1].tam;
		for(i=1;i<npessoas;i++){
			if(amizade[i+1].tam > maior[index]){
				maior[index] = amizade[i+1].tam;
			}
		}
	
	}
	for(index=0;index<ntestes;index++){
		printf("%d\n",maior[index]);
	}
	
	return 0;
}
