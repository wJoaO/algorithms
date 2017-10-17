#include<bits/stdc++.h>
#define maxn 100010
#define inf 0x3f3f3f3f3f3f3f3f
#define int long long

using namespace std;

int n, k;
int v[maxn], p[maxn], pd_dir[maxn], pd_esq[maxn];

int consulta(int i, int j){
	return p[j] - (i > 0 ? p[i-1] : 0 );
}

main(){
	scanf(" %lld %lld", &n, &k);
	for(int i = 0; i < n; i++)scanf(" %lld", &v[i]);

	p[0] = -v[0];
	for(int i = 1; i < n; i++ ) p[i] = -v[i] + p[i-1];

	memset(pd_dir, -inf, sizeof pd_dir);
	memset(pd_esq, -inf, sizeof pd_esq);

	for(int i = 0; i+k-1 < n; i++){
		int calc = consulta(i, i+k-1);
		pd_dir[i] = pd_esq[i+k-1] = calc;
	}
	for(int i = 1; i < n; i++){
		pd_esq[i] = max(pd_esq[i], pd_esq[i-1]);
	}
	for(int i = n-1; i >= 0; i--){
		pd_dir[i] = max(pd_dir[i], pd_dir[i+1]);
	}

	for(int i = 0; i < n; i++){
		//cout << pd_dir[i] << ", " << pd_esq[i] << endl;
	}

	int res = -inf;

	for(int i = 0; i+1 < n; i++ ) res = max(res, pd_esq[i] + pd_dir[i+1]);

	printf("%lld\n", res);
	
	return 0;
}
