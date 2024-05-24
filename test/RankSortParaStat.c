/* PROGRAM RankSortParallel */
/* Figure 2.3 */
#include <stdlib.h>
#define N 100
int values[N+1] = {
  2017, 4365, 9751, 6303, 2247,
  7630, 1550, 1601, 7608, 5710,
  4998, 7460, 3657, 5793, 4707,
  2540, 9125, 6489, 9437, 8530,
  7730, 6164, 5927, 8752, 8959,
  9380, 9455, 6314, 4480, 2502,
  9404, 1410, 4242, 7713, 2585,
  9366, 6696, 4892, 9097, 1918,
  1291, 5156, 7547, 1218, 2333,
  4700, 5767, 6811, 6585, 3816,
  4180, 6560, 3542, 9542, 9500,
  8761, 1807, 4310, 3554, 2654,
  2715, 8908, 5972, 2665, 2813,
  2635, 9400, 1948, 5929, 2179,
  6831, 8431, 8629, 3500, 8590,
  9603, 4054, 2941, 8517, 5313,
  3202, 6545, 7925, 4649, 5207,
  6016, 3899, 9735, 3705, 8180,
  9850, 9260, 9596, 9295, 8196,
  9220, 2341, 2367, 7568, 5836
};
int final[N+1];
int i;

void putinPlace( int src ) {
  int testval, j, rank;

  testval = values[src];
  j = src;   /* j moves through the whole array */
  rank = 1;  /* position of the first number in the arrays */
  do {
    j = j % N + 1; /* j moves to the next circular position */
    if (testval > values[j] ||
       (testval == values[j] && src > j)) 
       rank = rank + 1;
  } while (j != src);
  final[rank] = testval;  /*put into position*/
}

void display(int val[]) {
  int i;
  for (i = 1; i <= N; i++) {
    cout << val[i] << " "; 
    if (i % 10 == 0)
      cout << endl;
  }
  if (i % 10 != 1)
    cout << endl;
}

main() {
  /* display(values); */
  forall  i = 1 to N grouping 10 do
    putinPlace(i);  /* put values[i] in place */
  display(final);
}
