#include<bits/stdc++.h>
#define zero 0
#define maxn 100010

using namespace std;

struct SegmentTree{
    int st[4*maxn];
    // lazy
    int lazy[4*maxn];
    // tamanho
    int tam;

    int value(int p, int quantidade){
    	if( lazy[p] == -1 ) return st[p];
		return lazy[p]*quantidade;
    }

    void propagar(int p){
    	if( lazy[p] == -1 ) return;
		lazy[p*2] = lazy[p];
		lazy[p*2+1] = lazy[p];
		lazy[p] = -1;
    }
     
    void build(int n){
		tam = n;
    }
    
    int query( int i, int j ){
    	return query( 1, 0, tam-1, i, j );
    }
    
    int query( int p, int L, int R, int i, int j ){
        if( i > R || j < L ) return zero; // Fora do range da query
        if( L >= i && R <= j ) return value(p, R-L+1); // Totalmente dentro do range da query

        propagar(p);
        
		st[p] = value(p*2, (L+R)/2 - L + 1) + 
				value(p*2+1, R - (L+R)/2 - 1 + 1);
				
        return query(p*2, L, (L+R)/2, i, j ) +
        	   query(p*2+1, (L+R)/2 + 1, R, i, j);
    }

    void update(int i, int j, int val){
		return update( 1, 0, tam-1, i, j, val );
    }

    void update(int p, int L, int R, int i, int j, int val){
        if( i > R || j < L ) return; // Fora do range do update
        if( L >= i && R <= j ){ // Totalmente dentro do range do update
        	lazy[p] = val;
        	return;
        }
        propagar(p);
        
        update(p*2, L, (L+R)/2, i, j, val);
        update(p*2+1, (L+R)/2 + 1, R, i, j, val);
        
        st[p] = value(p*2, (L+R)/2 - L + 1) + 
        		value(p*2+1, R - (L+R)/2 - 1 + 1);
    }

	void print(){
		print(1, 0, tam-1);
	}
    void print(int p, int L, int R){
		cout << "P: " << p << " lazy: " << lazy[p] << " st: " << st[p] << " l: " << L << " r: " << R << " value: " << value(p, R-L+1) << endl;
		if( L == R ) return;
		print(p*2, L, (L+R)/2);
		print(p*2+1, (L+R)/2 + 1, R);
    }
} segtree;

int x, y, a, b;
int main(){
	int sol = 1;
	scanf(" %d %d", &y, &x);
	segtree.build(y);
	for(int i = 0; i < x-1; i++){
		scanf(" %d %d", &a, &b);
		segtree.update(a, b-1, 1);
		if( segtree.query(0,y-1) == y ){
			sol += 2;
			segtree.update(0,y-1,0);
			segtree.update(a,b-1,1);
		}
	}
	printf("%d\n", sol);
	return 0;
}

