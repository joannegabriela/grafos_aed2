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
	adj -> prox = NULL;
	
	return adj;
}

void inserir_adjacencia(grafo * g, int indice_vertice, int ver_adj){
	no * novo = inicializa_adjacencia(ver_adj);
	
	novo -> prox = g -> adjacencias[indice_vertice].primeiro;
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
  	int i, j;
  	getline(&linha, &len, arq);
  	
 		i = buscar_vertice(linha[0], g -> mapa);
 		j = buscar_vertice(linha[1], g -> mapa);
		
 		inserir_adjacencia(g, (i - 1), (j - 1));
 		inserir_adjacencia(g, (j - 1), (i - 1));
 		
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
			printf("[%d] ", adjacencia -> indice_adj);
			adjacencia = adjacencia -> prox;
		}
		printf("\n");
	}
}


void visita_vertice(grafo * g, int indice_vertice, int * cores, char * antecessores, int * tempo){
	
	cores[indice_vertice] = -1; // cinza
	tempo[indice_vertice]++;
	
	no * lista = g -> adjacencias[indice_vertice].primeiro;
	
		if(lista != NULL) {
			no * aux = lista;

			while(aux){
				if(cores[aux -> indice_adj] == 0){
					antecessores[aux -> indice_adj] = g->mapa[indice_vertice];
					visita_vertice(g, aux -> indice_adj, cores, antecessores, tempo);	
				} else {
						// se o vértice já foi descoberto (se não é branco)
						aux = aux -> prox;
					}
			}
		}

	cores[indice_vertice] = 1; // preta
	tempo[indice_vertice]++;	
}

void buscar_grafo_profundidade(grafo * g){
	
	int * cores = malloc(sizeof(int) * g -> v);
	int * tempo = malloc(sizeof(int) * g -> v);
	char * antecessores = malloc(sizeof(char) * g -> v);
	
	for(int i = 0; i < g -> v; i++){
		cores[i] = 0; // branco
		tempo[i] = 0;
 		strcpy(&antecessores[i], "");
	}
	
	for(int i = 0; i < g -> v; i++){
		if(cores[i] == 0){ // branco
			visita_vertice(g, i, cores, antecessores, tempo);
		}
	}
	
	
	printf("ANTECESSORES:\n");
	for(int i = 0; i < g -> v; i++){
		if(strcmp(&antecessores[i], "") == 0){
			printf("(%d): O vértice não tem antecessores\n", i);
		} else {
		printf("(%d): [%c]\n", i, antecessores[i]);
		}
	}
}


int main(int argc, int* argv) {
	grafo g;
	
	inicializar(&g, 5);
	
	ler_grafo("grafos.txt", &g);
	
	buscar_grafo_profundidade(&g);
	
	//print_adjacencias(&g);

}
