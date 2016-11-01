#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	
	Grafo * grafo = criar();

	IncluirVertice(grafo,1);
	IncluirVertice(grafo,8);
	IncluirVertice(grafo,3);
	IncluirVertice(grafo,16);
	IncluirVertice(grafo,5);
	IncluirVertice(grafo,6);
	
	Imprimir(grafo);
	
	return 0;
}
