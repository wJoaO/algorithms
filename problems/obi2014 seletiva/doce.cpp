#include<bits/stdc++.h>
#define maxn 100010
#define int long long

using namespace std;

int n, b, d, p;

struct Node {
	int valor, key, quantidade;
	int fv, fq;
	Node *l, *r;

	Node(int _valor, int _quantidade) : valor(_valor), key((rand() << 16) ^ rand()), quantidade(_quantidade), l(NULL), r(NULL), fq(_quantidade) {
		fv = _valor*_quantidade;
	}
	~Node() { delete l; delete r; }
	
	void recalc() {
		fq = quantidade;
		fv = valor*quantidade;
		if (l) fq += l->fq, fv += l->fv;
		if (r) fq += r->fq, fv += r->fv;
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

	// Ficarão "quantidade" no l(raiz do l pode fazer ultrapassar o quantidade), e os demais no r.
	void splitSmallest(Node * v, int quantidade, Node *& l, Node *& r) {
		l = r = NULL;
		if (!v) return;
		
		if (v->l && v->l->fq >= quantidade) {
			splitSmallest(v->l, quantidade, l, v->l);
			r = v;
		} else if( (v->l? v->l->fq:0) + v->quantidade >= quantidade ){
			quantidade -= (v->l? v->l->fq:0);
			if( quantidade != v->quantidade ){
				Node * n = new Node(v->valor, v->quantidade-quantidade);
				v->quantidade = quantidade;
				n->r = v->r;
				n->recalc();
				r = n;
			}else{
				r = v->r;
			}
			l = v;
			v->r = NULL;
		} else {
			splitSmallest(v->r, quantidade - v->quantidade - (v->l? v->l->fq: 0), v->r, r);
			l = v;
		}
		v->recalc();
	}
	Node * root;
	Treap() : root(NULL) {}
	~Treap() { delete root; }

	// Insere o valor mesmo se já exista outro com valor igual
	void insert(int valor, int quantidade) {
		Node * l, * r;
		split(root, valor, l, r);
		root = merge(merge(l, new Node(valor, quantidade)), r);
	}
	// Quantos valores existem menor que "valor"
	int menoresQue(int valor){
		Node * l, * r;
		split(root, valor, l, r);
		int res = (l? l->fq: 0);
		root = merge(l,r);
		return res;
	}
	// Retorna a soma dos primeiros "quantidade" valor
	int top(int quantidade){
		Node * l, * r;
		splitSmallest(root, quantidade, l, r);
		int valor = (l?l->fv:0);
		root = merge(l,r);
		return valor;
	}
	// Remover os d menores
	void removeSmallest(int d){ 
		Node * l, * r;
		splitSmallest(root, d, l, r);
		root = r;
		if( l ) delete l;
	}
	// Remover todos menos os d menores
	void limit(int d){
		Node * l, * r;
		splitSmallest(root, d, l, r);
		root = l;
		if( r ) delete r;
	}
	
	// Apaga todos os elementos que possuem o valor.
	void erase(int valor) {
		Node * l, * m, * r;
		split(root, valor, l, m);
		split(m, valor + 1, m, r);
		delete m; 
		root = merge(l, r);
	}
	int size() const { return root ? root->fq : 0; }
} treap;

main(){
	/*int a, b, c;
	while(true){
		cin >> a >> b >> c;
		if( a == 0 ) treap.insert(c, b);
		else if( a == 1 ) cout << treap.menoresQue(b) << endl;
		cout << treap.size() << endl;
	}*/
	cin >> n;
	int total = 0;
	for(int i = 0; i < n; i++){
		cin >> d >> b >> p;
		//cout << "INserindo : " << d << " " << b << " " << p << endl;
		//cout <<" Treap size: " << treap.size() << endl;
		int qtde_menores = 0;
		if( treap.size() ){
			int qtde_menores = min(d, treap.menoresQue(p));
			//cout << "QUantidade menores " << qtde_menores << endl;
			total += treap.top(qtde_menores);
			treap.removeSmallest(qtde_menores);
			d -= qtde_menores;
			//cout << "D resultado: " << d << endl;
		}
		treap.limit(d);
		if( d ){
			int usa_atual = min(d, b);
			total += usa_atual*p;
			b -= usa_atual;
			d -= usa_atual;
		}
		if( b ) treap.insert(p, b);
		if( d > treap.size() ){
			total = -1;
			break;
		}else if( d ){
			total += treap.top(d);
			treap.removeSmallest(d);
		}
		//cout << "Total: " << total << endl;
	}
	cout << total << endl;
	return 0;
}

