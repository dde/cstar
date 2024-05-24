/* PROGRAM MatrixMultiplySequential */ 
#include <stdlib.h>
#include <math.h>
#define M 4
#define N 4
#define P 4
float A[M+1][N+1] = {
  {0.0, 11.230000,  51.630000,  44.940000,  52.660000},
  {0.0, 11.230000,  51.630000,  44.940000,  52.660000},
  {0.0, 68.130000,  93.070000,  35.900000,  57.590000},
  {0.0, 40.590000,  80.250000,  83.770000,  22.410000},
  {0.0, 46.960000,  86.900000,  49.290000,  40.950000}};
float B[N+1][P+1] = {
  {0.0, 61.800000, 43.990000, 93.480000, 7.7700000},
  {0.0, 61.800000, 43.990000, 93.480000, 7.7700000},
  {0.0, 82.710000, 36.320000, 98.920000, 56.410000},
  {0.0, 21.260000, 56.780000, 50.130000, 75.390000},
  {0.0, 39.370000, 26.120000, 93.820000, 32.860000}};
float C[M+1][P+1]; 

float VectorProduct(int rw, int cl) {
  float sum;
  int k;
  sum = 0.0;
  for (k = 1; k <= N; ++k)
  {
    sum = sum + A[rw][k] * B[k][cl];
  }
  /*
  C[rw][cl] = sum;
  */
  return sum;
}

void printMatrix(float p[N+1][N+1]) {
  int l, m;
  for (l = 1; l <= N; l++) {
    for (m = 1; m <= N; m++) 
      cout << p[l][m] << " ";
    cout << "\n";
  }
  cout << "\n";
}

int i, j; 
int main() {
  cout.precision(9); /* use 8 significant digits for float output */
  /*
  for (i = 1; i <= N; i++)
    for (j = 1; j <= N; j++) {
      a[i][j] = (rand() % 10000)/100.0;
      b[i][j] = (rand() % 10000)/100.0;
    }
  */
  for (i = 1; i <= N; i++)
    for (j = 1; j <= N; j++) 
      /*compute row i of A times column j of B*/
      C[i][j] = VectorProduct(i, j);
  
  cout << "A = " << "\n";
  printMatrix(A);
  cout << "\n"; 
  
  cout << "B = " << "\n"; 
  printMatrix(B); 
  cout << "\n"; 
  
  cout << "C = " << "\n";  
  printMatrix(C);
  cout << "\n"; 
  return 0;
}
