struct BIT{
	int v[maxn];
	void update(int x, int val){
		for(; x < maxn; x += x&-x)
			v[x] += val;
	}
	void rangeupdate(int x, int y, int val){
		update(x, val);
		update(y+1, -val);
	}
	int query(int x){
		if( x <= 0 ) return 0;
		if( x >= maxn ) x = maxn-1;
		
		int sum = 0;
		for(; x > 0; x -= x&-x)
			sum += v[x];
		return sum;
	}
	int rangequery(int x, int y){
		return query(y) - query(x-1);
	}
} bit;
