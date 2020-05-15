#include "../run.h"
void kernel_case1(float (&A)[32][16]) {
  float temp[32][16];
  for(int i = -64; i < -64 + 128; ++i){
    for(int j = -64; j < -64 + 128; ++j){
      if ((((0 <= i && i < 32) && 0 <= j) && j < 16)) {
        temp[i][j] =0;
      } else {
        A[i][j] =A[i][j];
      }
      if ((((0 <= i && i < 32) && 0 <= j) && j < 16)) {
        temp[i][j] =(temp[i][j] + 2);
      } else {
        A[i][j] =A[i][j];
      }
      if ((((0 <= i && i < 32) && 0 <= j) && j < 16)) {
        A[i][j] =temp[i][j];
      } else {
        A[i][j] =A[i][j];
      }
    }
  }
}
