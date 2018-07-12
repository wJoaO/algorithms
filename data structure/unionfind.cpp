struct UnionFind{
    int pai[SZ];

    UnionFind(){
        memset(pai, -1, sizeof pai);
    }

    int find(int i){
        if(pai[i] == -1) return i;
        pai[i] = find(pai[i]);
        return pai[i];
    }

    bool uni(int x, int y){
        if(find(x) == find(y)) return false;
        pai[find(y)] = find(x);
        return true;
    }

} uf;

#define pii pair<int, int>
#define x first
#define y second

struct UnionFind2D{
	pii pai[SZ][SZ];

	UnionFind(){
		for(int i = 0; i < SZ; i++) for(int j = 0; j < SZ; j++ ) pai[i][j] = {i, j};
	}

	pii find(pii p){
		int i = p.x, j = p.y;
		if(pai[i][j] == p) return p;
		pai[i][j] = find(pai[i][j]);
		return pai[i][j];
	}

	bool uni(pii p1, pii p2){
		if(find(p1) == find(p2)) return false;
		pai[find(p2).x][find(p2).y] = find(p1);
		return true;
	}
} uf;