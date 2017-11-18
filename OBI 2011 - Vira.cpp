#include<bits/stdc++.h>
#define maxn 1010
#define mod 10007

using namespace std;

int n, v[maxn], pd[maxn][maxn], ipd[maxn][maxn];
char c;

int main(){
    scanf(" %d", &n);

    for(int i = 0; i < n; i++){
        scanf(" %c", &c);
        v[i] = (c == 'P');
    }

    pd[0][0] = v[0];
    ipd[0][0] = !v[0];
    for(int i = 1; i < n; i++){
        int prefix = 0;
        for(int k = 0; k <= i; k++){
            if(v[i]){
                ipd[i][k] = prefix;
            }else{
                pd[i][k] = prefix;
            }
            prefix += pd[i-1][k];
            prefix %= mod;
            //cout << prefix << endl;
        }
        int suffix = 0;
        for(int k = i; k >= 0; k--){
            suffix += ipd[i-1][k];
            suffix %= mod;
            //cout << suffix << endl;
            if(v[i]){
                pd[i][k] = suffix;
            }else{
                ipd[i][k] = suffix;
            }
        }
    }
    /*cout << "Table: \n";
    for(int i = 0; i < n; i++){
        cout << i << ", " << v[i] << " -> ";
        for(int j = 0; j < n; j++){
            cout << " " << pd[i][j];
        }
        cout << endl;
    }
    cout << "\nTable Invertida: \n";
    for(int i = 0; i < n; i++){
        cout << i << ", " << v[i] << " -> ";
        for(int j = 0; j < n; j++){
            cout << " " << ipd[i][j];
        }
        cout << endl;
    }*/
    int res = 0;
    for(int i = 0; i <= n; i++){
        res += pd[n-1][i];
        res %= mod;
    }
    printf("%d\n", res);

    return 0;
}

