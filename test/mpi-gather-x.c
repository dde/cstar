ARCHITECTURE MESH2(2);
#include <mpi.h>
#include <stdlib.h>
#define MSG_LEN 6
void strout(char *str, int ln)
{
  char ch;
  int sub = 0;
  while (sub < ln)
  {
    cout << *(str + sub);
    sub += 1;
  }
}
void strncpy(char tu[], char *fm, int ln)
{
  int ix = 0;
  while (ix < ln)
  {
    tu[ix] = *(fm + ix);
    ix += 1;
  }
  tu[ln] = '\0';
}
void b_func(int rnk, int rcvr, int ttl)
{
  char *buf = "ABCDEFGHIJKLMNOPQRSTUVWX";
  char sbuf[MSG_LEN + 1];
  char *rbuf;
  float clk;
  int ix;
  rbuf = (char *)malloc(msg_len * ttl + 1);
  /*
  strncpy(sbuf, buf + (rnk * MSG_LEN), MSG_LEN); 
  */
  ix = 0;
  while (ix < MSG_LEN)
  {
    sbuf[ix] = *(buf + (rnk * MSG_LEN)  + ix);
    ix += 1;
  }
  sbuf[MSG_LEN] = '\0';
  if (rnk == rcvr)
    cout << "receiver is " << rcvr << endl;
  MPI_Gather(&sbuf[0], MSG_LEN, MPI_CHAR, rbuf, MSG_LEN, MPI_CHAR, rcvr, MPI_COMM_WORLD);
  if (rnk == rcvr)
  {
    cout << "received ";
    strout(rbuf, MSG_LEN * ttl);
    cout << " in " << rnk << endl;
  }
  free(rbuf);
}
int main()
{
  int myrank, totalproc;
  cout.precision(3);
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  b_func(myrank, 3, totalproc);
  MPI_Finalize();
  return 0;
}
