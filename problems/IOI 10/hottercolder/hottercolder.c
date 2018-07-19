#include "grader.h"

int HC(int N){
   int g = Guess(1);
   int h = Guess(N);
   if (g == 0) return N/2;
   if (g < 0) return N/4;
   if (g > 0) return 3*N/4;
}
