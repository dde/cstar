#define PROCS 3
int stream lk;
void proc()
{
  int ix = 0, jx = 0, kx = 0;
  int msg;
  recv(lk, msg);
  if (myid == 1)
    ix = 2;
  if (myid == 2)
    jx = 3;
  if (myid == 3)
    kx = 4;
  cout << ix;
  cout << jx;
  cout << kx << endl;
}
int main()
{
  int qx;
  for (qx = 0; qx < PROCS; ++qx)
    fork proc();
  for (qx = 0; qx < PROCS; ++qx)
    send(lk, qx);
  for (qx = 0; qx < PROCS; ++qx)
    join;
  return 0;
}
