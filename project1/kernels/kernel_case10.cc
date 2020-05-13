#include "../run.h"
void kernel_case10(float (&B)[10][10], float (&A)[8][8]) {
  for(int i = -128; i < -128 + 256; ++i){
    for(int j = -128; j < -128 + 256; ++j){
      if ((((((((0 <= i && i < 8) && 0 <= (i + 1)) && (i + 1) < 10) && 0 <= (i + 2)) && (i + 2) < 10) && 0 <= j) && j < 8)) {
        A[i][j] =((B[i][j] + (B[(i + 1)][j] + B[(i + 2)][j])) / 3);
      } else {
        A[i][j] =A[i][j];
      }
    }
  }
}
