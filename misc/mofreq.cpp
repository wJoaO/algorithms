#include<bits/stdc++.h>
#define maxn 100010

using namespace std;
// Dado um vetor n de elementos realizar m consultas
// cada consulta a,b retorna a maior frequencia encontrada
// frequencia sendo a quantidade do mesmo número no intervalo.
// Aplicação do Mo
int n, rootn, m, v[maxn], r[maxn], id[maxn], i;
map<int, int> compressao;
pair<int, int> q[maxn];

struct Freq{
	int f[maxn], c[maxn], maior = 0;

	void insert(int v){
		int q = f[v]++;
		c[q]--; c[q+1]++;
		maior = max(maior, q+1);
	}

	void remove(int v){
		int q = f[v]--;
		c[q]--; c[q-1]++;
		if( q == maior && c[q] <= 0 ) maior = q-1;
		maior = max(maior, 0);
	}
}f;

bool operador( const int id1, const int id2){
	int bucket1 = q[id1].first/rootn, bucket2 = q[id2].first/rootn;
	if( bucket1 == bucket2 ){
		return q[id1].second < q[id2].second;
	}else return bucket1 < bucket2;
}

main(){
	scanf("%d%d", &n, &m);
	rootn = sqrt(n);

	for(i = 1; i <= n; i++){
		scanf(" %d", &v[i]);
		compressao[v[i]];
	}

	int k = 0;
	for(map<int, int>::iterator it = compressao.begin(); it != compressao.end(); it++ ){
		it->second = k++;
	}

	for(i = 1; i <= n; i++){
		v[i] = compressao[ v[i] ];
	}

	for(i = 0; i < m; i++){
		scanf(" %d %d", &q[i].first, &q[i].second); id[i] = i;
	}
	
	sort(id, id+m, operador);

	int lastj = 0, lasti = 1;
	for(i = 0; i < m; i++){
		int id1 = id[i];
		int atuali = q[id1].first;
		int atualj = q[id1].second;
		while( lastj < atualj ) f.insert(v[++lastj]);
		while( lasti > atuali ) f.insert(v[--lasti]);
		while( lastj > atualj ) f.remove(v[lastj--]);
		while( lasti < atuali ) f.remove(v[lasti++]);
		r[id1] = f.maior;
	}

	for(i = 0; i < m; i++)
		printf("%d\n", r[i]);
	return 0;
}