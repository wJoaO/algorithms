struct BIT2D{
	int v[maxn][maxn];

	void update(int x, int y, int val)
	{
		 for(; x < maxn; x += x&-x)
		 	for(int j = y; j < maxn; j += j&-j)
		    	v[x][j] += val;
	}
	int query(int x, int y)
	{
		 int sum = 0;
		 for(; x > 0; x -= x&-x)
		 	for(int j = y; j > 0; j -= j&-j)
		    	sum += v[x][j];
		 return sum;
	}
	int rangeupdate(int a1, int b1, int a2, int b2, int val){
		update(a1,b1,val);
		update(a2+1, b2+1, val);
		update(a1,b2+1, -val);
		update(a2+1,b1, -val);
	}
}bit;