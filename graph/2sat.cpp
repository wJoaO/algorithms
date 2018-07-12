// Os vertices pares indicam as proposicoes falsas
// Os vertices impares indicam as proposicoes verdadeiras
// Achar qual proposicao relativa a cada vertice, eh so dividiar vertice/2
// tamG = quantidade_proposicoes*2
bool twosat(){
	kosaraju();
	for(int i = 0; i < tamG; i+=2){
		// Todo par de proposicoes(proposicao falsa, proposicao verdadeira)
		// Nao podem esta no mesmo componente
		if( componente[i] == componente[i+1] ) return false;
	}
	return true;
}
// Id no grafo que representa a proposicao de número p1 como verdadeira.
int idVerdade(int p1){
	return p1*2 + 1;
}
// Id no grafo que representa a proposicao de número p1 como falsa.
int idFalso(int p1){
	return p1*2;
}
// Adiciona uma aresta no grafo.
void addAresta(int p1, int p2){
	g[p1].push_back(p2);
	gt[p2].push_back(p1);
}








