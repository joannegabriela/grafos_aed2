#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

Fila * inicializar_fila(){
	Fila * fila = malloc(sizeof(fila));
	return fila;
}

// tentar tornar uma função recursiva 
void inserir_fila(Fila * fila, char ver){
	if(fila -> primeiro == NULL){
		Elemento * elemento = malloc(sizeof(Elemento));
		elemento -> prox = NULL;
		elemento -> vertice = ver;
		
		fila -> primeiro = elemento;
	} else {
		Elemento * elem = fila -> primeiro;
		
		while(elem -> prox != NULL){
			elem = elem -> prox;
		}
		elem -> prox = malloc(sizeof(Elemento));
		elem -> prox -> vertice = ver;
	
	}
}

// função apenas para teste
void print_fila(Fila * fila){
	Elemento * elem = fila -> primeiro;

	while(elem != NULL){
		printf("[%c] ", elem -> vertice);
		elem = elem -> prox; 
	}
	
	printf("\n");
}
		

void remover_fila(Fila * fila){
	if(fila -> primeiro -> prox != NULL){
		fila -> primeiro = fila -> primeiro -> prox;
	} else {
		fila -> primeiro = NULL;
	}
}

void inicializar (grafo *g, int tamanho) {
	int i,j;
	g->v = tamanho;
	g->mapa = (char *) malloc(sizeof(char) * tamanho);
	g->matriz = (int **) malloc(sizeof(int) * tamanho);

	for(i =0; i < tamanho; i++)
		g->matriz[i] = (int *) malloc(sizeof(int) * tamanho);

	for(i =0; i < tamanho; i++) {
		for(j=0; j < tamanho; j++) {
				if(i==j) {
					g->matriz[i][j] = 1;
				} else {
					g->matriz[i][j] = 0;
				}
		}
	}
}


void ler_grafo(char * nome, grafo *g){
	FILE *arq;
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
 		
 		if(i != 0 && j != 0){
 			g -> matriz[i - 1][j - 1] = 1;
 			g -> matriz[j - 1][i - 1] = 1;
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


void buscar_grafo_largura(grafo * g, char vertice){
	
	int * cores = malloc(sizeof(int) * g -> v);
	int * distancias = malloc(sizeof(int) * g -> v);;
	char * antecessores  = malloc(sizeof(char) * g -> v);
	
	for(int i = 0; i < g -> v; i++){
		if(vertice == g -> mapa[i]){
			cores[i] = 1; // preto
		} else {
			cores[i] = 0; // branco 
		}
		
		distancias[i] = 0;
		// strcpy(&antecessores[i], "");
	}

	
	Fila * fila = inicializar_fila();
	inserir_fila(fila, vertice);
	
	while(fila -> primeiro != NULL){
		char u = fila -> primeiro -> vertice;
		int posicao_u = buscar_vertice(u, g -> mapa) - 1;
		
		remover_fila(fila);
		
		for(int i = 0; i < g -> v; i++){
			if(g -> matriz[posicao_u][i] == 1 
			|| g -> matriz[i][posicao_u] == 1){ // se existe uma aresta 
				if(cores[i] == 0){ 
					cores[i] = -1; // cinza
					distancias[i] = distancias[posicao_u] + 1;
					strcpy(&antecessores[i], &u);
					inserir_fila(fila, g->mapa[i]);	
				} 
				cores[i] = 1;
			}
		}	
	}
	
	printf("CORES: ");
	for(int i = 0; i < g -> v; i++){
		printf("[%d] ", cores[i]);
	}
	
	printf("\n");
	printf("DISTANCIAS: ");
	for(int i = 0; i < g -> v; i++){
		printf("[%d] ", distancias[i]);
	}
	
	printf("\n");
	printf("ANTECESSORES: ");
	for(int i = 0; i < g -> v; i++){
		printf("[%c] ", antecessores[i]);
	}
	
	printf("\n");
	
	free(fila);
	free(cores);
	free(distancias);
	free(antecessores);
	
}


int main(int argc, int* argv) {
	grafo g;

	inicializar(&g, 4);

	imprimir(&g);
	
	ler_grafo("grafos.txt", &g);
	
	printf("\n \n");
	
	imprimir(&g);
	
	buscar_grafo_largura(&g, 'A');
	
	printf("\n");
	for(int i = 0; i < g.v; i++){
		printf("[%c] ", g.mapa[i]);
	}
	
	printf("\n");
	
	
	

}
