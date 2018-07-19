#include "grader.h"
#include "hottercolder.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<bits/stdc++.h>

using namespace std;

static int moves, max_moves = 0, TT, NN, _prev = -1;
int Guess(int x){
   int r;
   if (_prev == -1 || abs(x-TT) == abs(_prev-TT)) r = 0;
   else if (abs(x-TT) > abs(_prev-TT)) r = -1;
   else r = 1;
   _prev = x;
   if (x < 1 || x > NN) exit(92);
   moves++;
   return r;
}

int main(){
    printf("Comecando a main\n");
   int n=0,i,t,OK=0,sub1=0,sub2=0,sub3=0;
   double worst = 999999;
   while (2 == scanf("%d%d",&NN,&TT)) {
      if (NN > n) n = NN;
      _prev = -1;
      moves = 0;
      int h = HC(NN);
      if (h != TT) {
         exit(91);
      }
      int W = floor(0.00001+log(3*NN)/log(2));
      double alpha = 2 - (double)moves/W;
      if (alpha < worst) worst = alpha;
      if( moves == 48 )
      printf("HC com N: %d, resposta igual: %d, chamadas igual: %d\n", NN, TT, moves);
      max_moves = max(max_moves, moves);
       // 1 means failure
      if ( NN <= 500 && moves > 500 ) exit(93);
      if ( NN <= 500 && moves > 18 ) sub2=1; 
      if ( NN <= 500 && moves > 16 ) sub3=1;
      OK++;
   }
   printf("Numero maximo de movimentos: %d\n", max_moves);
   if (!sub1) printf("OK 1\n");
   if (!sub2) printf("OK 2\n");
   if (!sub3) printf("OK 3\n");
   if (worst > 0) printf("OK 4 alpha %0.2lf\n",worst);
   return 0;
}
