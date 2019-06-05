#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char chave[51];
	char tipo[3];
	int tam;
	int ord;
	
	struct Node *esq, *dir;
}node;

int ordem = 0;

node *inicia(){
	node *raiz = (node*)malloc(sizeof(node));
	raiz = NULL;
	return raiz;
}

void insere(node **r,char key[51],char type[3],int size){
	if (*r == NULL){
		*r = (node*)malloc(sizeof(node));
			if (*r == NULL) return;
		(*r)->esq = NULL;
		(*r)->dir = NULL;
		strcpy((*r)->chave,key);
		strcpy((*r)->tipo,type);
		(*r)->tam = size;
		(*r)->ord = ordem;
		ordem ++;
		return;
	}
	if (strcmp(key,(*r)->chave) < 0){
		insere(&((*r)->esq),key,type,size);
	}
	if (strcmp(key,(*r)->chave) > 0){
		insere(&((*r)->dir),key,type,size);
	}
	if (strcmp(key,(*r)->chave) == 0){
		if(strcmp((*r)->tipo,"ro") == 0){
			return;
		}
		if(strcmp((*r)->tipo,"rw") == 0){
			strcpy((*r)->tipo,type);
			(*r)->tam = size;
			(*r)->ord = ordem;
			ordem ++;
		}
	}
}
void EPD(FILE* output,node *no){
	if(no != NULL){
		EPD(output,no->esq);
		fprintf(output,"%d %s %s %d byte",no->ord,no->chave,no->tipo,no->tam);
		if(no->tam > 1) fputc('s',output);
		fputc('\n',output);
		EPD(output,no->dir);
	}
}

void PED(FILE* output,node *no){
	if(no !=NULL){
		fprintf(output,"%d %s %s %d byte",no->ord,no->chave,no->tipo,no->tam);
		if(no->tam > 1) fputc('s',output);
		fputc('\n',output);
		PED(output,no->esq);
		PED(output,no->dir);
	}
}

void EDP(FILE* output,node *no){
	if(no != NULL){
		EDP(output,no->esq);
		EDP(output,no->dir);
		fprintf(output,"%d %s %s %d byte",no->ord,no->chave,no->tipo,no->tam);
		if(no->tam > 1) fputc('s',output);
		fputc('\n',output);
	}
}

int main (int argc, char* argv[]){
	FILE* input = fopen(argv[1],"r");
	FILE* output = fopen(argv[2],"w");
	node *raiz = inicia();
		int n, size,i;
		char key[51]={0}, type[3]={0};
		fscanf(input,"%d%*c",&n);
			for(i=0;i<n;i++){
				fscanf(input,"%s %s %d%*c",key,type,&size);
				insere(&raiz,key,type,size);
				key[0] = '\0';
				type[0] = '\0';
			}
			fputs("EPD:\n",output);
			EPD(output,raiz);
			fputs("PED:\n",output);
			PED(output,raiz);
			fputs("EDP:\n",output);
			EDP(output,raiz);
	return 0;
}
