/* test character functions */
#include <ctype.h>
int main()
{
  int ix;
  char ch;
  for (ix = 0; ix < 128; ++ix)
  {
    ch = (char)ix;
    if (ix < 32 || ix == 127)
      cout << ix << ": ";
    else
      cout << ch;
    if (isalnum(ch))
      cout << " isalnum";
    if (isalpha(ch))
      cout << " isalpha";
    if (iscntrl(ch))
      cout << " iscntrl";
    if (isdigit(ch))
      cout << " isdigit";
    if (isgraph(ch))
      cout << " isgraph";
    if (islower(ch))
      cout << " islower";
    if (isprint(ch))
      cout << " isprint";
    if (ispunct(ch))
      cout << " ispunct";
    if (isspace(ch))
      cout << " isspace";
    if (isupper(ch))
      cout << " isupper";
    if (isxdigit(ch))
      cout << " isxdigit";
    cout << endl;
  }
  return 0;
}
