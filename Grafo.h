
//Definição

typedef struct grafo Grafo;

//Criar grafo
Grafo * criar();

//Incluir vertice
void IncluirVertice(Grafo * g, int key);

//Incluir aresta
void IncluirAresta(Grafo * g, int vertice1, int vertice2, int peso);

//Deletar vertice
void DeletarVertice(Grafo * g, int vertice1, int vertice2);

//Deletar aresta
void DeletarAresta(Grafo * g, int vertice1, int vertice2);

//Caminho minimo com bellman ford
void CaminhoMinimo(Grafo * g, int vertice1, int vertice2);

//Commands
void Imprimir(Grafo * g);
int ExisteVertice (Grafo * g, int key);
int ExisteAresta(Grafo * g, int vertice1, int vertice2);

