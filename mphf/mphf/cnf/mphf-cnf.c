#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char** argv) {
  int h, i, j, k, n, m, seed = 123456;

  if (argc > 1) {
    n = atoi (argv[1]); k = log2(n); }
  else {
    printf ("c use as follows: ./mphf-cnf #ELEMENTS #VARIABLES [SEED]\n"); exit (0); }

  if (argc > 2) {
    m = atoi (argv[2]); }
  else {
    printf ("c use as follows: ./mphf-cnf #ELEMENTS #VARIABLES [SEED]\n"); exit (0); }

  if (argc > 3) {
    seed = atoi (argv[3]); }
  srand (seed);

  int **hash;
  hash = (int**) malloc (sizeof (int*) * n);
  for (i = 0; i < n; i++) {
    hash[i] = (int*) malloc (sizeof(int) * k);
    for (j = 0; j < k; j++) hash[i][j] = rand () % m; }

  int match = 0;
  for (h = 0; h < n; h++)
    for (i = h + 1; i < n; i++)
      for (j = 0; j < k; j++)
        if (hash[h][j] == hash[i][j]) match++;

  int pairs = n * (n-1) / 2;
  int xors  = pairs * k - match;

  printf ("p cnf %i %i\n", m + pairs * k, pairs + xors * 4 + match);

  int tmp = m + 1;
  for (h = 0; h < n; h++)
    for (i = h + 1; i < n; i++) {
      for (j = 0; j < k; j++) {
        printf ("%i ", tmp + j); }
      printf ("0\n");
      for (j = 0; j < k; j++) {
        if (hash[h][j] == hash[i][j]) {
          printf ("-%i 0\n", tmp + j); }
        else {
          printf ("%i %i -%i 0\n", hash[h][j] + 1, hash[i][j] + 1, tmp + j);
          printf ("%i -%i %i 0\n", hash[h][j] + 1, hash[i][j] + 1, tmp + j);
          printf ("-%i %i %i 0\n", hash[h][j] + 1, hash[i][j] + 1, tmp + j);
          printf ("-%i -%i -%i 0\n", hash[h][j] + 1, hash[i][j] + 1, tmp + j);
        }
      }
    tmp += k; }

}
