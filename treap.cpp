#include<bits/stdc++.h>

using namespace std;

struct Node {
	int valor, key, size, maior;
	Node *l, *r;

	Node(int _valor) : valor(_valor), key((rand() << 16) ^ rand()), size(1), l(NULL), r(NULL), maior(_valor) {}
	~Node() { delete l; delete r; }
	
	void recalc() {
		size = 1;
		maior = valor;
		if (l) size += l->size, maior = max(maior, l->maior);
		if (r) size += r->size, maior = max(maior, r->maior);
	}
};

struct Treap {

	Node * merge(Node * l, Node * r) {
		if (!l || !r) return l ? l : r;
		// Se a prioridade esquerda é menor.
		if (l->key < r->key) {
			l->r = merge(l->r, r);
			l->recalc();
			return l;
			// Se a prioridade direita é maior ou igual.
		} else {
			r->l = merge(l, r->l);
			r->recalc();
			return r;
		}
	}

	// Valores maiores ou iguais a "valor" ficarão no r, e os demais no l.
	void split(Node * v, int valor, Node *& l, Node *& r) {
		l = r = NULL;
		if (!v) return;
		// Se o valor for maior, ir para direita
		if (v->valor < valor) {
			split(v->r, valor, v->r, r);
			l = v;
			// Se o valor for menor ou igual ir para esquerda.
		} else {
			split(v->l, valor, l, v->l);
			r = v;
		}
		v->recalc();
	}

	bool find(Node *v, int valor){
		if(!v) return false;
		if( v->valor == valor ) return true;
		if( v->valor < valor ) return find(v->r, valor);
		if( v->valor > valor ) return find(v->l, valor);
	}

	int smallestCount(Node *v, int valor){
		if(!v) return 0;
		if( v->valor == valor ) return ( v->l ? v->l->size : 0 ); // Se for menor ou igual adicionar + 1.
		if( v->valor < valor ) return 1 + ( v->l ? v->l->size : 0 ) 
										+ smallestCount(v->r, valor);
		if( v->valor > valor ) return smallestCount(v->l, valor);
	}

	Node * kth(Node *v, int posicao){
		if(!v) return NULL;
		int esquerda = (v->l? v->l->size: 0);
		if( posicao-esquerda == 1 ) return v;
		if( posicao-esquerda > 1 ) return kth(v->r, posicao-esquerda-1);
		if( posicao-esquerda < 1 ) return kth(v->l, posicao);
	}

	// Sendo i e j os índices no array ordenado
	// Talvez dê problemas de i e j estiverem fora do range.
	int query(int i, int j){
		Node *l, *q, *r;
		split(root, kth(root, i+1)->valor, l, q);
		split(q, kth(q, j+1-i)->valor+1, q, r);
		int x = q->maior;
		root = merge(l, merge(q,r));
		return x;
	}

	Node * root;
	Treap() : root(NULL) {}
	~Treap() { delete root; }

	// Se existe um elemento com o valor
	bool find(int valor){
		return find(root, valor);
	}
	// Quantidade de elementos menores que o valor
	int smallestCount(int valor){
		return smallestCount(root, valor);
	}
	// Retorna o k-th menor elemento
	Node * kth(int posicao){
		return kth(root, posicao);
	}
	// Insere o valor mesmo se já exista outro com valor igual
	void insert(int valor) {
		Node * l, * r;
		split(root, valor, l, r);
		root = merge(merge(l, new Node(valor)), r);
	}
	// Apaga todos os elementos que possuem o valor.
	void erase(int valor) {
		Node * l, * m, * r;
		split(root, valor, l, m);
		split(m, valor + 1, m, r);
		delete m;
		root = merge(l, r);
	}
	int size() const { return root ? root->size : 0; }
} treap;

int n, a;
char op;

int main(){
	scanf(" %d", &n); 

	for(int i = 0; i < n; i++){
		scanf(" %c %d", &op, &a);

		if( op == 'I' ){
			if( !treap.find(a) )
				treap.insert(a);
		}else if( op == 'D' ){
			treap.erase(a);
		}else if( op == 'C' ){
			cout << treap.smallestCount(a) << endl;
		}else if( op == 'K' ){
			Node * v = treap.kth(a);
			if( v == NULL ) cout << "invalid" << endl;
			else cout << v->valor << endl;
		}
	}

	return 0;
}
