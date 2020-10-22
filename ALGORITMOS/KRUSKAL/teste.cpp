#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include "grafos.h"

using namespace std;

// inserção dos pesos -> ler_grafo()
void inicializar (grafo *g, int tamanho) {
	int i,j;
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->matriz = (int **) malloc(sizeof(int) * tamanho);

	for(i =0; i < tamanho; i++){
		g->matriz[i] = (int *) malloc(sizeof(int) * tamanho);
	}
}


void ler_grafo(char * nome, grafo *g){
	FILE *arq;
	arq = fopen(nome, "rb");
	
	int arestas;
	
	size_t len = 25; 
  char *linha = (char*)malloc(len);
	char delim[] = " ";
  
  getline(&linha, &len, arq);
  	
  char *ptr = strtok(linha, delim);
  g -> v = atoi(ptr);
  ptr = strtok(NULL, delim);
  arestas = atoi(ptr);
  
  for(int i = 0; i < g -> v; i++){
  	getline(&linha, &len, arq);
  	strcpy(&g -> mapa[i], linha);
  }
  
  for(int x = 0; x < arestas; x++){
  	int i, j, peso;
  	getline(&linha, &len, arq);
  	
 		i = buscar_vertice(linha[0], g -> mapa);
 		j = buscar_vertice(linha[1], g -> mapa);
 		
 		peso = atoi(&linha[2]);
 		

 		
 		if(i != 0 && j != 0){
 			g -> matriz[i - 1][j - 1] = peso;
 			g -> matriz[j - 1][i - 1] = peso;
 		}
 		
  }

	free(linha);
}

/*
Já que o retorno 0 poderia occorer tanto se a posição do array fosse igual
a 0 quanto se o char não existisse no array, a função retorna i+1 para que 
o valor 0 seja exclusivamente para casos em que o char procurado não se 
encontrem no array
*/
int buscar_vertice(char letra, char * array){
	for(int i = 0; i < strlen(array); i++){
		char a = array[i];
		
		if(a == letra){
			return i + 1;
		}
	}
	
	return 0;
}


void imprimir(grafo *g) {
		int i,j;

		for(i =0; i < g->v; i++) {
				
				for(j = 0; j < g->v; j++) {
						printf("\t%d", g->matriz[i][j]);
				}					
				printf("\n");
		}
}


int buscar_conjunto(int * antecessores, int i){
	if(antecessores[i] == i){
		return i;
	}
	
	return buscar_conjunto(antecessores, antecessores[i]);
	
}

int contido_arv(int * arvore, int i){
	int cont = 0;
	
	while(arvore[cont] != NULL){
		
	}
	
}

void kruskal(grafo * g){
	int * antecessores = (int *)malloc(sizeof(int) * g -> v);
	int * arv_min = (int *)malloc(sizeof(int) * g -> v);
	
	vector<int>pesos;
	
	for(int i = 0; i < g -> v; i++){
		antecessores[i] = i;
		arv_min[i] = -1;
	}
	

	for(int i = 0; i < g -> v; i++){
		for(int j = i; j < g -> v; j++){
			if(g -> matriz[i][j] != 0){
				pesos.push_back(g-> matriz[i][j]);
				
			}
		}
	}	
	
	sort(pesos.begin(), pesos.end());
	
	int t = 0;
	
	while(pesos[t] != NULL){
		printf("[%d] ", pesos[t]);
		t++;
	}
	
	int soma_pesos = 0;
	
	int cont = 0;
	int cont_arv = 0;
	


	for(int cont = 0; cont < pesos.size(); cont++){
		int achou = 0;
		// printf("\n entrou no peso %d\n", pesos[cont]);
		
		while(!achou){
			for(int i = 0; i < g -> v; i++){
				for(int j = i; j < g -> v; j++){
					if(g -> matriz[i][j] == pesos[cont]){
						achou = 1;
						
						if(buscar_conjunto(antecessores, antecessores[i]) != buscar_conjunto(antecessores, antecessores[j])){	
							printf("\nENTROU: %d\n%d e %d\n", pesos[cont], i, j);
							
																	
							if(arv_min[i] == -1){
								arv_min[i] = j;
							} else {
								arv_min[j] = i;
							}
							
							soma_pesos += pesos[cont];
							
							antecessores[buscar_conjunto(antecessores, i)] = buscar_conjunto(antecessores, j);
						}			
					}
				}
			}
		}	
		
	printf("ANTECESSORES:\n");
	for(int i = 0; i < g -> v; i++){
		printf("%d: [%d] ", i, arv_min[i]);
		printf("\n");
	}

	printf("\nA SOMA DOS PESOS É: %d\n", soma_pesos);
	
}	
		
		// mudar isso
	for(int i = 0; i < g -> v; i++){
		printf("%d: [%d] ", i, arv_min[i]);
		printf("\n");
	}
	
	/*
	int contador = 0;
	
	while(pesos[contador] != NULL){
		printf(": %d ", pesos[contador]);
		contador++;
	}
	
	printf("\n");
	*/
	
	// mudar isso
	/*
	for(int i = 0; i < g -> v; i++){
		printf("%d: [%d] ", i, arv_min[i]);
		printf("\n");
	}
	*/
	
	//	printf("A SOMA DOS PESOS É: %d\n", soma_pesos);
	
}	
	



int main(int argc, int* argv) {
	grafo g;

	inicializar(&g, 4);
	int * antecessores = (int *) malloc(sizeof(int) * 4);
	antecessores[0] = 0;
	antecessores[1] = 0; 
	antecessores[2] = 1;

	// imprimir(&g);
	
	ler_grafo("grafo.txt", &g);
	
	//printf("\n \n");
	
	//imprimir(&g);
	
	kruskal(&g);
	
	//printf("%d\n", mesmo_grupo(antecessores, 0, 2));
	
}
