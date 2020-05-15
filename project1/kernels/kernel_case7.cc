#include "../run.h"
void kernel_case7(float (&A)[32][16], float (&B)[16][32]) {
  float temp[16][32];
  for(int i = -64; i < -64 + 128; ++i){
    for(int j = -64; j < -64 + 128; ++j){
      if ((((0 <= i && i < 16) && 0 <= j) && j < 32)) {
        temp[i][j] =0;
      } else {
        B[i][j] =B[i][j];
      }
      if ((((0 <= i && i < 16) && 0 <= j) && j < 32)) {
        temp[i][j] =(temp[i][j] + A[j][i]);
      } else {
        B[i][j] =B[i][j];
      }
      if ((((0 <= i && i < 16) && 0 <= j) && j < 32)) {
        B[i][j] =temp[i][j];
      } else {
        B[i][j] =B[i][j];
      }
    }
  }
}
