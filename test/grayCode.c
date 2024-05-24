/* generate Grap codes recursively */
#include <stdlib.h>
#include <math.h>
/* set the order of the desired Graycode, max 10 */
#define GC_ORDER 6
/**
 * Generate a gray code of the request order in a reference array parameter
 */
int *sub1(int *arr, int sb) {
  return (arr + sb);
}
char *sub1c(char *arr, int sb) {
  return (arr + sb);
}
int grayCode(int order, int **rarrp) {
  int i, j, sz, sz2;
  int *r1, *rtn;
  if (order <= 1)
  {
    rtn = calloc(2, 2);
    *sub1(rtn, 1) = 1;
    sz2 = 2;
  }
  else
  {
    sz = grayCode(order - 1, &r1);
    sz2 = 2 * sz;
    rtn = calloc(sz2, 2);
    for (i = 0; i < sz; ++i)
    {
      *sub1(rtn, i) = *sub1(r1, i);
    }
    for (j = sz - 1, i = sz; i < sz2; ++i, --j)
    {
      *sub1(rtn, i) = *sub1(r1, j) + sz;
    }
    free(r1);
  }
  *rarrp = rtn;
  return sz2;
}
void displayGray(int sz, int *arr) {
 int i, j, val, order;
 int lc, per_line = 10;
 char *ch;
 order = (int)(log((float)sz) / log(2.0));
 /*
 cout << "size " << sz << ", order " << order << endl;
 */
 cout.width(1);
 cout << " Order " << order << " Graycode" << endl;
 lc = 0;
 ch = calloc(order, 1);
 for (i = 0; i < sz; ++i)
 {
    for (j = 0; j < order; ++j)
      *sub1c(ch, j) = '0';
    cout << ' '; 
    j = 0;
    val = *sub1(arr, i);
    /*
    cout << "val " << val << endl;
    */
    while (val != 0)
    {
      if (val % 2 == 1)
        *sub1c(ch, j) = '1';
      ++j;
      val /= 2;
    }
    if (lc >= per_line)
    {
      cout << endl << ' ';;
      lc = 0;
    }
    for (j = order - 1; j >= 0; --j)
      cout << *sub1c(ch, j);
    ++lc;
 }
 cout << endl;
 free(ch);
}
int main() {
  int sz, *arr;
  if (GC_ORDER > 10)
  {
    cout << "maximum supported Graycode order is 10" << endl;
    return 1;
  }
  sz = grayCode(GC_ORDER, &arr);
  displayGray(sz, arr);
  free(arr);
  return 0;
}
