//
// BIT 2D
//

ll BIT2D[maxn][maxn];

void update(ll x, ll y, ll val)
{
     for(; x < maxn; x += x&-x)
     	for(ll j = y; j < maxn; j += j&-j)
        	BIT2D[x][j] += val;
}
ll query(ll x, ll y)
{
     ll sum = 0;
     for(; x < maxn; x += x&-x)
     	for(ll j = y; j < maxn; j += j&-j)
        	sum += BIT2D[x][j];
     return sum;
}
