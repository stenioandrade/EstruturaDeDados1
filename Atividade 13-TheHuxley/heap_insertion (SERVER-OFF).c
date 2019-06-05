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
			heap_min(v,t,p);
		}
}


node remover(node *v, int *t){
	node root = v[0];
	v[0] = v[(*t)-1];
	*t = (*t)-1;
	return root;
}

void inserir(){
	
}

int main(){
	int napostas,sorteado[10],i,j,h;
	char str[17]={0};
	int tn = (napostas-1)/2;
	for (i=0;i<10;i++){
		scanf("%d",&sorteado[i]);
	}
	scanf("%d",&napostas);
	node *vheapmax = (node*)malloc(napostas*sizeof(node)); // onde aplica o heap max
	node *vheapmin = (node*)malloc(napostas*sizeof(node)); // onde aplica o heap min
	node *vmax = (node*)malloc(napostas*sizeof(node));     // onde guarda os ganhadores de max acertos
	node *vmin = (node*)malloc(napostas*sizeof(node));     // onde guarda os ganhadores de min acertos
		for(i=0;i<napostas;i++){
			scanf("%s ",str);
			strcpy(vheapmax[i].codigo,str);
			strcpy(vheapmin[i].codigo,str);
			vheapmax[i].acerto = 0;
			vheapmin[i].acerto = 0;
			for(j=0;j<15;j++){
				scanf("%d",&vheapmax[i].aposta[j]);
				vheapmin[i].aposta[j] = vheapmax[i].aposta[j];
					for(h=0;h<10;h++){
						if(sorteado[h] == vheapmax[i].aposta[j]){
							vheapmax[i].acerto++;
							vheapmin[i].acerto++;
							h = 10;
						}
					}
			}
		}	
//  auxiliares para aplicar remoção e não decrementar o napostas que será usado 2 vezes 
	int t_max = napostas;
	int t_min = napostas;		
		
//	heap_max
	for(i=tn;i>=0;i--) heap_max(vheapmax,t_max,i);
	i = 0;
	node temp;
	node referencia_acerto = vheapmax[0];
	int ctrl = 1;
	while(ctrl){
		temp = remover(vheapmax,&t_max);
		heap_max(vheapmax,t_max,0);
		if(referencia_acerto.acerto != temp.acerto){
			ctrl = 0;
		}else {
			vmax[i] = temp;
			i++;
		}
	}
//	imprime_max	
	if(vmax[0].acerto > 1) printf("Faixa: %d acertos\n",vmax[0].acerto);
	else printf("Faixa: %d acerto\n",vmax[0].acerto);
	for(j=0;j<i;j++) printf("%s\n",vmax[j].codigo);
	if(i > 1) printf("%d ganhadores\n\n",i);
	else printf("1 ganhador\n\n");
	
//	heap_min
	for(i=tn;i>=0;i--) heap_min(vheapmin,t_min,i);
	i = 0;
	node temp2;
	node referencia_acerto2 = vheapmin[0];
	ctrl =  1;
	while(ctrl){
		temp2 = remover(vheapmin,&t_min);
		heap_min(vheapmin,t_min,0);
		if(referencia_acerto2.acerto != temp2.acerto){
			ctrl = 0;
		}else {
			vmin[i] = temp2;
			i++;
		}
	}
	
//	imprime_min	
	if(vmin[0].acerto > 1) printf("Faixa: %d acertos\n",vmin[0].acerto);
	else printf("Faixa: %d acerto\n",vmin[0].acerto);
	for(j=0;j<i;j++) printf("%s\n",vmin[j].codigo);
	if(i > 1) printf("%d ganhadores",i);
	else printf("1 ganhador");
	
	
	
	return 0;
}
