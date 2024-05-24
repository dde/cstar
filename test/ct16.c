#include <stdlib.h>
#define AREAS 10
char *cpa[AREAS];
int main() {
  int ix;
  for (ix = 0; ix < AREAS; ++ix)
  {
    cpa[ix] = (char *)calloc(1, 8 + 8 * ix);
  }
  for (ix = 0; ix < AREAS; ix += 2)
  {
    free(cpa[ix]);
  }
  for (ix = 1; ix < AREAS; ix += 2)
  {
    free(cpa[ix]);
  }
  return 0;
}
