#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Node{
	int key;
	struct Node* esq;
	struct Node* dir;
}node;

node *inicia(){
	node* raiz = (node*)malloc(sizeof(node));
	raiz = NULL;
	return raiz;
}
void insereEsq(node** r, char str[200], int* i){
	(*i)++;
	if(strlen(str)  <= *i) return;
	if(*r == NULL){
		char skey[10];
		int key;
		int j = 0;
		while(str[(*i)] != '(' ){
			skey[j] = str[(*i)];
			(*i)++;
			j++;
		}
		skey[j] = '\0';
		key = atoi(skey);
		node* no = (node*)malloc(sizeof(node));
		no->key = key;
		no->esq = NULL;
		no->dir = NULL;
		*r = no;
	}//ate aqui a raiz
	
	//Esquerda inicio
	if(str[*i] == '(' && str[(*i)+1] == ')'){
		(*r)->esq = NULL;
		*i = *i + 2;
	}
	else insereEsq(&((*r)->esq),str,i);
	//Esquerda fim
	
	//Direita inicio
	if(str[*i] == '(' && str[(*i)+1] == ')'){
		(*r)->dir = NULL;
		*i = *i + 2;
	}
	else insereEsq(&((*r)->dir),str,i);
	//Direita fim
	
	*i = *i + 1;
	
	return;
	
}

void EPD(node *no, int *v, int *pos){
	if(no != NULL){
		EPD(no->esq,v,pos);
		printf("-%d",no->key);
		v[*pos] = no->key;
		*pos = *pos + 1;
		EPD(no->dir,v,pos);
	}
}

int main(int argc, char **argv){
	node *r = inicia();
	int* p ;
	int ind = 0;
	p = &ind;
	
	
	int *pos;
	int npos = 0;
	pos = &npos;
	int v[200];
	
	char str[400];
	/*scanf("%s %s",str1,str2);
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int i=0;
	strcpy(str,str1);
	for(i=len1;i<len1+len2+1;i++){
		str[i] = str2[i-len1];
	}*/
	
	//printf("\n=%s=\n",str);
	scanf("%[^\n]s", str);
	insereEsq(&r,str,p);
	
	EPD(r,v,pos);
	
	int j;
	for(j=0;j<*pos;j++){
		printf("\n%d", v[j-1]);
		if(v[j] < v[j-1]){
			printf("FALSO");
			break;
		}
	}
	if(j == *pos) printf("VERDADEIRO");
		
	return 0;
}
