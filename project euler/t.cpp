#include <stdio.h>

#define N 1000000000000000000LL
#define M 20092010
#define D 2000

long long int ax[4][D*2-1];

void mult(int s0, int s1, int t);

int main(int argc, char **argv) {
  long long int x;
  long long int answer;

  int i;
  int src, trg;
  int src_g, trg_g;

  src = 0;
  trg = 1;
  src_g = 2;
  trg_g = 3;

  ax[src_g][0] = 1;

  x = N/2048;
  ax[src][48] = 1;
  ax[src][49] = 1;
  // x = N;
  // ax[src][1] = 1;

  while (1) {
    if (x%2) {
      mult(src, src_g, trg_g);
      
      src_g = 5 - src_g; // xchange
      trg_g = 5 - trg_g;
    }

    x /= 2;
    if (!x)
      break;

    mult (src, src, trg);
    src = 1 - src; // xchange
    trg = 1 - trg;
  }

  answer = 0;
  for (i=0; i<D; i++)
    answer += ax[src_g][i];
  answer %= M;
  printf ("answer: %lld\n", answer);
}

// s0*s1 -> t
void mult(int s0, int s1, int t) {
  int i, j;

  for (i=0; i<(D<<1)-1; i++)
    ax[t][i] = 0;

  for (i=0; i<D; i++)
    for (j=0; j<D; j++)
      ax[t][i+j] += ax[s0][i] * ax[s1][j];

  for (i=D; i<(D<<1)-1; i++) {
    ax[t][i-D] += ax[t][i];
    ax[t][i-D+1] += ax[t][i];
  }

  for (i=0; i<D; i++)
    ax[t][i] %= M;
}