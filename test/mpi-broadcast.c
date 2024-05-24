ARCHITECTURE MESH2(2);
#include <mpi.h>
#define MSG_LEN 1
void b_func(int rnk, int sndr)
{
  char buf = 'X';
  if (rnk == 0)
    buf = 'm';
  cout << "clock before broadcast " << clock << " in " << rnk << endl;
  MPI_Bcast(&buf, MSG_LEN, MPI_CHAR, sndr, MPI_COMM_WORLD);
  if (rnk != sndr)
    cout << "received " << buf << " at " << clock << " in " << rnk << endl;
}
int main()
{
  int myrank, totalproc;
  cout.precision(3);
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  b_func(myrank, 0);
  MPI_Finalize();
  return 0;
}
