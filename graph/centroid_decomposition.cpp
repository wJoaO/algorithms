#include<bits/stdc++.h>
#define maxn 100010

using namespace std;

struct Tree{

    // Normal graph
    vector<int> g[maxn];
    int n,
        parent[maxn], 
        children[maxn];

    // Centroid Graph
    vector<int> g_centroid[maxn];
    int root_centroid, height_centroid[maxn];

    Tree(){
        memset(parent, -1, sizeof parent);
    }

    void add(int v, int u){
        g[v].push_back(u);
        g[u].push_back(v);
    }

    void inputTree(){
        scanf(" %d", &n);
        int a, b;
        for(int i = 0; i < n-1; i++){
            scanf(" %d %d", &a, &b);
            add(a,b);
        }
    }

    // V é uma sugestão de raiz.
    int centroid_component(int v, int h){
        int total = 1;
        pair<int, int> maior = {0, -1};
        for(int i = 0; i < g[v].size(); i++){
            int u = g[v][i];
            int tam = children[u];
            total += tam;
            maior = max(maior, {tam,u});
        }

        if(maior.first > total/2){ // V Não é uma raiz pois tem um filho com o tamanho maior que total/2
            rotate_tree(v, maior.second);
            return centroid_component(maior.second, h);
        }

        // V é uma raiz
        // Removendo o peso do vértice para não ser escolhido como raiz novamente.
        children[v] = 0;
        height_centroid[v] = h;
        for(int i = 0; i < g[v].size(); i++){
            int u = g[v][i];
            if(children[u] != 0){
                g_centroid[v].push_back(centroid_component(u, h+1));
            }
        }
        return v;
    }

    void rotate_tree(int father, int child){
        parent[father] = child;
        parent[child] = -1;

        children[father] -= children[child];
        children[child] += children[father];
    }

    void make_root(int v){
        children[v] = 1;
        for(int i = 0; i < g[v].size(); i++){
            int u = g[v][i];
            if(parent[v] == u) continue;

            parent[u] = v;
            make_root(u);
            children[v] += children[u];
        }
    }

    void make_centroid(){
        make_root(1);
        root_centroid = centroid_component(1, 0);
    }
} t;

int main(){
    t.inputTree();
    t.make_centroid();
    for(int i = 1; i <= t.n; i++){
        if(i!=1)printf(" ");
        printf("%c", 'A'+t.height_centroid[i]);
    }printf("\n");
    return 0;
}