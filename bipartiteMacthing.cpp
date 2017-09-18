struct BipartiteGraph{
	vector<int> l[maxn];
	int matchL[maxn], matchR[maxn], seen[maxn], tamL;

	void build(int n){
		tamL = n;
		for(int i = 0; i < n; i++){
			l[i].clear();
		}
	}
	// Sendo v do lado esquerdo e u do lado direito.
	void connect(int v, int u){
		l[v].push_back(u);
	}

	bool augmentingPath(int v){

		for(int i = 0; i < l[v].size(); i++){
			int u = l[v][i];
			if( !seen[ u ] ){
				seen[ u ] = true;
				if( matchR[u] == -1 || augmentingPath( matchR[u] ) ){
					matchR[u] = v;
					matchL[v] = u;
					return true;
				}
			}
		}
		return false;
	}
	
	int maxMatching(){
		memset(matchL, -1, sizeof matchL);
		memset(matchR, -1, sizeof matchR);

		int matching = 0;
		for(int i = 0; i < tamL; i++){
			memset(seen, 0, sizeof seen);

			if( matchL[i] == -1 && augmentingPath(i) ){
				matching++;
			}
		}
		return matching;
	}

} g;
