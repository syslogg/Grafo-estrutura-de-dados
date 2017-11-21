#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "Grafo.h"

#define TAM_VERT_MAX 32
#define TAM_ARES_MAX 64

typedef struct no No;
typedef struct aresta Aresta;
typedef struct vertice Vertice;

Vertice * BuscarVertice (Grafo * g, int key);
Aresta * BuscarAresta (Grafo * g, int arestaId);

struct grafo {
	Vertice * inicial;
	int countVertice;
};
struct vertice {
	int key;
	Vertice * prox;
	int peso;
	Aresta * primeiroVizinho;
	Vertice * anterior;
	int countAresta;
};

struct aresta {
	Aresta * prox;
	Vertice * vert;
	int peso;
	int id;
};


int ExisteVertice (Grafo * g, int key);
int ExisteAresta(Grafo * g, int vertice1, int vertice2);
Vertice * BuscarVertice (Grafo * g, int key);


Grafo * criar(){
	Grafo * g = (Grafo *) malloc(sizeof(Grafo));
	g->inicial = NULL;
	g->countVertice = 0;
	return g;
}

void limpar(Grafo * g) {
	
	Vertice * vert = g->inicial;
	
	while (vert != NULL) {
		Aresta * ares = vert->primeiroVizinho;
		
		while(ares != NULL) {
			
			
			Aresta * r = ares;
			ares = ares->prox;
			free(r);
		}
		Vertice * v = vert;
		vert = vert->prox;
		free(v);
	}
	
	g->inicial = NULL;
}

void destruir(Grafo * g) {
	limpar(g);
	free(g);
}

void IncluirVertice(Grafo * g, int key) {
	
	if(g->inicial == NULL) {
		Vertice * v = (Vertice *) malloc(sizeof(Vertice));
		v->key = key;
		v->prox = NULL;
		v->primeiroVizinho = NULL;
		v->peso = -1;
		v->countAresta = 0;//parei aqui
		g->countVertice++;
		g->inicial = v;
	} else {
		Vertice * ant = g->inicial;
		
		if(ExisteVertice(g,key) == 1) {
			printf("\nERROR: Ja contem vertice com chave '%c'.\n",key);
			return;	
		} 
		
		//Percorre at� chegar no final
		while(ant->prox != NULL) {
			ant = ant->prox;
		}
		
		Vertice * n = (Vertice *) malloc(sizeof(Vertice));
		n->key = key;
		n->prox = NULL;
		n->primeiroVizinho = NULL;
		n->peso = -1;
		ant->prox = n;
		g->countVertice++;
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
		vert1->countAresta++;
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
		vert1->countAresta++;
		
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
			vert2->countAresta++;
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
			vert2->countAresta++;
			
		}
	}
	
	
	
}

int * Vizinhos(Grafo * g, int vertice){
	if(g != NULL) {
		Vertice * aux = g->inicial;
		int * arr = (int *) malloc(TAM_VERT_MAX*sizeof(int));
		int i = 0;
		while(aux != NULL) {
			arr[i++] = aux->key;
			aux = aux->prox;
		}
		return arr;
	}
	return NULL;
}


int * ArestaIdsPorVertice(Grafo * g, int vertice) {
	if(g != NULL){
		Vertice * vert =  BuscarVertice(g, vertice);
		if(vert != NULL) {
			Aresta * aux = vert->primeiroVizinho;
			int * arr = (int *) malloc(TAM_ARES_MAX*sizeof(int));
			int i = 0;
			while (aux != NULL) {
				arr[i++] = aux->id;
				aux = aux->prox;
			}
			return arr;
		} else {
			return NULL;
		}
	}
	return NULL;
}

int * ListaDeVertices(Grafo * g) {
	if (g != NULL) {
		Vertice * aux = g->inicial;
		int * arrVert = (int *) malloc(TAM_VERT_MAX * sizeof(int));
		int i = 0;
		while (aux != NULL){
			arrVert[i++] = aux->key;
			aux = aux->prox;
		}
		return arrVert;
	}
	return NULL;
}

