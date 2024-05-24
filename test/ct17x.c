/* Sequential Back Substitution */
#include <stdlib.h>
#include <math.h>
#define UNKNOWNS 10    /* number of unknowns/equations */
float  equations[UNKNOWNS][UNKNOWNS+1];
float  upperTri[UNKNOWNS][UNKNOWNS+1];
float  xx[1][UNKNOWNS];
void dispMat(float fm[][UNKNOWNS+1], int d1, int d2) {
  int i, j;
  for (i = 0; i < d1; ++i)
  {
    cout.width(1);
    cout << fm[i][0];
    for (j = 1; j < d2; ++j)
    {
      cout.width(1);
      cout << ", " << fm[i][j];
    }
    cout << endl;
  }
}
void dispMatR(float fm[][UNKNOWNS+1], int d1, int d2) {
  int i, j;
  for (i = d1 - 1; i >= 0; --i)
  {
    cout.width(1);
    cout << fm[i][d2 - 2];
    for (j = d2 - 3; j >= 0; --j)
    {
      cout.width(1);
      cout << ", " << fm[i][j];
    }
    cout << endl;
  }
  cout << endl;
  cout.width(1);
  cout << fm[d1 - 1][d2 - 1];
  for (i = d1 - 2; i >= 0; --i)
  {
    cout.width(1);
    cout << ", " << fm[i][d2 - 1];
  }
  cout << endl;
}

void readArray(float aa[][UNKNOWNS+1], int d1, int d2) {
  int i, j;
  /*Initialize array values*/
  for (i = 0; i < d1; ++i)
  {
    for (j = 0; j < d2; ++j)
      cin >> aa[i][j];
  }
}
/* assumes upper triangular result from gaussian elimination */
/*Solve equation i for value of xi */
/*
for (i = 1; i <= n; ++i)
{
  sum = 0;
  for (j = 1; j <= i - 1; ++i)
  {
    sum = sum + A[i][j] * x[j];
  }
  x[i] = (B[i] - sum) / A[i][i];
}
*/
void backSub(float eq[][UNKNOWNS+1])
{
  int b, d1;
  int i, j;
  float sum;
  b = UNKNOWNS;
  d1 = b - 1;
  for (i = d1; i >= 0; --i)
  {
    sum = 0.0;
    for (j = d1; j > i; --j)
    {
      sum = sum + eq[i][j] * xx[0][j];
    }
    xx[0][i] = (eq[i][b] - sum) / eq[i][i];
  }
}
void xchangeRows(float eq[][UNKNOWNS+1], int d1, int d2) {
  int i;
  float ex;
  if (d1 == d2)
    return;
  for (i = 0; i < UNKNOWNS + 1; ++i)
  {
    ex = eq[d1][i];
    eq[d1][i] = eq[d2][i];
    eq[d2][i] = ex;
  }
}
void elimVar(float eq[][UNKNOWNS+1], int rw, int rw1, int cl)
{
  float mult;
  if (0.0 == eq[rw][cl])
  {
    cout << "linear independence failure at row " << rw << endl;
    exit(1);
    return;
  }
  if (0.0 == eq[rw1][cl])
    return;
  mult = -eq[rw][cl] / eq[rw1][cl];
  for (; cl < UNKNOWNS + 1; ++cl)
  {
    eq[rw1][cl] = mult * eq[rw1][cl] + eq[rw][cl];
  }
}
int maxInCol(float eq[][UNKNOWNS+1], int col)
{
  float max;
  int j, rw;
  max = eq[col][col];
  j = col;
  for (rw = col; rw < UNKNOWNS; ++rw)
  {
    if (max < eq[rw][col])
    {
      max = eq[rw][col];
      j = rw;
    }
  }
  /*
  cout << "max " << max << " in [" << j << "," << col << "]" << endl;
  */
  return j;
}
void gauss(float eq[][UNKNOWNS + 1])
{
  int k, i, j;
  for (i = 0; i < UNKNOWNS; ++i)
  {
    /* start by finding max in column i */
    k = maxInCol(eq, i);
    if (0.0 == eq[k][i])
    {
      xchangeRows(eq, i + 1, k);
      continue;
    }
    xchangeRows(eq, i, k);
    for (j = i + 1; j < UNKNOWNS; ++j)
      elimVar(eq, i, j, i);
  }
}
void verify(float ut[][UNKNOWNS + 1])
{
  float sum, dif;
  int i, j;
  for (i = 0; i < UNKNOWNS; ++i)
  {
    sum = 0.0;
    for (j = 0; j < UNKNOWNS; ++j)
    {
      sum += ut[i][j] * xx[0][j];
    }
    dif = fabs(sum - ut[i][UNKNOWNS]);
    if (0.1 < dif)
    {
      cout << "solution failure: row " << i << endl;
    }
  }
}
int main( ) {
  int k, i, j;
  readArray(equations, UNKNOWNS, UNKNOWNS+1);
  cout.precision(6);
  cout << "input matrix:" << endl;
  dispMat(equations, UNKNOWNS, UNKNOWNS+1);
  upperTri = equations;
  gauss(upperTri);
  backSub(upperTri);
  verify(equations);
  cout << "output matrix:" << endl;
  dispMatR(upperTri, UNKNOWNS, UNKNOWNS+1);
  cout << "solution:" << endl;
  dispMat(xx, 1, UNKNOWNS);
} 
