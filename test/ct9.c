int main()
{
  int ix, jx;
  ix = 0;
  jx = 1;
  do
  {
    if (ix % 2 == 0)
      if (jx % 2 == 0)
        cout << "Hello ix, jx % 2 == 0" << endl;
      else
        cout << "Hello ix % 2 == 0, jx % 2 != 0" << endl;
    else
      if (jx % 2 == 1)
        cout << "Hello ix, jx % 2 == 1" << endl;
      else
        cout << "Hello ix % 2 != 0, jx % 2 != 1" << endl;
    ix = ix + 1;
    jx = jx - 1;
  }
  while (ix < 2);
}