int PesoDaAresta (Grafo * g, int arestaId){
	if(g != NULL) {
		Vertice * auxVert = g->inicial;
		
		while (auxVert != NULL){
			Aresta * auxAresta =  auxVert->primeiroVizinho;
			while (auxAresta != NULL) {
				if(arestaId == auxAresta->id){
					return auxAresta->peso;
				}
			}
			auxVert = auxVert->prox;
		}

	}
	return -1;
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
		printf("\nERROR: Nao existe arestas entre '%c' e '%c'.\n",vertice1,vertice2);
		return;
	}
	
	Vertice * vert1 = BuscarVertice(g,vertice1);
	Vertice * vert2 = BuscarVertice(g,vertice2);
	
	Aresta * aresta1 = vert1->primeiroVizinho;
	Aresta * aresta2 = vert2->primeiroVizinho;
	
	Aresta * aux1 = NULL;
	Aresta * aux2 = NULL;
	
	
	//Aresta 1
	while(aresta1 != NULL) {
		if(aresta1->vert->key == vertice2) {
			//Deletar da lista
			if(aux1 != NULL) {
				aux1->prox = aresta1->prox;
			} else {
				vert1->primeiroVizinho = aresta1->prox;
			}
			vert1->countAresta--;
			free(aresta1);
			break;
		}
		
		aux1 = aresta1;
		aresta1 = aresta1->prox;
	}
	
	//Aresta 2
	while(aresta2 != NULL) {
		if(aresta2->vert->key == vertice1) {
			//Deletar da lista
			if(aux2 != NULL) {
				aux2->prox = aresta2->prox;
			} else {
				vert2->primeiroVizinho = aresta2->prox;
			}
			vert2->countAresta--;
			free(aresta2);
			break;
		}
		
		aux2 = aresta2;
		aresta2 = aresta2->prox;
	}
	

	
}

void RetirarIncidenciaDaAresta(Grafo * g, Vertice * vertice) {
	if(g != NULL) {
		Vertice * aux = g->inicial;
		
		while(aux != NULL) {
			
			Aresta * aresAux = aux->primeiroVizinho;
			Aresta * aresAnt = NULL;
			while (aresAux != NULL) {
				Aresta * prox = aresAux->prox;
				if(vertice == aresAux->vert){
					if(aresAnt == NULL) {
						aux->primeiroVizinho = aresAux->prox;
					} else {
						aresAnt->prox = aresAux->prox;
					}
					aux->countAresta--;
					free(aresAux);
				}
				aresAnt = aresAux;
				aresAux = prox;
			}
			aux = aux->prox;
		}
		
	} 
}

int * ArestaOrdenadas(Grafo * g, int * retTam){
	if(g != NULL) {
		//Vertice * vert = BuscarVertice(g,verticeId);

		int countArestas = 0;
		int arestasContadas[TAM_ARES_MAX];
		Aresta * arestas[TAM_ARES_MAX];
		Vertice * vertAux = g->inicial;

		//Add arestas sem duplicaçao
		while (vertAux != NULL) {
			Aresta * arestaAux = vertAux->primeiroVizinho;
			while (arestaAux != NULL) {
				if(!BuscaEmArray(arestasContadas,arestaAux->id)){
					arestasContadas[countArestas] = arestaAux->id;
					arestas[countArestas++] = arestaAux;
				}
				arestaAux = arestaAux->prox;
			}
			vertAux = vertAux->prox;
		}
		int i,n;

		//Bubble sort
		for (i = 1; i < countArestas; i++){
			for (n = 0; n < i;n++){
				if(arestas[n]->peso > arestas[n+1]->peso) {
					Aresta * arestaAux = arestas[n];
					arestas[n] = arestas[n+1];
					arestas[n+1] = arestaAux;
				}
			}
		}

		int * idsOrdenados = (int *) malloc(countArestas * sizeof(int));
		for(i = 0; i < countArestas; i++){
			idsOrdenados[i] = arestas[i]->id;
		}
		*retTam = countArestas;
		return idsOrdenados;
	}
	return NULL;
}

