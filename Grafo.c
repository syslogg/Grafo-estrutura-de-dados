#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
typedef struct no No;

struct grafo {
	No * inicial;
};
struct no {
	int key;
	No * prox;
	No * vizinhos;
};


Grafo * criar(){
	Grafo * g = (Grafo *) malloc(sizeof(Grafo));
	
	g->inicial = NULL;
	
	
	return g;
	
	
}

void IncluirVertice(Grafo * g, int key) {
	
	if(g->inicial == NULL) {
		No * no = (No *) malloc(sizeof(sizeof(No)));
		no->key = key;
		no->prox = NULL;
		g->inicial = no;
	} else {
		No * node = g->inicial;
		No * ant = NULL;
		while(node != NULL) {
			//Já existente
			if(node->key == key) return;
			ant = node;
			node = node->prox;
		}
		//Criar o no
		No * no = (No *) malloc(sizeof(sizeof(No)));
		no->key = key;
		no->prox = NULL;
		ant->prox = no;
	}	
}

void IncluirAresta(Grafo * g, int key) {
	
}

void Imprimir(Grafo * g){
	printf("[ ");
	
	if(g->inicial != NULL) {
		No * node = g->inicial;
		
		while (node != NULL) {
			printf("%d ",node->key);
			node = node->prox;
		}
		
	}
	
	printf("]\n");
	
}
