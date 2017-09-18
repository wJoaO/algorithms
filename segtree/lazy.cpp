#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f
#define zero inf
#define maxn 1000

using namespace std;

struct SegmentTree{
    int st[4*maxn];
    // lazy
    int lazy[4*maxn];
	// Array inicial.
    int vet[maxn];
    // tamanho
    int tam;

    int join(int a, int b){
		return min(a ,b);
    }

    int value(int p){
		return st[p] + lazy[p];
    }

    void propagar(int p){
		lazy[p*2] += lazy[p];
		lazy[p*2+1] += lazy[p];
		lazy[p] = 0;
    }

    void clear(){
		memset( st, 0, sizeof st );
		memset( lazy, 0, sizeof lazy );
    }
     
    void build(int n){
		tam = n;
    	build(1, 0, tam-1);
    }
    
    void build(int p, int L, int R){
        if( L == R ){
            st[p] = vet[L];
			return;
        }
        build( p*2, L, (L+R)/2 );
        build( p*2+1, (L+R)/2 + 1, R);
        st[p] = join(st[p*2], st[p*2+1]);
    }
    
    int query( int i, int j ){
    	return query( 1, 0, tam-1, i, j );
    }
    
    int query( int p, int L, int R, int i, int j ){
        if( i > R || j < L ) return zero; // Fora do range da query
        if( L >= i && R <= j ) return value(p); // Totalmente dentro do range da query
        propagar(p);
		st[p] = join( value(p*2), value(p*2+1) );
		
        int p1 = query(p*2, L, (L+R)/2, i, j );
        int p2 = query(p*2+1, (L+R)/2 + 1, R, i, j);

        return join(p1, p2);
    }

    void update(int i, int j, int val){
		return update( 1, 0, tam-1, i, j, val );
    }

    void update(int p, int L, int R, int i, int j, int val){
        if( i > R || j < L ) return; // Fora do range do update
        if( L >= i && R <= j ){ // Totalmente dentro do range do update
        	lazy[p] += val;
        	return;
        }
        propagar(p);
        update(p*2, L, (L+R)/2, i, j, val);
        update(p*2+1, (L+R)/2 + 1, R, i, j, val);
        st[p] = join( value(p*2), value(p*2+1) );
    }
} segtree;


int main(){
	// Array inicial
	segtree.vet[0] = 10;
	segtree.vet[5] = 5;
	// Fazer o build
	segtree.build(7);
	// Updates
	segtree.update(0, 5, 2);
	segtree.update(2,2, 5);
	segtree.update(3,3, 5);
	// Querys
	cout << segtree.query(0,0) << endl;
	cout << segtree.query(0,6) << endl;
	cout << segtree.query(2,3) << endl;
	cout << segtree.query(5,5) << endl;

	return 0;
}