void DeletarVertice(Grafo * g, int vertice) {
	
	if(ExisteVertice(g,vertice) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice);
		return;
	}
	
	Vertice * vert = BuscarVertice(g,vertice);
	
	Aresta * arestaAux = vert->primeiroVizinho;
	
	//Matar a lista de vertice 
	
	while(arestaAux != NULL) {
		Aresta * prox = arestaAux->prox;
		free(arestaAux);
		arestaAux = prox;
	}
	vert->primeiroVizinho = NULL;
	
	RetirarIncidenciaDaAresta(g,vert);
	
	
	Vertice * auxVert = g->inicial;
	Vertice * antVert = NULL;
	
	while (auxVert != NULL) {
		if(auxVert == vert) {
			if(antVert == NULL) {
				g->inicial = auxVert->prox;
			} else {
				antVert->prox = auxVert->prox;
			}
			free(auxVert);
			g->countVertice--;
			break;
		}
		antVert = auxVert;
		auxVert = auxVert->prox;
	}
	
	/*
	Vertice * vert2 = g->inicial;
	Vertice * anteriorVert = NULL;
	
	
	
	//Pegar o anterior do vertice
	while (vert2 != NULL) {
		anteriorVert = vert2;
		if(vert2 == vert) {
			
		}
		vert2 = vert2->prox;
	} 
	 
	 
	 
	//Matar o vertice
	//free(vert);*/
	
	/*
	//Retirar incidencia daquele vertice nas listas
	
	//Retira todas as arestas daquele vertice
	Vertice * auxVertice = NULL;
	Vertice * vert = BuscarVertice(g,vertice);
	
	auxVertice = g->inicial;
	
	//Retira as arestas da memoria
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
				//free(auxAresta);
				//break;
			}
			auxAresta2 = auxAresta;
			auxAresta = auxAresta->prox;
		}
		auxVertice = auxVertice->prox;
	}
	
	
	
	//Matar a lista do arestas
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
	*/
	
	
}


int QuantidadeVertice(Grafo * g) {
	Vertice * a = g->inicial;
	int c = 0;
	while (a != NULL) {
		c++;
		
		
		a = a->prox;
	}
	
	return c;
}

//Caminho minimo
void Relaxamento (Grafo * g, int inicio) {
	
	//Inicializar (colocar pesos infinitos);
	Vertice * init = g->inicial;
	while(init != NULL) {
		init->peso = -1;
		init->anterior = NULL;
		init = init->prox;
	}
	
	//Vertice * ant = g->inicial;
	
	Vertice * origin = BuscarVertice(g,inicio);
	Vertice * verd = origin;
	origin->peso = 0;
	int quant = QuantidadeVertice(g), i;
	
	while(quant-1 > i) {
		
		Aresta * ant2 = origin->primeiroVizinho;
		
		
		/*if(TodosVisitados(g) == 1) 
			stop = 0;*/
		
		//int control = 0;
		while(ant2 != NULL) {
			
			//Navega pelos vizinhos
			Vertice * vertV = ant2->vert;
			
			
			
			//vertV->peso = (vertV->peso > origin->peso + ant2->peso) || vertV-> peso == -1 ? origin->peso + ant2->peso : vertV->peso;
			//(vertV->peso > origin->peso + ant2->peso) || vertV-> peso == -1
			if(vertV->peso == -1 || (vertV->peso > (origin->peso + ant2->peso))) {
				
				vertV->peso = origin->peso + ant2->peso;
				printf("%d\n\n", vertV->peso);	
				vertV->anterior = origin;
				
				
				//getch();
				
			}
			
			
			ant2 = ant2->prox;
		}
		origin = origin->prox == NULL ? g->inicial : origin->prox;
		i++;
	}
	
	
	
}

void BellmanFord(Grafo * g, int vertice, int origem) {
	return;
	Vertice * vert = BuscarVertice(g,vertice);
	Vertice * origin = BuscarVertice(g,origem);
	printf("Origem: %c \t Destino: %c\n", origem, vertice);
	printf("%c --> ",origem);
	
	int i = 0;
	
	while(vert != origin) {
		
		//printf("Vert: %c; Origin: %c\n", vert->key);
		vert = vert->anterior;
		//getch();
		i++;
	}
	
	
	vert = BuscarVertice(g,vertice);
	int * arr = (int *) malloc(i*sizeof(int));
	int tan = i;
	i = 0;
	while(vert != origin) {
		
		arr[i] = vert->key;
		i++;
		
		vert = vert->anterior;
	}
	
	i = 0;
	for(i = tan-1; i >= 0; i--) {
		if(i != 0) printf("%c -->",arr[i]);
		else printf(" %c", arr[i]);
	}
	
	printf("\n\n");
	
	
	
}

void CriaVerticeText(char * buff,int key) {
	sprintf(buff, "CV %c\n", key);
}

void CriaArestaText(char * buff, int key, int aresta1, int aresta2, int peso) {
	sprintf(buff,"CA %d %c %c %d\n", key,aresta1,aresta2,peso);
}

int BuscaEmArray(int * arr, int val) {
	int i;

	for(i = 0; i < TAM_VERT_MAX; i++){
		if(arr[i] == val) {
			return 1;
		}
	}
	return 0;
}

