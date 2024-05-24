int main()
{
  int ix;
  ix = 0;
  do
  {
    if (ix == 0)
      cout << "Hello ix == 0" << endl;
    else
      cout << "Hello ix != 0" << endl;
    ix = ix + 1;
  }
  while (ix < 2);
}
