#ifndef GRAFO_H
#define GRAFO_H

typedef struct no {
	int peso;
	int indice_adj;
	struct no * prox;
} no;

typedef struct lista{
	no * primeiro;
} Lista;

typedef struct grafo {
	int v;
	char * mapa;
	Lista * adjacencias;
} grafo;


void inicializar (grafo *g, int tamanho);
void imprimir(grafo *g);
void adicionarAresta(grafo *g, char v1, char v2);
int buscar_vertice(char letra, char * array);

void print_adjacencias(grafo * g);

// void visita_vertice(grafo * g, int indice_vertice);


#endif
