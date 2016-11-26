#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
typedef struct no No;
typedef struct aresta Aresta;
typedef struct vertice Vertice;

Vertice * BuscarVertice (Grafo * g, int key);

struct grafo {
	No * inicial;
};
struct vertice {
	int key;
	Vertice * prox;
	Aresta * primeiroVizinho;
	int peso;
};

struct aresta {
	Aresta * prox;
	Vertice * vert;
	int peso;
	int id;
};





Grafo * criar(){
	Grafo * g = (Grafo *) malloc(sizeof(Grafo));
	g->inicial = NULL;
	g->peso = -1;
	return g;
}

void IncluirVertice(Grafo * g, int key) {
	
	if(g->inicial == NULL) {
		Vertice * v = (Vertice *) malloc(sizeof(Vertice));
		v->key = key;
		v->prox = NULL;
		v->primeiroVizinho = NULL;
		g->inicial = v;
		
		
	} else {
		Vertice * ant = g->inicial;
		
		if(ExisteVertice(g,key) == 1) {
			printf("\nERROR: Ja contem vertice com chave '%c'.\n",key);
			return;	
		} 
		
		//Percorre até chegar no final
		while(ant->prox != NULL) {
			ant = ant->prox;
		}
		
		Vertice * n = (Vertice *) malloc(sizeof(Vertice));
		n->key = key;
		n->prox = NULL;
		n->primeiroVizinho = NULL;
		
		ant->prox = n;
	}
		
}

void IncluirAresta(Grafo * g, int vertice1, int vertice2, int peso, int id) {
	
	//Verifica se existe o vertice e a aresta
	if(ExisteVertice(g,vertice1) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice1);
		return;
	}
	if(ExisteVertice(g,vertice2) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice2);
		return;
	}
	if(ExisteAresta(g,vertice1,vertice2) == 1) {
		printf("\nWARNING: Ja contem arestas entre '%c' e '%c'.\n",vertice1,vertice2);
		return;
	}
	
	Vertice * vert1 = BuscarVertice(g,vertice1);
	Vertice * vert2 = BuscarVertice(g,vertice2);
	
	
	
	//Vertice 1
	if(vert1->primeiroVizinho == NULL) {
		Aresta * a = (Aresta *) malloc(sizeof(Aresta));
		a->peso = peso;
		a->prox = NULL;
		a->vert = vert2;
		a->id = id;
		vert1->primeiroVizinho = a;
	} else {
		Aresta * ant = vert1->primeiroVizinho;
		
		while (ant->prox != NULL) {
			ant = ant->prox;
		}
		
		Aresta * a = (Aresta *) malloc(sizeof(Aresta));
		a->peso = peso;
		a->prox = NULL;
		a->vert = vert2;
		a->id = id;
		ant->prox = a;
		
	}
	
	if(vertice1 != vertice2) {
	
		//Vertice 2
		if(vert2->primeiroVizinho == NULL) {
			Aresta * a = (Aresta *) malloc(sizeof(Aresta));
			a->peso = peso;
			a->prox = NULL;
			a->vert = vert1;
			a->id = id;
			vert2->primeiroVizinho = a;
		} else {
			Aresta * ant = vert2->primeiroVizinho;
			
			while (ant->prox != NULL) {
				ant = ant->prox;
			}
			
			Aresta * a = (Aresta *) malloc(sizeof(Aresta));
			a->peso = peso;
			a->prox = NULL;
			a->vert = vert1;
			a->id = id;
			ant->prox = a;
			
		}
	}
	
	
	
}

void DeletarAresta(Grafo * g, int vertice1, int vertice2) {
	if(ExisteVertice(g,vertice1) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice1);
		return;
	}
	if(ExisteVertice(g,vertice2) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice2);
		return;
	}
	if(ExisteAresta(g,vertice1,vertice2) == 0) {
		printf("\ERROR: Nao existe arestas entre '%c' e '%c'.\n",vertice1,vertice2);
		return;
	}
	
	Vertice * vert1 = BuscarVertice(g,vertice1);
	Vertice * vert2 = BuscarVertice(g,vertice2);
	
	Aresta * aresta1 = vert1->primeiroVizinho;
	Aresta * aresta2 = vert2->primeiroVizinho;
	
	Aresta * aux1 = NULL;
	Aresta * aux2 = NULL;
	
	
	//Aresta 1
	while(aresta1->prox != NULL) {
		if(aresta1->vert->key == vertice2) {
			//Deletar da lista
			if(aux1 != NULL) {
				aux1->prox = aresta1->prox;
			} else {
				vert1->primeiroVizinho = aresta1->prox;
			}
			free(aresta1);
			break;
		}
		
		aux1 = aresta1;
		aresta1 = aresta1->prox;
	}
	
	//Aresta 2
	while(aresta2->prox != NULL) {
		if(aresta2->vert->key == vertice1) {
			//Deletar da lista
			if(aux2 != NULL) {
				aux2->prox = aresta2->prox;
			} else {
				vert2->primeiroVizinho = aresta2->prox;
			}
			free(aresta2);
			break;
		}
		
		aux2 = aresta2;
		aresta2 = aresta2->prox;
	}
	

	
}

