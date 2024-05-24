ARCHITECTURE MESH2(2);
#include <mpi.h>
#define MSG_LEN 6
void strout(char str[], int ln)
{
  char ch;
  int sub = 0;
  while (sub < ln)
  {
    cout << str[sub];
    sub += 1;
  }
}
void b_func(int rnk, int sndr)
{
  char *sbuf = "ABCDEFGHIJKLMNOPQRSTUVWX";
  char rbuf[MSG_LEN];
  float clk;
  if (rnk == sndr)
    cout << "sender is " << sndr << endl;
  MPI_Scatter(sbuf, MSG_LEN, MPI_CHAR, &rbuf[0], MSG_LEN, MPI_CHAR, sndr, MPI_COMM_WORLD);
  if (rnk == sndr)
  {
    cout << "received ";
    strout(rbuf, MSG_LEN);
    cout << " in " << rnk << endl;
  }
}
int main()
{
  int myrank, totalproc;
  cout.precision(3);
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  b_func(myrank, 3);
  MPI_Finalize();
  return 0;
}
