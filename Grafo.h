
//Definição

typedef struct grafo Grafo;

//Criar grafo
Grafo * criar();

//Incluir vertice
void IncluirVertice(Grafo * g, int key);

//Incluir aresta
void IncluirAresta(Grafo * g, int key);

//Commands
void Imprimir(Grafo * g);