void SalvarGrafo(Grafo * g, char * arquivo) {
	if(g != NULL) {
		
		FILE * file = fopen(arquivo,"w");
		char codeStr[10000];
		
		//Retorna os vertices como texto
		Vertice * auxVert = g->inicial;
		
		while (auxVert != NULL){
			char cvBuff[32];
			CriaVerticeText(cvBuff,auxVert->key);

			strcat(codeStr, cvBuff);
			auxVert = auxVert->prox;
		}

		//retorna o aresta como Textos
		auxVert = g->inicial;
		int vertice[TAM_VERT_MAX];
		int i = 0;

		while (auxVert != NULL){
			Aresta * auxAresta = auxVert->primeiroVizinho;
			while(auxAresta != NULL){
				if(!BuscaEmArray(vertice,auxAresta->id)){
					vertice[i++] = auxAresta->id;
					char caBuff[32];
					CriaArestaText(caBuff,auxAresta->id, auxVert->key, auxAresta->vert->key,auxAresta->peso);
					strcat(codeStr,caBuff);
				}
				auxAresta = auxAresta->prox;
			}

			auxVert = auxVert->prox;
		}
		fprintf(file,"%s",codeStr);
		fclose(file);
	}
}

void CaminhoMinimo(Grafo * g, int vertice1, int vertice2) {
	
	if(ExisteVertice(g,vertice1) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice1);
		return;
	}
	
	if(ExisteVertice(g,vertice2) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice2);
		return;
	}
	
	
	
	//Relaxamento
	Relaxamento(g, vertice1);
	
	//Algoritmo de Bellman-ford
	BellmanFord(g, vertice2,vertice1);
	
	
}

int QtdArestaByVertice(Grafo * g, int vertice) {
	
	if(ExisteVertice(g,vertice) == 0) {
		printf("\nERROR: Nao existe o vertice com chave '%c'.\n",vertice);
		return;
	}
	
	Vertice * vert = BuscarVertice(g, vertice);
	Aresta * ares = vert->primeiroVizinho;
	int i = 0;
	
	while(ares != NULL) {
		i++;
		ares = ares->prox;
	}
	return i;
}

int QtdVertice(Grafo * g) {
	Vertice * ant = g->inicial;
	int i = 0;
	while (ant != NULL) {
		i++;
		ant = ant->prox;
	}
	
	return i;
	
}

int QtdArestas(Grafo * g) {
	Vertice * vert = g->inicial;
	Aresta * ares = NULL;
	int i = 0;
	
	
	while (vert != NULL) {
		
		ares = vert->primeiroVizinho;
		
		while(ares != NULL) {
			
			i++;
			
			ares = ares->prox;
		}
		
		vert = vert->prox;
	}
	
	return i;
}


//Getters

int getPesoByIdVertice(Grafo * g, int vertice) {
	
	Vertice * vert = BuscarVertice(g,vertice);
	return vert->peso;
	
}

void RemoveArestaPorId(Grafo * g,int id) {
	Vertice * ant = g->inicial;
	
	
	while(ant != NULL) {
		
		Aresta * ant2 = ant->primeiroVizinho;
		while(ant2 != NULL) {
			if(ant2->id == id){
				DeletarAresta(g,ant->key, ant2->vert->key);
				return;
			}
				
			ant2 = ant2->prox;
		}
		ant = ant->prox;
	}
	
	
}

int GetVerticeUm(Grafo * g,int arestaId) {
	if (g != NULL){
		Aresta * aresta = BuscarAresta(g,arestaId);
		Vertice * aux = g->inicial;
		while (aux != NULL){
			Aresta * auxAres = aux->primeiroVizinho;
			while (auxAres != NULL) {
				if(auxAres = aresta){
					return aux->key;
				}
				auxAres = auxAres->prox;
			}
			aux = aux->prox;
		}
	}
	return -1;
}

int GetVerticeDois(Grafo * g,int arestaId) {
	if (g != NULL){
		Aresta * aresta = BuscarAresta(g,arestaId);
		return aresta->vert->key;
	}
	return -1;
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

Aresta * BuscarAresta (Grafo * g, int arestaId) {
	Vertice * ant = g->inicial;
	while(ant != NULL) {
		Aresta * arestaAux = ant->primeiroVizinho;

		while (arestaAux != NULL){

			if(arestaAux->id == arestaId){
				return arestaAux;
			}

			arestaAux = arestaAux->prox;
		}
		
		ant = ant->prox;
	}
}













