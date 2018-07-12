// Variaveis que devem ser inicializadas na MAIN
int tamG;
vi g[maxn], gt[maxn];

// Variavies auxiliares do algoritmos Kosaraju

// int cont[maxn]; // Contar quantos elementos em cada scc
// int componente[maxn]; // Dizer qual componente de cada vertice
// vi scc[maxn]; // Ter uma lista de elementos em cada scc
stack<int> kosaraju_pilha;
int visitado[maxn], numSCC;

void kosaraju_dfs1(int v){
	visitado[v] = true;
	for(int i = 0; i < g[v].size(); i++){
		int u = g[v][i];

		if( !visitado[u] ) kosaraju_dfs1(u);
	}

	kosaraju_pilha.push(v);
}

void kosaraju_dfs2(int v){
	visitado[v] = true;
	for(int i = 0; i < gt[v].size(); i++){
		int u = gt[v][i];

		if( !visitado[u] ) kosaraju_dfs2(u);
	}
	// cont[numSCC]++;
	// scc[numSCC].push_back(v);
	// componente[v] = numSCC;
}

void kosaraju(){
	numSCC = 0;
	// Deve-se limpar arrays e pilha se rodar o kosaraju mais de uma vez.
	for(int i = 0; i < tamG; i++)
		if( !visitado[i] ) kosaraju_dfs1(i);

	memset(visitado, 0, sizeof visitado);

	while( !kosaraju_pilha.empty() ){
		int v = kosaraju_pilha.top(); kosaraju_pilha.pop();
		if( !visitado[v] ) kosaraju_dfs2(v), numSCC++;
	}
}
