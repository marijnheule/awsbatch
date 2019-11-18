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

  int *used;
  used = (int *) malloc (sizeof (int) * m);
  for (i = 0; i < m; i++) used[i] = 0;

  int **hash;
  hash = (int**) malloc (sizeof (int*) * n);
  for (i = 0; i < n; i++) {
    hash[i] = (int*) malloc (sizeof(int) * k);
    for (j = 0; j < k; j++) {
      int r = rand () % m;
      hash[i][j] = r;
      used[r]++; } }

  int nCls = 0;
  for (i = 0; i < m; i++)
    if (!used[i])
      nCls++;

  nCls += n * (n * k + 1);

  printf ("p cnf %i %i\n", m + n * n, nCls);

  for (i = 0; i < m; i++)
    if (!used[i])
      printf ("-%i 0\n", i + 1);

  int l = 0, v = 0;
  if (n != (1<<k)) { v = 1<<(k-1); l = n - v; }

  int var = m;
  for (h = 0; h < n; h++) {
    int b = k; if ((h >= l) && (h < v)) b--;
    for (i = 1; i <= n; i++) printf ("%i ", var + i);
    printf ("0\n");
    for (i = 1; i <= n; i++) {
      for (j = 0; j < b; j++) {
        if (((h >> j) & 1)) printf ("-");
        printf ("%i -%i 0\n", hash[i-1][j] + 1, var + i);
      } }
    var += n; }
}
