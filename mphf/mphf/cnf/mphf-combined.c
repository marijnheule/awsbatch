#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

int *removeDups(int *x, int k) {
  int i, j;

  for(i = 0; i < k-1; i++) {
    for(j = i+1; j < k; j++) {
      if(x[i] == x[j]) { //Duplicate literal
        x[j] = x[k-1];
        x[k-1] = 0;
        j--; k--;
      }
    }
  }
}

int isTautology(int *x, int k){
  int i, j;
  for(i = 0; i < k-1; i++) {
    for(j = i+1; j < k; j++) {
      if(x[i] == -x[j]) {  //Tautology
        return 1;
      }
    }
  }
  return 0;
}

void compare(int *x, int *y, int k) {
  int i, j;
  int clause[k*2];
  for(i = 0; i < (1<<k); i++) {
    for(j = 0; j < k; j++) {
      int pos = (i>>j) & 1;
      if(pos) {
        clause[j*2] = x[j];
        clause[j*2+1] = y[j];
      } else {
        clause[j*2] = -x[j];
        clause[j*2+1] = -y[j];
      }
    }

    /*
    printf("c ");
    for(j = 0; j < k*2; j++) {
      printf("%i ", clause[j]);
    }
    printf("\n");
    */

    if(!isTautology(clause, k*2)) {
      removeDups(clause, k*2);
      for(j = 0; j < k*2; j++) {
        if(clause[j] == 0) break;
        printf("%i ", clause[j]);
      }

      printf("0\n");
    }
  }
}

int countTautologies(int *x, int *y, int k) {
  int i, j;
  int clause[k*2];
  int numTautolgies = 0;

  for(i = 0; i < (1<<k); i++) {
    for(j = 0; j < k; j++) {
      int pos = (i>>j) & 1;
      if(pos) {
        clause[j*2] = x[j];
        clause[j*2+1] = y[j];
      } else {
        clause[j*2] = -x[j];
        clause[j*2+1] = -y[j];
      }
    }

    if(isTautology(clause, k*2)) {
      numTautolgies++;
    }
  }

  return numTautolgies;
}


int main (int argc, char** argv) {
  int h, i, j, n, m;
  int k = 3;

  struct timeval tv1;
  struct timezone tzp1;
  gettimeofday(&tv1, &tzp1);
  int seed = ((tv1.tv_sec & 0177) * 1000000) + tv1.tv_usec;

  if (argc > 1) {
    n = atoi (argv[1]); while (n > (1<<k)) k++; }
  else {
    printf ("c use as follows: ./mphf-cnf #ELEMENTS #VARIABLES [SEED]\n"); exit (0); }

  if (argc > 2) {
    m = atoi (argv[2]); }
  else {
    printf ("c use as follows: ./mphf-cnf #ELEMENTS #VARIABLES [SEED]\n"); exit (0); }

  if (argc > 3) {
    seed = atoi (argv[3]); }

  fprintf(stderr, "random seed = %d\n", seed);
  srand(seed);

  int **hash;
  hash = (int**) malloc (sizeof (int*) * n);
  for (i = 0; i < n; i++) {
    hash[i] = (int*) malloc (sizeof(int) * k);
    for (j = 0; j < k; j++) hash[i][j] = (rand () % m) + 1; }

  int numTautolgies = 0;
  for (h = 0; h < n; h++) {
    for (i = h + 1; i < n; i++) {
      numTautolgies += countTautologies(hash[h], hash[i], k);
    }
  }

  printf ("p cnf %i %i\n", m + n * n, n * (n * k + 1) + (n * (n - 1)/2) * (1<<k) - numTautolgies);

  for (h = 0; h < n; h++) {
    for (i = h + 1; i < n; i++) {
      compare(hash[h], hash[i], k);
    }
  }

  int var = m;
  for (h = 0; h < n; h++) {
    for (i = 1; i <= n; i++) printf ("%i ", var + i);
    printf ("0\n");
    for (i = 1; i <= n; i++)
      for (j = 0; j < k; j++) {
        if (((h >> j) & 1) == 0) printf ("-");
        printf ("%i -%i 0\n", hash[i-1][j], var + i);
      }
    var += n; }

}