void DeletarVertice(Grafo * g, int vertice) {
	
	if(ExisteVertice(g,vertice) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice);
		return;
	}
	
	//Retira todas as arestas daquele vertice
	Vertice * auxVertice = NULL;
	Vertice * vert = BuscarVertice(g,vertice);
	
	auxVertice = g->inicial;
	
	while(auxVertice->prox != NULL) {
		
		Aresta * auxAresta = NULL;
		Aresta * auxAresta2 = NULL;
		
		
		auxAresta = auxVertice->primeiroVizinho;
		
		while(auxAresta->prox != NULL) {
			
			if(auxAresta->vert->key == vertice) {
				if(auxAresta2 != NULL) {
					auxAresta2->prox = auxAresta->prox;
				} else {
					auxVertice->primeiroVizinho = auxAresta->prox;
				}
				free(auxAresta);
				break;
			}
			auxAresta2 = auxAresta;
			auxAresta = auxAresta->prox;
		}
		auxVertice = auxVertice->prox;
	}
	
	
	
	//Matar a lista do vertice
	Aresta * auxAresta = vert->primeiroVizinho;
	Aresta * aux2 = NULL;
	
	
	while(auxAresta != NULL) {
		aux2 = auxAresta;
		auxAresta = auxAresta->prox;
		free(aux2);
	}
	
	vert->primeiroVizinho = NULL;
	
	
	//Mata o vertice
	auxVertice = g->inicial;
	Vertice * ant = NULL;
	
	while(auxVertice != NULL) {
		
		if(auxVertice->key == vert->key) {
			
			if(vert == g->inicial) {
				g->inicial = vert->prox;
			} else {
				ant->prox = auxVertice->prox;
			}
			free(auxVertice);
			break;
			
		}
		
		ant = auxVertice;
		auxVertice = auxVertice->prox;
	}
	
	
	
}

void CaminhoMinimo(Grafo * g, int vertice1, int vertice2) {
	
	
}

void TrocarChaveVertice(Grafo * g, int vertice, int novoVertice) {
	if(ExisteVertice(g,vertice) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice);
		return;
	}
	
	Vertice * vert = BuscarVertice(g, vertice);
	vert->key = novoVertice;
	
}

void TodosVizinhos(Grafo * g, int vertice) {
	
}

//Commands

void Imprimir(Grafo * g){
	Vertice * ant = g->inicial;
	
	
	while(ant != NULL) {
		printf("%c -> ",ant->key);
		
		Aresta * ant2 = ant->primeiroVizinho;
		printf("[ ");
		while(ant2 != NULL) {
			printf("%c%d ",ant2->vert->key, ant2->peso);
			ant2 = ant2->prox;
		}
		printf("];\n");
		ant = ant->prox;
	}
	
	printf("\n");
	
}

int ExisteVertice (Grafo * g, int key) {
	Vertice * ant = g->inicial;
	if(ant == NULL) return 0;
	while(ant != NULL) {
		if(ant->key == key) return 1;
		ant = ant->prox;
	}
	return 0;
}

int ExisteAresta(Grafo * g, int vertice1, int vertice2) {
	Vertice * vert1 = BuscarVertice(g,vertice1);
	
	Aresta * ant = vert1->primeiroVizinho;
	if(ant == NULL) return 0;
	
	while(ant != NULL) {
		if(ant->vert->key == vertice2) return 1;
		ant = ant->prox;
	}
	return 0;
	
}

Vertice * BuscarVertice (Grafo * g, int key) {
	if(ExisteVertice(g,key) == 0) return NULL;
	Vertice * ant = g->inicial;
	while(ant != NULL) {
		
		if(ant->key == key) {
			return ant;
		}
		ant = ant->prox;
	}
}













