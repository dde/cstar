int main()
{
  int ix, jx;
  ix = 0;
  jx = 1;
  if (ix == 0)
    if (jx == 0)
      cout << "Hello ix, jx == 0" << endl;
    else
      cout << "Hello ix == 0, jx != 0" << endl;
  else
    if (jx == 1)
      cout << "Hello ix, jx == 1" << endl;
    else
      cout << "Hello ix != 0, jx != 1" << endl;
  return 0;
}
