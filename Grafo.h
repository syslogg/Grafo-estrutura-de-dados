
//Definição

typedef struct grafo Grafo;

//Commands
void Imprimir(Grafo * g);
int ExisteVertice (Grafo * g, int key);
int ExisteAresta(Grafo * g, int vertice1, int vertice2);

//Criar grafo
Grafo * criar();

//Destruir grafo
void destruir(Grafo * g);

//Incluir vertice
void IncluirVertice(Grafo * g, int key);

//Incluir aresta
void IncluirAresta(Grafo * g, int vertice1, int vertice2, int peso);

//Deletar vertice
void DeletarVertice(Grafo * g, int vertice);

//Deletar aresta
void DeletarAresta(Grafo * g, int vertice1, int vertice2);

//Caminho minimo com bellman ford
void CaminhoMinimo(Grafo * g, int vertice1, int vertice2);

//Quantidades
int QtdVertice(Grafo * g);
int QtdArestas(Grafo * g);
int QtdArestaByVertice(Grafo * g, int vertice);

//Getters
int getPesoByIdVertice(Grafo * g, int vertice);



// - TODO
/*
	- Quantidade de vertice e aresta
	- Implementar informações de vertices e aresta
*/

