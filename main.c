#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void command(Grafo * g,char * cmd);
void execute(FILE * f);
void console(Grafo * g);



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
	
	
	/*IncluirAresta(grafo,'A','B',1, 1);
	IncluirAresta(grafo,'B','C',2, 2);
	IncluirAresta(grafo,'C','D',4,3);
	IncluirAresta(grafo,'D','A',3,4);
	IncluirAresta(grafo,'B','D',5,5);*/
	
	//CaminhoMinimo(grafo, 'D', 'B');

	//DeletarVertice(grafo,'A');

	Imprimir(grafo);
	
	/*FILE * f = fopen("arquivo.txt","r");
	
	if(f == NULL) {
		printf("Erro ao executar o arquivo");
		return;
	}
	
	execute(f);*/
	console(grafo);
	
	//fclose(f);
	return 0;
}

void console (Grafo * g) {
	
	while(1) {
		char input[500];
		gets(input);
		fflush(stdin);
		command(g,input);
	}
	
}

void command(Grafo * g, char * cmd) {
	
	int params[500];
	
	if(sscanf(cmd,"CV %c",&params[0]) > 0) {
		
		IncluirVertice(g,params[0]);
		
	} else if (sscanf(cmd,"RV %c",&params[0]) > 0) {
		
		DeletarVertice(g,params[0]);
		
	} else if (sscanf(cmd,"CA %d %c %c %d",&params[0], &params[1], &params[2], &params[3]) > 0) {
		IncluirAresta(g, params[1],params[2],params[3],params[0]);
		//IncluirAresta(g, params[1],params[2],params[3],params[0]);
		printf("%d %c %c %d", params[0],params[1], params[2], params[3]);
		
	} else if (!strcmp(cmd,"IG")) {
		Imprimir(g);
	} else if (sscanf(cmd,"CA %d %c %c %d",&params[0], &params[1], &params[2], &params[3]) > 0) {
		
	}
}






