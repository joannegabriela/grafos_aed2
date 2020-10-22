#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo {
	int v;
	char *mapa;
	int **matriz;
} grafo;

typedef struct elemento {
	char vertice;
	struct elemento * prox;
} Elemento;

typedef struct fila {
	Elemento * primeiro;
} Fila;




void inicializar (grafo *g, int tamanho);
void imprimir(grafo *g);
void adicionarAresta(grafo *g, char v1, char v2);
int buscar_vertice(char letra, char * array);


#endif
