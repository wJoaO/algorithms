//
// Convex Hull - Andrew
//
double cross(const par &O, const par &A, const par &B){
    return (A.first - O.first) * (B.second - O.second) -
    	(A.second - O.second) * (B.first - O.first);
}

vector<par> CH(vector<par> P){
    int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<par> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		// Se for para tirar os pontos collineares colocar <=
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) < 0) k--; 
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		// Se for para tirar os pontos collineares colocar <=
		while (k >= t && cross(H[k-2], H[k-1], P[i]) < 0) k--; 
		H[k++] = P[i];
	}

	H.resize(k-1);
	return H;
}
