#include<bits/stdc++.h>
#define maxn 100010
using namespace std;

//
// GREEDY
//

int n;
double a[maxn], b[maxn];

int main(){
    scanf(" %d", &n);

    for(int i = 0; i < n; i++){
        scanf(" %lf %lf", &a[i], &b[i]);
        a[i]--;
        b[i]--;
    }

    sort(a, a+n);
    sort(b, b+n);

    double soma_a = 0, soma_b = 0, res = 0;
    int ind_b = n-1;
    for(int i = n-1; i>= 0 && a[i] > 0; i--){
        soma_a += a[i];
        soma_b--;

        while(ind_b >= 0 && min(soma_b, soma_a) < min(soma_b+b[ind_b], soma_a-1)){
            soma_b += b[ind_b--];
            soma_a--;
        }

        res = max(res, min(soma_a, soma_b));
    }
    printf("%.4lf\n", res);

    return 0;
}