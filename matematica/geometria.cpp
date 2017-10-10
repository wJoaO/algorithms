struct Ponto{
	int x, y;
	bool operator!=(Ponto &p){ return x != p.x || y != p.y; }
	
	// To find orientation of ordered triplet (p, Ponto, q).
	// Vetor PontoP e PontoQ
	// 0 --> p, q and r are colinear
	// 1 --> Clockwise
	// -1 --> Counterclockwise
	int orientation(Ponto &p, Ponto &r)
	{
		int val = (y - p.y) * (r.x - x) -
			      (x - p.x) * (r.y - y);
	 
		if (val == 0) return 0;  // colinear
		return (val > 0)? 1: -1; // clock or counterclock wise
	}
};

struct SegmentoLinha{
	Ponto p, q;
	bool intersect(SegmentoLinha &s){
		return p.orientation(q, s.p)*p.orientation(q, s.q) <= 0 && s.p.orientation(s.q, p)*s.p.orientation(s.q, q)<=0;
	}
};