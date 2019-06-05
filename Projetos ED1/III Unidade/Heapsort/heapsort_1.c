#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int ctrl = 0, ord = 0;
typedef struct Node{
	int key;
	int tam;
	int byt[1024];
}node;

int esquerda(int i){
	return 2*i+1;
}

int direita(int i){
	return 2*i+2;
}

void troca (node *v, int p, int i){
	node aux = v[i];
	v[i] = v[p];
	v[p] = aux;
}
void construir(node *v, int n){
	int i;
	for(i=((n-2)/2);i>=0;i--){
		heap(v,n,i);
	}
}

void heap (node *v, int n, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < n && v[e].key < v[p].key) p = e;
		if (d < n && v[d].key < v[p].key) p = d;
		if (p != i){
			troca(v,p,i);
			heap(v,n,p);
		}
}

void sort (node *v, int n){
	construir(v,n);
	int i;
	for(i=n-1;i<0;i--){
		troca(v,0,i);
		heap(v,i,0);
	}
}

node remover(node *v, int *n){
	node root = v[0];
	v[0] = v[(*n)-1];
	*n = (*n)-1;
	return root;
}

void print(){}

void imprime(node *v, int n){
	int i=0,j=0,k=1;
		if(v[0].key == ctrl){
			fprintf(output,"[%d]",ord);
			ord++;
			while(v[i].key == ctrl){
				ctrl++;
				for(j=0;j<v[0].tam;j++){
					fprintf(output," %X",v[i].byt[j]);
				}
				i++;
			}
		}
}

int main(int argc, char* argv[]){
	FILE* input = fopen("input.txt","r");
	FILE* output = fopen("Myoutput.txt","w");
	int np, qp, i, j;
	
	fscanf(input,"%d %d",&np,&qp);
		
	node* v = (node*)malloc(np*sizeof(node));
	//node* out = (node*)malloc(np*sizeof(node));
	
	for(i=0;i<np;i++){
		for(j=0;j<2;j++){
			fscanf(input,"%d %d%*c",&v[i].key,&v[i].tam);
				for(j=0;j<v[i].tam;j++){
					fscanf(input," %X",&v[i].byt[j]);
				}
		}
		if(v[0].key == ctrl){
			
		}
	}
	
	
	
	
	
				/*if(v[i].byt[j] < 0x10) fprintf(output," 0%X",v[i].byt[j]);
				else fprintf(output," %X",v[i].byt[j]);*/
		
	return 0;
}
