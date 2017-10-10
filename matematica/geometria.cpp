#include<bits/stdc++.h>
#define int long long
#define EPS 1e-9
using namespace std;

// CHECA SE PONTOS SAO DOUBLE OU INT
// CHECAR O EPS EM TODAS OPERAÇÕES

struct Point{
	double x, y;
	Point(){}
	Point(double _x, double _y): x(_x), y(_y) {}
	
	bool operator!=(Point p){ return x != p.x || y != p.y; } // Usar EPS
	Point operator-(Point p){ return Point(x-p.x, y-p.y); }
	
	// Area do triangulo = cross/2
	// ==0 - colinear, >0 - horário, <0 => antihorário
	double cross(Point &p, Point &r){
		return (y - p.y) * (r.x - x) - (x - p.x) * (r.y - y);
	}
	double dist(Point &p){
		return sqrt( (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y) );
	}
	int orientation(Point &p, Point &r){
		double val = cross(p,r);
		if( fabs(val) < EPS ) return 0;
		return (val > 0.0? 1 : -1);
		//int val = cross(p,r);
		//if (val == 0) return 0;
		//return (val > 0)? 1: -1;
	}
};

struct LineSegment{
	Point p, q;
	LineSegment(){}
	LineSegment(Point _p, Point _q): p(_p), q(_q) {}
	
	bool intersect(LineSegment s){
		return p.orientation(q, s.p)*p.orientation(q, s.q) <= 0 && 
			   s.p.orientation(s.q, p)*s.p.orientation(s.q, q)<=0;
	}
};

struct Line{
	double a, b, c;
	Line(){}
	Line(Point p, Point q){
		a = q.y - p.y;
		b = p.x - q.x;
		c = a*p.x + b*p.y;
	}
	Line(LineSegment s): Line(s.p, s.q) {}
	Line(double _a, double _b, double _c): a(_a), b(_b), c(_c) {}
	
	Point reflect(Point p){
		// Linha perpendicular: -Bx+Ay=D
		Point Y = intersectPoint(Line(-b, a, -b*p.x + a*p.y));
		return Y - ( p - Y );
	}

	bool intersect(Line l){
		return fabs( a*l.b - l.a*b ) < EPS;
		//return ( a*l.b - l.a*b ) != 0;
	}

	Point intersectPoint(Line l){
		double det = a*l.b - l.a*b;
		return Point(((double)l.b*c - b*l.c)/det,((double)a*l.c - l.a*c)/det);
	}
};
