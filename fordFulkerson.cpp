/**
Ford Fulkerson cap eh a matriz de adjacencia.
g eh a lista de adjacencia do grafo.
inf eh maior que a quantidade maxima de fluxo possivel.
maxn eh a quantidade de vertice maxima.
ini sendo o vertice source.
fim sendo o vertice fim.
**/
struct FordFulkerson{
	int ini = 0, fim = 1;
	int cap[maxn][maxn], visited[maxn];
	vector< int > g[maxn];

	int ford_dfs(int v, int capMax){
		if( v == fim ) return capMax;
		if( visited[v] ) return -1;

		for(int j = 0; j < g[v].size(); j++){
			int u = g[v][j];
			if( cap[v][u] > 0 ){
				visited[v] = true;
				int x = ford_dfs(u, min(capMax, cap[v][u]));
				visited[v] = false;
				if( x > 0 ){
					cap[ v ][ u ] -= x;
					cap[ u ][ v ] += x;
					return x;
				}
			}
		}
		return -1;
	}

	int maxflow(){
		int total = 0;
		int x = ford_dfs(ini, inf);
		while( x != -1 ){
			total += x;
			x = ford_dfs(ini, inf);
		}
		return total;
	}
	// I se contecta com J com capacidade C
	int add(int i, int j, int c){
		g[i].push_back(j);
		g[j].push_back(i);
		cap[i][j] = c;
	}
} f;