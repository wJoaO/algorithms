int ternary_search( int l, int r, int k ) {
	int ml, mr;

	while( l <= r ) {
		ml = ( 2*l + r ) / 3; // l + ( r-l ) / 3;
		mr = ( 2*r + l ) / 3; // r - ( r-l ) / 3;
		if( v[ml] == k )
			return ml;
		if( v[mr] == k )
			return mr;
		if( k < v[ml] )
			r = ml-1;
		else if( k > v[mr] )
			l = mr+1;
		else
			l = ml+1, r = mr-1;
	}
	return -1;
}
