#include "../run.h"
void kernel_case11(float (&B)[16], float (&C)[32], float (&D)[12], float (&E)[24], float (&A)[8]) {
  float temp[8] = {};
  for(int i = 0; i < 0 + 8; ++i){
    if ((0 <= i && i < 8)) {
      temp[i] =0;
    } else {
      A[i] =A[i];
    }
    if ((0 <= i && i < 8)) {
      temp[i] =(temp[i] + A[i]);
    } else {
      A[i] =A[i];
    }
    for(int j = 0; j < 0 + 16; ++j){
      for(int k = 0; k < 0 + 32; ++k){
        if ((((0 <= j && j < 16) && 0 <= k) && k < 32)) {
          temp[i] =(temp[i] - (B[j] * C[k]));
        } else {
          A[i] =A[i];
        }
      }
    }
    for(int p = 0; p < 0 + 12; ++p){
      for(int q = 0; q < 0 + 24; ++q){
        if ((((0 <= p && p < 12) && 0 <= q) && q < 24)) {
          temp[i] =(temp[i] + (D[p] - E[q]));
        } else {
          A[i] =A[i];
        }
      }
    }
    if ((0 <= i && i < 8)) {
      A[i] =temp[i];
    } else {
      A[i] =A[i];
    }
  }
}
