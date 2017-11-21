
//Defini��o

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
void IncluirAresta(Grafo * g, int vertice1, int vertice2, int peso, int id);

//Deletar vertice
void DeletarVertice(Grafo * g, int vertice);

//Deletar aresta
void DeletarAresta(Grafo * g, int vertice1, int vertice2);

//Caminho minimo com bellman ford
void CaminhoMinimo(Grafo * g, int vertice1, int vertice2);

//Salvar arquivo
void SalvarGrafo(Grafo * g, char * arquivo);

//Quantidades
int QtdVertice(Grafo * g);
int QtdArestas(Grafo * g);
int QtdArestaByVertice(Grafo * g, int vertice);

//Getters
int getPesoByIdVertice(Grafo * g, int vertice);

void RemoveArestaPorId(Grafo * g,int id);

//Algoritmo de Kruskal
int * Vizinhos(Grafo * g, int vertice);
int PesoDaAresta (Grafo * g, int arestaId);
int * ListaDeVertices(Grafo * g);
int * ArestaIdsPorVertice(Grafo * g, int vertice);
int * ArestaOrdenadas(Grafo *g, int * retTam);
int GetVerticeUm(Grafo * g,int arestaId);
int GetVerticeDois(Grafo * g,int arestaId);


// - TODO
/*
	- Quantidade de vertice e aresta
	- Implementar informa��es de vertices e aresta
*/

