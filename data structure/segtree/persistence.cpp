#include<bits/stdc++.h>
#define ll long long
#define maxn 200010
#define maxlogn 20
#define maxq 200010
#define zero 0

using namespace std;

struct PersistenceSegmentTree{
	struct Node{
		int v, l, r;
		Node(){ l = r = -1; v = zero; }
	};

	// maxn sendo o espaço amostral
	// maxlogn o logn de maxn (altura maxima)
	// maxq o total de updates
    Node st[4*maxn + maxlogn * maxq ];
    // versoes
    vector<int> versions;
    // tamanho
    int tam;
    // id para o último nó
    int last_node = -1;
    
    int join(int a, int b){
    	return a + b;
    }
    
    int join(int p){
		return join( st[p].l != -1 ? st[st[p].l].v : zero, 
				     st[p].r != -1 ? st[st[p].r].v : zero);
    }

    void build(int n){
		tam = n;
    	build(1, 0, tam-1);
    	versions.push_back(1);
    }
    
    void build(int p, int L, int R){
    	last_node = max(last_node, p);
        if( L == R ){
            //st[p].v = vet[L];
			return;
        }
        st[p].l = p*2;
        st[p].r = p*2+1;
        build( st[p].l, L, (L+R)/2 );
        build( st[p].r, (L+R)/2 + 1, R);
        st[p].v = join(p);
    }

	int rangequery(int i, int j, int version_left, int version_right){
		return query(i,j,version_right) - query(i,j, max(0, version_left-1));
	}
    
    int query( int i, int j, int version = -1 ){
		if( version < 0 || version >= versions.size()) version = (int)versions.size()-1;
		if( i > j ) return 0;		
    	return query( versions[version], 0, tam-1, i, j );
    }
    
    int query( int p, int L, int R, int i, int j ){
        if( i > R || j < L ) return zero; // Fora do range da query
        if( L >= i && R <= j ) return st[p].v; // Totalmente dentro do range da query

        int p1 = query(st[p].l, L, (L+R)/2, i, j );
        int p2 = query(st[p].r, (L+R)/2 + 1, R, i, j);

        return join(p1, p2);
    }
	// Point update
    void update(int i, int val, int version = -1){
    	// Se não for passado versão, atualizar a última versão.
    	if( version == -1 ) version = (int)versions.size()-1;
		versions.push_back(update( versions[version], 0, tam-1, i, val ));
    }

    int update(int old_p, int L, int R, int i, int val){
        if( i > R || i < L ) return old_p; // Fora do range do update
        int p = ++last_node;
        if( L == i && R == i ){ // Totalmente dentro do range do update
			st[p].v = val;
			return p;
		}
		st[p].l = update(st[old_p].l, L, (L+R)/2, i, val);
        st[p].r = update(st[old_p].r, (L+R)/2 + 1, R, i, val);

        st[p].v = join(p);
    	return p;
    }
} segtree;