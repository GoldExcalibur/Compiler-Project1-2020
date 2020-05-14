#include "../run.h"
void kernel_case1(float (&A)[32][16]) {
  for(int i = -128; i < -128 + 256; ++i){
    for(int j = -128; j < -128 + 256; ++j){
      if ((((0 <= i && i < 32) && 0 <= j) && j < 16)) {
        A[i][j] =2;
      } else {
        A[i][j] =A[i][j];
      }
    }
  }
}
