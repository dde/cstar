/* PROGRAM 2D Summation of random float numbers */
#include <stdlib.h>
#define m 2
#define n 5
float values[2+1][n+1];

main() {
  int i, j;
  cout.precision(4);
  /* generate mxn random float numbers between 0 and 10 */
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      values[i][j] = (rand() % 1000)/100.0; /* generating random int in [0, 10) */
      cout << "values[" << i << "][" << j << "] = " << values[i][j] << endl;
    }
  }
  float sum = 0.0;
  i = 1;
  while (i <= m)
  {
    j = 1;
    while (j <= n)
    {
      cout << "i-sum = " << sum << " + " << values[i][j] << endl;
      sum += values[i][j];
      ++j;
    }
    ++i;
  }
  cout << "sum = " << sum << endl;
}
