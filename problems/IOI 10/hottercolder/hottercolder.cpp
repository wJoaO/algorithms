#include "grader.h"
#include<bits/stdc++.h>

using namespace std;

// 81 pontos
int HC(int N){
    int i = 1, j = N, last = 1, next, r, meio, left, right;
    Guess(last);
    while(true){
        if( i == j ) return i;
        if( last > i ){
            next = i-(last-j);
            next = min(next, i);
            if((last+next)%2 == 1) next--;
            next = max(1, next);
            r = Guess(next);
        } else {
            next = j+(i-last);
            next = max(j, next);
            if((last+next)%2 == 1) next++;
            next = min(N, next);
            r = Guess(next);
        } 
        left = min(next, last);
        right = max(next, last);
        meio = (last+next)/2;
        if( r == 0 ) return meio;
        if( r == 1 ){ // hotter
            if( last < next ){
                i = meio+1;
            }else{
                j = meio;
                if((last+next)%2 == 0){
                    j--;
                }
            }
        }else{ // colder
            if( last < next ){
                j = meio;
                if((last+next)%2 == 0){
                    j--;
                }
            }else{
                i = meio+1;
            }
        }

        last = next;
    }   
}