#define SZ 1
void polyMult()
{
  return;
}
int process(int sz1, int sz2)
{
  int i, j;
  cout << "p1 size:" << sz1 << ", p2 size:" << sz2 << endl;
  forall i = 0 to sz1 - 1 do
    forall j = 0 to sz2 - 1 do
    {
      cout << "starting id " << myid << "," << i << "," << j << endl;
      polyMult();
    }
  return sz1 + sz2;
}
int pl0[3][2] = {{1, 1}, {2, 2}, {1, 3}};
int pl1[2][2] = {{1, 0}, {1, 2}};
int pl2[6][2] = {{1, 0}, {-1, 1}, {1, 2}, {-1,3}, {1,4}, {-1, 5}};
int pl3[2][2] = {{1, 0}, {1, 1}};
int pl4[2][2] = {{-1, 0}, {1, 1}};
main() { 
  int pr;
  cout << endl;
  pr = process(SZ, SZ);
}
