#include "grader.h"
#include "hottercolder.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static int moves, TT, NN, prev = -1;
int Guess(int x){
   int r;
   if (prev == -1 || abs(x-TT) == abs(prev-TT)) r = 0;
   else if (abs(x-TT) > abs(prev-TT)) r = -1;
   else r = 1;
   prev = x;
   if (x < 1 || x > NN) exit(92);
   moves++;
   return r;
}

int main(){
   int n=0,i,t,OK=0,sub1=0,sub2=0,sub3=0;
   double worst = 999999;
   while (2 == scanf("%d%d",&NN,&TT)) {
      if (NN > n) n = NN;
      prev = -1;
      moves = 0;
      int h = HC(NN);
      if (h != TT) {
         exit(91);
      }
      int W = floor(0.00001+log(3*NN)/log(2));
      double alpha = 2 - (double)moves/W;
      if (alpha < worst) worst = alpha;
       // 1 means failure
      if ( NN <= 500 && moves > 500 ) exit(93);
      if ( NN <= 500 && moves > 18 ) sub2=1; 
      if ( NN <= 500 && moves > 16 ) sub3=1;
      OK++;
   }
   if (!sub1) printf("OK 1\n");
   if (!sub2) printf("OK 2\n");
   if (!sub3) printf("OK 3\n");
   if (worst > 0) printf("OK 4 alpha %0.2lf\n",worst);
   return 0;
}
