#include<bits/stdc++.h>
#define ll long long
#define inf 0x3f3f3f3f3f3f3f3fLL

using namespace std;

struct Line{
    ll m, b;
    double x;
    Line(ll _m, ll _b, ll _x = -inf){
        m = _m;
        b = _b;
        x = _x;
    }
    Line(ll _m, ll _b, Line l2){
        m = _m;
        b = _b;
        x = get_x(l2);
    }
    double get_x(Line l2){
        return (double)(l2.b-b)/(m-l2.m);
    }
    ll get_y(ll x){
        return m*x + b;
    }
    bool operator<(const Line &l2) const{
        return x <= l2.x;
    }
};

struct ConvexHullTrick { 
    vector< Line > s;
    void add(ll m, ll b){
        while(s.size() >= 2){
            int sz = s.size();
            Line l1 = s[sz-2];
            Line l2 = s[sz-1];
            Line l3 = Line(m, b);

            if(l1.get_x(l2) < l2.get_x(l3))
                break;
            
            s.pop_back();
        }
        if(s.size() == 0) s.push_back(Line(m,b));
        else s.push_back(Line(m,b, s[(int)s.size()-1]));
    }

    ll query(ll x){
        if(s.size() == 0) return 0;
        auto it = lower_bound(s.begin(), s.end(), Line(-1, -1, x));
        it--;
        return (*it).get_y(x);
    }
} convex_hull_trick;
