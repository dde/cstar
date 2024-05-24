
#include <stdlib.h>
#include <string.h>
#define ASZ 4
void strdisp(char *cp)
{
  char ch;
  int ix;
  ix = 0;
  while (*(cp + ix) != '\0')
  {
    ch = *(cp + ix);
    cout << ch; 
    ++ix;
  }
}
int main()
{
  /*
   * strcat strchr strcpy strcmp strlen strstr
   * malloc calloc realloc free
  */
  char *a1, *a2;
  char s1[2];
  char *a3[ASZ];
  int ix, jx, al, fr;
  int ln = 2;
  char cx;
  boolean b1;
  s1[0] = '\0';
  s1[1] = '\0';
  a3[0] = "YZ";
  a3[1] = "QRS";
  a3[2] = "IJKL";
  a3[3] = "ABCDE";
  a1 = (char *)malloc(ln);
  al += 1;
  *a1 = '\0';
  for (cx = 'A'; cx <= 'Z'; ++cx)
  {
    s1[0] = cx;
    strcat(a1, s1);
    strdisp(a1);
    ix = strlen(a1);
    cout << " length " << ix;
    cout << endl;
    a2 = calloc(1, ln);
    al += 1;
    strcpy(a2, a1);
    ++ln;
    a2 = realloc(a2, ln);
    free(a1);
    fr += 1;
    a1 = a2;
  }
  b1 = true;
  for (cx = 'A'; cx <= 'Z'; ++cx)
  {
    a2 = strchr(a1, cx);
    if (a2 == null || *a2 != cx)
    {
      cout << "strchr failed " << *a2 << " != " << cx << endl;
      b1 = false;
    }
  }
  if (b1)
     cout << "strchr succeeded " << endl;
  for (ix = 0; ix < ASZ; ++ix)
  {
    a2 = strstr(a1, a3[ix]);
    strdisp(a3[ix]);
    if (a1 != null)
    {
      jx = (a2 - a1);
      cout << " found at " << jx << endl;
      jx = strlen(a3[ix]);
      cx = *(a2 + jx);
      *(a2 + jx) = '\0';
      if (0 != strcmp(a3[ix], a2))
        cout << "strcmp failed" << endl;
      else
        cout << "strcmp succeeded" << endl;
      *(a2 + jx) = cx;
    }
    else
      cout << " not found" << endl;
  }
  free(a1);
  fr += 1;
  cout << "allocs " << al << ", frees " << fr << endl;
  return 0;
}
