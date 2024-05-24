#include <stdlib.h>
int main()
{
  div_t result;
  result = div(160, 43);
  cout << "160 / 43 = quot:" << result.quot << " rem:" << result.rem << endl;
}
