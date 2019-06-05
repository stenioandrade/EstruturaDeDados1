#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	char codigo[17];
	int aposta[15];
	int acerto;
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

void heap_max (node *v, int t, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < t && v[e].acerto > v[p].acerto) p = e;
		if (d < t && v[d].acerto > v[p].acerto) p = d;
		if (p != i){
			troca(v,p,i);
			heap_max(v,t,p);
		}
}

void heap_min (node *v, int t, int i){
	unsigned int p = i;
	unsigned int e = esquerda(i);
	unsigned int d = direita(i);
		if (e < t && v[e].acerto < v[p].acerto) p = e;
		if (d < t && v[d].acerto < v[p].acerto) p = d;
		if (p != i){
			troca(v,p,i);
			heap_max(v,t,p);
		}
}
//mini funcao q conta qnts apostadores acertaram igualmente o maxacerto (nao conta com o primeiro)
int cont_vencedores(node *v, int napostas){
	int i, cont = 0; 
		for(i=0;i<napostas;i++){
			if(v[0].acerto != v[2*i+1].acerto && v[0].acerto != v[2*i+2].acerto)
				i = napostas + 1;
			else{
				if(v[0].acerto == v[2*i+1].acerto) cont++;
				if(v[0].acerto == v[2*i+2].acerto) cont++;
			}
		}
		return cont;
}
// funcao que preenche um vetor passado como argumento com as pessoas que tvrm a msm qntd de acertos
void preenche_vetor_win(node *v, node *vwin, int c){
	int cont = c, i = 0, j = 1;
		vwin[0] = v[0];
		while (cont){
			if(v[0].acerto != v[2*i+1].acerto && v[0].acerto != v[2*i+2].acerto)
				cont = 0;
			else{
				if(v[0].acerto == v[2*i+1].acerto){
					vwin[j] = v[2*i+1];
					j++;
					cont--;
				}
				if(v[0].acerto == v[2*i+2].acerto){
					vwin[j] = v[2*i+2];
					j++;
					cont--;
				}
			}
			i++;
		}
}

int main(int argc, char* argv[]){
	FILE* input = fopen("testes.txt","r");
	FILE* output = fopen("output_1.txt","w");
	int premio,napostas,sorteado[10],i,j,h,l;
	char str[17]={0};
	fscanf(input,"%d %d",&premio,&napostas);
	int tn = (napostas-1)/2;
	for (i=0;i<10;i++){
		fscanf(input,"%d",&sorteado[i]);
	}
	node *v = (node*)malloc(napostas*sizeof(node));
		for(i=0;i<napostas;i++){
			fscanf(input,"%s\n",str);
			strcpy(v[i].codigo,str);
			v[i].acerto = 0;
			for(j=0;j<15;j++){
				fscanf(input,"%d",&v[i].aposta[j]);
					for(h=0;h<10;h++){
						if(sorteado[h] == v[i].aposta[j]){
							v[i].acerto++;
							break;
						}
					}
			}
		}
	int contmax,contmin;
	
	for(l=tn;l>=0;l--) heap_max(v,napostas,l);                          // aplica o heap max
	contmax = cont_vencedores(v,napostas)+1;                            // cont recebe o numero total de pessoas q acertaram o max
	node *winmax = (node*)malloc(contmax*sizeof(node));                 // cria vetor q guarda os vencedores de max
	preenche_vetor_win(v,winmax,contmax);                               // funçao q preenche o vetor com os ganhadores de msm qntd de acertos max
	
	for(l=tn;l>=0;l--) heap_min(v,napostas,l);                          // aplica heap min
	contmin = cont_vencedores(v,napostas)+1;							// cont recebe o numero total de pessoas q acertaram o min
	node *winmin = (node*)malloc(contmin*sizeof(node));                 // cria vetor q guarda os vencedores de min
	preenche_vetor_win(v,winmin,contmin);                               // funçao q preenche o vetor com os ganhadores de msm qntd de acertos min
	
	int pmax = (premio/2)/contmax;                                      // divisao de preios
	int pmin = (premio/2)/contmin;
	
	//abaixo esta toda a impressao do arquivo
	
	if(winmax[0].acerto > 1) fprintf(output,"Faixa: %d acertos\n",winmax[0].acerto);
	else fprintf(output,"Faixa: 1 acerto\n");
	for(i=0;i<contmax;i++) fprintf(output,"%s\n",winmax[i].codigo);
	if(contmax > 1) fprintf(output,"%d ganhadores de R$%d\n\n",contmax,pmax);
	else fprintf(output,"1 ganhador de R$%d\n\n",pmax);
	
	if(winmin[0].acerto > 1) fprintf(output,"Faixa: %d acertos\n",winmin[0].acerto);
	else fprintf(output,"Faixa: 1 acerto\n");
	for(i=0;i<contmin;i++) fprintf(output,"%s\n",winmin[i].codigo);
	if(contmin > 1) fprintf(output,"%d ganhadores de R$%d\n",contmin,pmin);
	else fprintf(output,"1 ganhador de R$%d\n",pmin);
	
	return 0;
}
