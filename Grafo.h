
//Definição

typedef struct grafo Grafo;

//Criar grafo
Grafo * criar();

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

//Todos os vizinhos
void TodosVizinhos(Grafo * g, int vertice);

//Trocar chave
void TrocarChaveVertice(Grafo * g, int vertice, int novoVertice);

//Commands
void Imprimir(Grafo * g);
int ExisteVertice (Grafo * g, int key);
int ExisteAresta(Grafo * g, int vertice1, int vertice2);

