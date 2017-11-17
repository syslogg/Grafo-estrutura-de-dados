#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void command(Grafo * g,char * cmd);
void execute(FILE * f);
void console(Grafo * g);

Grafo * grafo;

int main(int argc, char *argv[]) {
	
	
	

	grafo = criar();
	
	/*IncluirVertice(grafo,'A');
	IncluirVertice(grafo,'B');
	IncluirVertice(grafo,'C');
	IncluirVertice(grafo,'D');
	IncluirVertice(grafo,'E');
	
	
	//Ligar vertices
	IncluirAresta(grafo,'A','B',1,1);
	IncluirAresta(grafo,'B','E',2,2);
	IncluirAresta(grafo,'B','C',3,3);
	IncluirAresta(grafo,'A','C',3,4);
	IncluirAresta(grafo,'B','D',2,5);
	IncluirAresta(grafo,'C','D',4,6);
	IncluirAresta(grafo,'D','E',1,7);
	*/
	/*int i;
	for(i = 0; i < 14; i++) {
		IncluirVertice(grafo,'A'+i);
	}
	
	
	
	IncluirAresta(grafo, 'A', 'F', 1, 1);
	IncluirAresta(grafo, 'A', 'E', 5, 2);
	IncluirAresta(grafo, 'A', 'I', 2, 3);
	IncluirAresta(grafo, 'B', 'I', 9, 4);
	IncluirAresta(grafo, 'B', 'C', 11, 5);
	IncluirAresta(grafo, 'B', 'E', 1, 6);
	IncluirAresta(grafo, 'C', 'F', 3, 7);
	IncluirAresta(grafo, 'C', 'J', 6, 8);
	IncluirAresta(grafo, 'C', 'G', 5, 9);
	IncluirAresta(grafo, 'C', 'D', 3, 10);
	IncluirAresta(grafo, 'D', 'G', 4, 11);
	IncluirAresta(grafo, 'D', 'N', 5, 12);
	IncluirAresta(grafo, 'E', 'H', 8, 13);
	IncluirAresta(grafo, 'F', 'I', 6, 14);
	IncluirAresta(grafo, 'F', 'M', 4, 15);
	IncluirAresta(grafo, 'F', 'G', 1, 16);
	IncluirAresta(grafo, 'H', 'I', 10, 17);
	IncluirAresta(grafo, 'H', 'M', 7, 18);
	IncluirAresta(grafo, 'J', 'L', 8, 19);
	IncluirAresta(grafo, 'J', 'K', 13, 20);
	IncluirAresta(grafo, 'K', 'M', 9, 21);
	IncluirAresta(grafo, 'K', 'N', 6, 22);*/
	
	//CaminhoMinimo(grafo, 'A', 'D');
	
	//RemoveArestaPorId(grafo,1);
	
	//DeletarVertice(grafo,'A');

	//Imprimir(grafo);
	
	
	
	//Abre console para grafo
	console(grafo);
	
	//fclose(f);
	return 0;
}

void console (Grafo * g) {
	
	while(1) {
		char input[500];
		printf(">");
		fflush(stdin);
		gets(input);
		fflush(stdin);
		command(g,input);
	}
	
}

void command(Grafo * g, char * cmd) {
	
	int params[500];
	char paramStr[100];
	
	if(sscanf(cmd,"CV %c",&params[0]) > 0) {
		char letter = params[0];
		IncluirVertice(g,letter);
		
	} else if (sscanf(cmd,"RV %c",&params[0]) > 0) {
		char letter = params[0];
		DeletarVertice(g,letter);
		
	} else if (sscanf(cmd,"CA %d %c %c %d",&params[0], &params[1], &params[2], &params[3]) > 0) {
		
		char v1 = params[1], v2 = params[2];
		
		IncluirAresta(grafo, v1,v2,params[3],params[0]);
		
	} else if (!strcmp(cmd,"IG")) {
		Imprimir(g);
	} else if (!strcmp(cmd,"HELP")) {
		printf("\n-= Sistema de Grafos - Comandos =-\n");
		printf("* CV [chave] - Criar vertice\n");
		printf("* CA [chave] [vertice_ori] [vertice_dest] [peso] - Criar aresta\n");
		printf("* RV [chave] - Deletar vertices\n");
		printf("* RA [chave] - Deletar Aresta\n");
		printf("* IG - Imprimir vertices\n");
		printf("* AM - Arvore de caminho minimo\n");
		printf("* CRG [nome_arquivo] - Carrega grafo pelo arquivo\n");
		printf("* SVG [nome_arquivo] - Cria arquivo com grafo da memoria\n");
		printf("* FM - Destroi grafo e encerra o programa\n\n");
	} else if (!strcmp(cmd,"FM")) {
		destruir(g);
		printf("Fim do programa!\n");
		gets();
		exit(1);
	} else if (sscanf(cmd,"RA %d",&params[0]) > 0) {
		RemoveArestaPorId(grafo,params[0]);
	} else if (sscanf(cmd,"CRG %s",paramStr) > 0) {
		//Executar arquivo
		FILE * f = fopen(paramStr,"r");
		
		if(f == NULL) {
			printf("Arquivo Inexistente\n");
			return;
		}
		destruir(g);
		g = criar();

		char buf[50];
		
		while((fgets(buf, sizeof(buf), f)) != NULL){
			//Retirar ultimo caracter e colocar EndOfString
			char c = buf[0];
			int i = 0;
			
			while(c != '\0'){
				if(c == '\n'){
					buf[i] = '\0';
				}
				c = buf[i++];
			}
			
			
			command(g,buf);
		}
		
	} else if (sscanf(cmd,"SVG %s",paramStr) > 0) {
		SalvarGrafo(g,paramStr);
	} else {
		printf("\nComando inexistente!\n\n");
	}
	
}






