#include <stdio.h>
#include <stdlib.h>

int main (int argc, char** argv) {
  int h, i, j, k = 3, n, m, seed = 123456;

  if (argc > 1) {
    n = atoi (argv[1]); while (n > (1 << k)) k++; }
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

  int **xor;
  xor = (int**) malloc (sizeof (int*) * m);
  for (i = 0; i < m; i++) {
    xor[i] = (int*) malloc (sizeof(int) * m);
    for (j = 0; j < m; j++) xor[i][j] = 0; }

  int var = m;
  for (h = 0; h < n; h++)
    for (i = h + 1; i < n; i++)
      for (j = 0; j < k; j++)
        if (hash[h][j] != hash[i][j]) {
          int a = hash[h][j], b = hash[i][j];
          if (xor[a][b] == 0)
            xor[a][b] = xor[b][a] = ++var;
        }

  printf ("p cnf %i %i\n", var,  n * (n - 1)/2 + 2 * (var - m));

  for (h = 0; h < n; h++)
    for (i = h + 1; i < n; i++) {
      for (j = 0; j < k; j++)
        if (hash[h][j] != hash[i][j])
          printf ("%i ", xor[ hash[h][j] ][ hash[i][j] ]);
      printf ("0\n"); }

  for (i = 0; i < m; i++)
    for (j = i + 1; j < m; j++)
      if (xor[i][j]) {
          printf ("%i %i -%i 0\n",   i + 1, j + 1, xor[i][j]);
          printf ("-%i -%i -%i 0\n", i + 1, j + 1, xor[i][j]);
      }
}
