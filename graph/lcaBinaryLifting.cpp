#define maxn 50010
#define maxlogn 20

class BinaryLifting{ public:
	int table[maxn][maxlogn];
	int prof[maxn];
	int tam;
	BinaryLifting(){
		memset(table, -1, sizeof table);
	}
	// a profundidade
	// a posição [i][0] deve está preenchida.(Os pais dos nós)
	void build(int n){
		int i, j, aux;
		tam = n;

		for(j = 1; j < maxlogn; j++){
			for(i = 0; i < n; i++){
				aux = table[i][j-1];
				if( aux != -1 ) aux = table[aux][j-1];
				table[i][j] = aux;
			}
		}
	}

	int up(int a, int d){
		for(int i = 0; i < maxlogn; i++){
			if( d & (1 << i) ){
				a = table[a][i];
			}
		}
		return a;
	}

	int lca(int a, int b){
	
		if( prof[a] < prof[b] ) b = up(b, prof[b]-prof[a]);
		else if( prof[b] < prof[a] ) a = up(a, prof[a]-prof[b]);

		if( a == b ) return a;
		
		for(int i = maxlogn-1; i >= 0; i--){
			if( table[a][i] != table[b][i] ){
				a = table[a][i];
				b = table[b][i];
			}
		}
		return table[a][0];
	}

	int dist(int a, int b){
		return prof[a] + prof[b] - 2*prof[lca(a,b)];
	}
} lca;
