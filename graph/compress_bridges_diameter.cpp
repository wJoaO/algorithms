#include<bits/stdc++.h>
#define maxn 300010
#define maxm 300010

using namespace std;

int a, b;

struct Graph{
  // Achar pontes
  vector< pair<int, int> > g[maxn];
  int n, m, low[maxn], high[maxn], t;
  bool bridge[maxm];
  // Comprimir para árvore
  vector< int > tree[maxn];
  int scc, component[maxn];

  Graph(){
    t=1;
    scc = 0;
  }

  void add(int a, int b, int id){
    g[a].push_back(make_pair(b, id));
    g[b].push_back(make_pair(a, id));
  }

  // Um vertice aleatorio
  void find_bridges(int v, int p){
    low[v] = high[v] = t++;

    for(int i = 0; i < g[v].size(); i++){
      int u = g[v][i].first;
      if( u == p ) continue;
      if(!high[u]){
        find_bridges(u, v);
        if(low[u] > high[v]){
          bridge[ g[v][i].second ] = true;
        }
      }
      low[v] = min(low[v], low[u]);
    }
  }

  void make_component(int v, int grp){
    component[v] = grp;

    for(int i = 0; i < g[v].size(); i++){
      int u = g[v][i].first;
      int bdge = bridge[ g[v][i].second ];

      if(bdge){
        if(!component[u])
          make_component(u, ++scc);
        tree[ component[v] ].push_back( component[u] );
      }else{
        if(!component[u])
          make_component(u, grp);
      }
    }
  }

  void compress(){
    for(int i = 1; i <= n; i++){
      if(!component[i]) make_component(i, ++scc);
    }
  }

  // Vertice, distancia
  pair<int, int> bfs(int ini){
    int mark[maxn];
    memset(mark, 0, sizeof mark);

    queue< pair<int, int> > f;
    f.push(make_pair(ini, 0));
    mark[ini] = true;
    while(!f.empty()){
      int v = f.front().first;
      int dist = f.front().second;
      f.pop();

      for(int i = 0; i < tree[v].size(); i++){
        int u = tree[v][i];
        if(!mark[u]){
          mark[u] = true;
          f.push(make_pair(u, dist+1));
        }
      }

      if(f.empty())
        return make_pair(v, dist);
    }
    return make_pair(ini,0);
  }

  pair<int, int> diameter(){
    return bfs(bfs(1).first);
  }
} graph;

int main(){
  cin >> graph.n >> graph.m;
  for(int i = 0; i < graph.m; i++){
    cin >> a >> b;
    graph.add(a,b, i);
  }
  graph.find_bridges(1, -1);
  graph.compress();
  cout << graph.diameter().second << endl;
  return 0;
}