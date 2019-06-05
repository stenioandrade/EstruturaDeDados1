#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
	char org[51];
	char nome[51];
	int old;
	int prf;
	int hor;
	int min;
	int seg;
}node;

typedef struct Orgao{
	char nome[51];
	int atd;
	int ind;
	int tam;
	int it;
}orgao;

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

void heap(node *v, int t, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < t && v[e].prf > v[p].prf) p = e;
		if (e < t && v[e].prf == v[p].prf){
			if(v[e].hor < v[p].hor) p = e;
			if(v[e].hor == v[p].hor){
				if(v[e].min < v[p].min) p = e;
				if(v[e].min == v[p].min){
					if(v[e].seg < v[p].seg) p = e;
				}
			}
		}
		if (d < t && v[d].prf > v[p].prf) p = d;
		if (d < t && v[d].prf == v[p].prf){
			if(v[d].hor < v[p].hor) p = d;
			if(v[d].hor == v[p].hor){
				if(v[d].min < v[p].min) p = d;
				if(v[d].min == v[p].min){
					if(v[d].seg < v[p].seg) p = d;
				}
			}
		}
		if (p != i){
			troca(v,p,i);
			heap(v,t,p);
		}
}

node remova(node *v, int *t){
	node root = v[0];
	v[0] = v[(*t)-1];
	*t = (*t)-1;
	return root;
}

int main(int argc, char* argv[]){
	FILE* input = fopen(argv[1],"r");
	FILE* output = fopen(argv[2],"w");
	int no, np, i, j, h, x, c;
	int *tam;
	char ch1, ch2;
	fscanf(input,"%d%*c",&no);
	orgao *o = (orgao*)malloc(no*sizeof(orgao));
	for(i=0;i<no;i++){
		o[i].nome[0] = '\0';
		fscanf(input,"%s %d%*c",o[i].nome,&o[i].atd);
		o[i].ind = i;
		o[i].tam = 0;
		o[i].it = 0;
	}
	fscanf(input,"%d%*c",&np);
	node *v = (node*)malloc(2*np*sizeof(node));
	node **m = (node**)malloc(2*no*sizeof(node*));
	for(i=0;i<no;i++) m[i] = (node*)malloc(2*np*sizeof(node));
	for(i=0;i<np;i++){
		h=0;
		while((ch1 = fgetc(input)) != ':'){
			v[i].org[h] = ch1;
			h++;
		}
		v[i].org[h] = '\0';
		j=0;
		while((ch2 = fgetc(input)) != '-'){
			v[i].nome[j] = ch2;
			j++;
		}
		v[i].nome[j] = '\0';
		fscanf(input,"%d%*c%d%*c%d%*c%d%*c",&v[i].old,&v[i].hor,&v[i].min,&v[i].seg);
		if(v[i].old >= 60) v[i].prf = 1;
		else v[i].prf = 0;
	}
	for(i=0;i<np;i++){
		for(x=0;x<no;x++){
			tam = &o[x].tam;
			if(strcmp(o[x].nome,v[i].org) == 0){
				m[x][*tam] = v[i];
				*tam = (*tam) + 1;
				break;
			}
		}
	}
	for(i=0;i<no;i++){
		c = (o[i].tam - 1)/2 ;
		for(j=c;j>=0;j--){
			heap(m[i],o[i].tam,j);
		}
	}
	int qtd;
	qtd = np;
	node temp;
	while(qtd){
		for(i=0;i<no;i++){
			if(o[i].tam > 0){
				fprintf(output,"[%s]",o[i].nome);
				for(j=0;j<o[i].atd;j++){
					temp = remova(m[i],&o[i].tam);
					heap(m[i],o[i].tam,0);
					fprintf(output," %s",temp.nome);
					qtd--;
					if(0 == o[i].tam) break;
					if( j == o[i].atd - 1) break;
					fprintf(output,",");
					if(qtd == 0) break;
				}
				if(qtd == 0) break;
				fprintf(output,"\n");
			}
		}
	}
	return 0;
}
