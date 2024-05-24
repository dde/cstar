/* PROGRAM Summation of random float numbers */
#include <stdlib.h>
#define n 10
float values[n+1] = {0.0, 9.820, 4.250, 4.330, 6.630, 7.500, 1.110, 8.530, 7.610, 8.810, 4.310};
int i;

main() {
  cout.precision(4);
  /* generate n random float numbers between 0 and 10 */
  for (i = 1; i <= n; i++) {
    /*
    values[i] = (rand() % 1000)/100.0;
    */
    cout << "values[" << i << "] = " << values[i] << endl;
  }
  float sum = 0.0;
  for (i = 1; i <= n; i++)
  {
    cout << "i-sum = " << sum << " + " << values[i] << endl;
    sum += values[i];
  }
  cout << "sum = " << sum << endl;
}
