int main()
{
  int ix, sum;
  int ia[4];
  ia[0] = 0;
  sum = 0;
  for (ix = 1; ix < 4; ++ix)
  {
    ia[ix] = ix;
    cout << "ia[" << ix << "]=" << ia[ix] << endl;
    sum = sum + ia[ix];
  }
  cout << "sum=" << sum << endl;
}
