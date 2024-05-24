ARCHITECTURE MESH2(2);
#include <mpi.h>
#include <string.h>
#define PROCS 4
#define MSG_LEN 6
char *alpha[PROCS];
void init()
{
  alpha[0] = "ABCDEF";
  alpha[1] = "GHIJKL";
  alpha[2] = "MNOPQR";
  alpha[3] = "STUVWX";
}
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
void g_func(int rnk, int rcvr)
{
  char sbuf[MSG_LEN + 1];
  char rbuf[MSG_LEN * PROCS];
  strcpy(sbuf, alpha[rnk]); 
  if (rnk == rcvr)
    cout << "receiver is processor " << rcvr << endl;
  MPI_Gather(&sbuf[0], MSG_LEN, MPI_CHAR, &rbuf[0], MSG_LEN, MPI_CHAR, rcvr, MPI_COMM_WORLD);
  if (rnk == rcvr)
  {
    cout << "received ";
    strout(rbuf, MSG_LEN * PROCS);
    cout << " in processor " << rnk << endl;
  }
}
int main()
{
  int myrank, totalproc;
  cout.precision(3);
  init();
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  g_func(myrank, 2);
  MPI_Finalize();
  return 0;
}
