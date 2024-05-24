/* PROGRAM Summation of float numbers */
#define n 10
float values[n+1] = {1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9.1, 10.2, 11.3};
int i;

main() {
  float sum = 0.0;
  cout.precision(4);
  for (i = 1; i <= n; i++)
  {
    cout << "i-sum = " << sum << " + " << values[i] << endl;
    sum += values[i];
  }
  cout << "sum = " << sum << endl;
}
