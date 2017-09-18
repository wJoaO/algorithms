#define vi vector<int>
#define vvi vector< vi >

vvi multiplica( vvi m1, vvi m2 ){
	int tam = m1.size();
	vvi aux(tam, vi(tam, 0));
	for(int i = 0; i < tam; i++){
		for(int j = 0; j < tam; j++){
			aux[i][j] = 0;
			for(int k = 0; k < tam; k++){
				aux[i][j] += m1[i][k]*m2[k][j];
				aux[i][j] %= mod;
			}
		}
	}
	return aux;
}

vvi potencia( vvi m1, ll pot ){
	int tam = m1.size();
	ll pot_atual = 1LL;
	vvi temp = m1;
	// Matriz identidade
	vvi res(tam, vi(tam, 0)); for(int i = 0; i < tam; i++ ) res[i][i] = 1;
	while( pot_atual <= pot ){
		if( pot_atual & pot ){
			res = multiplica(res, temp);
		}
	
		temp = multiplica(temp, temp);
		pot_atual <<= 1LL;
	}

	return res;
}
