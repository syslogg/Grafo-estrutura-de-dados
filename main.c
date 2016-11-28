#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	
	Grafo * grafo = criar();

	
	/*IncluirVertice(grafo,'A');
	IncluirVertice(grafo,'B');
	IncluirVertice(grafo,'C');
	IncluirVertice(grafo,'D');
	IncluirVertice(grafo,'E');
	
	
	//Ligar vertices
	IncluirAresta(grafo,'A','B',1);
	IncluirAresta(grafo,'B','E',2);
	IncluirAresta(grafo,'B','C',3);
	IncluirAresta(grafo,'A','C',3);
	IncluirAresta(grafo,'B','D',2);
	IncluirAresta(grafo,'C','D',4);
	IncluirAresta(grafo,'D','E',1);*/
	
	
	IncluirVertice(grafo,'A');
	IncluirVertice(grafo,'B');
	IncluirVertice(grafo,'C');
	IncluirVertice(grafo,'D');
	
	IncluirAresta(grafo,'A','B',1);
	IncluirAresta(grafo,'B','C',2);
	IncluirAresta(grafo,'C','D',4);
	IncluirAresta(grafo,'D','A',3);
	IncluirAresta(grafo,'B','D',5);
	
	CaminhoMinimo(grafo, 'D', 'B');

	//DeletarVertice(grafo,'A');

	Imprimir(grafo);
	
	return 0;
}
