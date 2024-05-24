/* PROGRAM 2D Summation of random float numbers */
#include <stdlib.h>
#define m 2
#define n 5
float values[m+1][n+1] = {{0.0, 5.930, 0.8400, 2.5, 5.930, 9.010},
{0.0, 0.5900, 9.330, 6.4, 3.660, 1.580},
{0.0, 6.190, 2.590, 7.9, 7.210, 6.390}};

main() {
  int i, j;
  cout.precision(4);
  /* generate mxn random float numbers between 0 and 10 */
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      /* generating random int in [0, 10) */
      /*
      values[i][j] = (rand() % 1000)/100.0;
      */
      cout << "values[" << i << "][" << j << "] = " << values[i][j] << endl;
    }
  }
  float sum = 0.0;
  for (i = 1; i <= m; i++)
    for (j = 1; j <= n; j++)
    {
      cout << "i-sum = " << sum << " + " << values[i][j] << endl;
      sum += values[i][j];
    }
  cout << "sum = " << sum << endl;
}
