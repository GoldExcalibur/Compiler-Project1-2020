#include "../run.h"
void kernel_case4(float (&B)[16][32], float (&C)[32][32], float (&A)[16][32]) {
  for(int i = -128; i < -128 + 256; ++i){
    for(int j = -128; j < -128 + 256; ++j){
      for(int k = -128; k < -128 + 256; ++k){
        if ((((((0 <= i && i < 16) && 0 <= j) && j < 32) && 0 <= k) && k < 32)) {
          A[i][j] =(A[i][j] + (B[i][k] * C[k][j]));
        } else {
          A[i][j] =A[i][j];
        }
      }
    }
  }
}
