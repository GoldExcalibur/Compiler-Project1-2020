#include "../run.h"
void kernel_case7(float (&A)[32][16], float (&B)[16][32]) {
  for(int i = -128; i < -128 + 256; ++i){
    for(int j = -128; j < -128 + 256; ++j){
      if ((((0 <= i && i < 16) && 0 <= j) && j < 32)) {
        B[i][j] =A[j][i];
      } else {
        B[i][j] =B[i][j];
      }
    }
  }
}
