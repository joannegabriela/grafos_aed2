#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"


void inicializar (grafo *g, int tamanho) {
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->adjacencias = (Lista *) malloc(sizeof(Lista) * tamanho);
	
	for(int i = 0; i < tamanho; i++){
		g -> adjacencias[i].primeiro = NULL;
	}
}

no * inicializa_adjacencia(int ver){
	no * adj = (no *) malloc(sizeof(no));
	adj -> indice_adj = ver;
	adj -> peso = 0;
	adj -> prox = NULL;
	
	return adj;
}

void inserir_adjacencia(grafo * g, int indice_vertice, int ver_adj, int p){
	no * novo = inicializa_adjacencia(ver_adj);
	
	novo -> prox = g -> adjacencias[indice_vertice].primeiro;
	novo -> peso = p;
	g -> adjacencias[indice_vertice].primeiro = novo;
}


void ler_grafo(char * nome, grafo * g){
	FILE * arq;
	arq = fopen(nome, "rb");
	
	int arestas;
	
	size_t len = 25; 
  char *linha = malloc(len);
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
 		
		
 		inserir_adjacencia(g, (i - 1), (j - 1), peso);
 		inserir_adjacencia(g, (j - 1), (i - 1), peso);
 		
  }
	free(linha);
	
	
}
	

/* Já que o retorno 0 poderia occorer tanto se a posição do array fosse igual
a 0 quanto se o char não existisse no array, a função retorna i+1 para que 
o valor 0 seja exclusivamente para casos em que o char procurado não se 
encontrem no array */
int buscar_vertice(char letra, char * array){
	for(int i = 0; i < strlen(array); i++){
		char a = array[i];
		
		if(a == letra){
			return i + 1;
		}
	}
	
	return 0;
}

void print_mapa(grafo * g){
  for(int i = 0; i < g -> v; i++){
  	printf("[%c - %d] ", g -> mapa[i], i);
  }
  
  printf("\n");
}

void print_adjacencias(grafo * g){
	for(int i = 0; i < g -> v; i++){
		printf("ADJACENCIAS DE %d: ", i);
		no * adjacencia = g -> adjacencias[i].primeiro;
		
		while(adjacencia){
			printf("(%d)[%d] ", adjacencia -> peso, adjacencia -> indice_adj);
			adjacencia = adjacencia -> prox;
		}
		printf("\n");
	}
}


int obter_aresta_minima(grafo * g, int vertice){
	no * adj = g -> adjacencias[vertice].primeiro;
	no * adj_min = adj;

	while(adj){
		if(adj -> peso < adj_min -> peso){
			adj_min = adj;
		}
		
		adj = adj -> prox;
		
	}
	
	return adj_min -> indice_adj;

}


int obter_peso(grafo * g, int vertice1, int vertice2){
	no * adj = g -> adjacencias[vertice1].primeiro;
	// int peso_minimo = adj -> peso;

	while(adj){
		if(adj -> indice_adj == vertice2){
			return adj -> peso;
		}
		
		adj = adj -> prox;
		
	}
}

int obter_prox_aresta_minima(grafo * g, int vertice, int min){
	no * adj = g -> adjacencias[vertice].primeiro;
	no * adj_min;
	
	if(adj -> peso != min){
		adj_min = adj;
	} else {
		adj_min = adj -> prox;
	}


	while(adj){
		if(adj -> peso < adj_min -> peso && adj -> peso != min){
			adj_min = adj;
		}
		
		adj = adj -> prox;
		
	}
	// mudar aqui
	return adj_min -> peso;

}


void prim(grafo * g, int origem){
	int * antecessores = (int *) malloc(sizeof(int) * g -> v);
	int soma_pesos = 0;
		
	for(int i = 0; i < g -> v; i++){
		antecessores[i] = -1;
	}
	
	antecessores[origem] = origem;
	

	for(int i = 0; i < g -> v - 1; i++){
		printf("ORIGEM: %d\n", origem);
		no * adj = g -> adjacencias[origem].primeiro;
		int peso_min = g -> adjacencias[origem].primeiro -> peso;
		
		no * adj_prox = adj;
				
		while(adj){
			if(adj -> peso < peso_min && antecessores[adj -> indice_adj] == -1){
				printf("ENTROU: %d\n\n", adj -> indice_adj);
				peso_min = adj -> peso;
				adj_prox = adj; 
			}	
			
			adj = adj -> prox;
			
		}		
		
		antecessores[adj_prox  -> indice_adj] = origem;
		soma_pesos += adj_prox -> peso;
		origem = adj_prox -> indice_adj;

		
	}
	
	printf("ANTECESSORES: \n");
	for(int i = 0; i < g -> v; i++){
		printf("%d: [%d]\n", i, antecessores[i]);
	}
	
	printf("\n");
	
	
	printf("SOMA DOS PESOS: %d\n", soma_pesos);
}



int main(int argc, int* argv) {
	grafo g;
	
	inicializar(&g, 4);
	
	ler_grafo("grafo.txt", &g);
	
	//buscar_grafo_profundidade(&g);
	
	print_adjacencias(&g);
	
	// printf("\n");
	
	//printf("%d\n", obter_aresta_minima1(&g, 0));
	
	prim(&g, 0);
	
	//printf("%d\n", obter_prox_aresta_minima(&g, 0, 2));
	

}
