#define maxn 4000
#define inf 0x3f3f3f3f
using namespace std;

/**
Edmond Karp.
g eh a lista de adjacencia do grafo.
inf eh maior que a quantidade maxima de fluxo possivel.
maxn eh a quantidade de vertice maxima.
ini sendo o vertice source.
fim sendo o vertice sink.
**/
struct EdmondKarp{
	struct Edge{
		int v, cap, flow;
		Edge * rev;
		Edge(int _v, int _cap): v(_v), cap(_cap), flow(0), rev(NULL) {}
	};
	int ini = 0, fim = 1;
	vector< Edge * > g[maxn];

	int maxflow(){
		//(Run a bfs to find the shortest s-t path.
        // We use 'pred' to store the edge taken to get to each vertex,
        // so we can recover the path afterwards)
		int flow = 0;
		Edge * pred[maxn];
		queue<int> q;
        while(true){
			memset(pred, 0, sizeof pred);
			q.push(ini);
		    while( !q.empty() ){
		    	int cur = q.front(); q.pop();
				for(int i = 0; i < g[cur].size(); i++){
					Edge * e = g[cur][i];
					if( pred[e->v] == NULL && e->v != ini && e->cap > e->flow ){
						pred[e->v] = e;
						q.push(e->v);
					}
				}
			}
			//break;
			if( pred[fim] == NULL ) return flow;
		
	        //(We found an augmenting path.
	        // See how much flow we can send) 
	        int df = inf;
	        for( Edge * e = pred[fim]; e != NULL; e = pred[e->rev->v] ){
				df = min(df, e->cap - e->flow);
			}
	        // (And update edges by that amount)
			for( Edge * e = pred[fim]; e != NULL; e = pred[e->rev->v] ){
				e->flow = e->flow + df;
				e->rev->flow = e->rev->flow - df;
			}
	        flow += df;
		}
	}
	// I se contecta com J com capacidade C
	int add(int i, int j, int c){
		// Aresta e com aresta reversa r
		Edge * e = new Edge(j, c), * r = new Edge(i, c);
		e->rev = r;
		r->rev = e;
		g[i].push_back(e);
		g[j].push_back(r);
	}
} f;