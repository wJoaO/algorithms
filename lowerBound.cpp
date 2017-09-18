#include<bits/stdc++.h>
using namespace std;

// 1 - Se o valor for maior.
// 0 - Se o valor for menor igual.
bool check(int i){
	return busca > v[i];
}

// a inicio e b é o final
int lower_bound(int a, int b){
	int meio = (a+b)/2LL;
	if( a == b ) return a;
	if( check(meio) ){
		return lower_bound(meio+1LL, b);
	}else{
		return lower_bound(a, meio);
	}
}
// int v[] = {1, 2, 3, 3, 3, 4, 5, 10};
// int busca = 10;
// Se busca = 10 ele acha o item 10
// Se busca = 3 ele acha o primeiro 3
// Se busca = 11 ele acha o último elemento(10)
// Se busca = 8 ele acha o 10
// A função check "transforma" todo o array em algo assim:
// [1, 1, 1, 1, 1, .... , 1, 0, 0, 0, 0, 0]
// E pega o primeiro 0 que aparecer.





