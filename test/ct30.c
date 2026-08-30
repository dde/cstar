#define PP 3
int main()
{
  int ix, jx, ct = PP;
  cout << "main start" << endl;
  cout << "without closure" << endl;
  for (ix = 0; ix < ct; ++ix)
  {
    fork
    {
      cout << "process " << self << endl;
      cout << " ix " << ix << endl;
    }
  }
  for (jx = 0; jx < ct; ++jx)
    join;
  cout << "with closure" << endl;
  for (ix = 0; ix < ct; ++ix)
  {
    fork [jx, ix, ct]
    {
      cout << "process " << self << endl;
      cout << " ix " << ix << endl;
    }
  }
  for (jx = 0; jx < ct; ++jx)
    join;
  cout << "main end" << endl;
  return 0;
}
 
