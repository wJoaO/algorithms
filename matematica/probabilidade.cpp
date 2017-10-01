#include<bits/stdc++.h>
#define mod 1000000007
#define maxfat 100
#define int long long

using namespace std;

int power(int x, unsigned int y){
	if (y == 0)
	    return 1;
	int p = power(x, y/2) % mod;
	p = (p * p) % mod;
	return (y%2 == 0)? p : (x * p) % mod;
}



int inversoMult(int a) {
	return power(a, mod-2);
}



struct Prob{
	int fat[maxfat];
	Prob(){
		fat[1] = 1;
		for(int i = 2; i < maxfat; i++ ) fat[i] = ( fat[i-1] * i ) % mod;
	}

	int arranjo(int n, int p){
		return ( fat[n] * inversoMult( fat[n-p] ) ) % mod;
	}

	int permutacao(int n){
		return arranjo(n,n-1);
	}

	int combinacao_normal(int n, int p){
		return ( arranjo(n, p) * inversoMult( fat[p] ) ) % mod;
	}

	int combinacao_repeticao(int n, int p){
		return combinacao_normal(n+p-1, p);
	}

	// Let's say that I have two ordered sets of numbers {1,2} and {3,4}. 
	// I'm trying to figure out the number of possible ways to combine these two sets 
	// into one without breaking the ordering of the two sets.
	// So for instance, {1,2,3,4}, {3,4,1,2}, and {1,3,2,4} are valid combinations, but {2,1,4,3} isn't.
	int combinar_conjuntos_ordenados(int p1, int p2){
		return combinacao_repeticao(p1+1, p2); // combinacao_repeticao(p2+1, p1);
	}

} prob;

