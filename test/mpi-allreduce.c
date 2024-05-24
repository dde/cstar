ARCHITECTURE MESH2(2);
#include <mpi.h>
#define MSG_LEN 3
void a_func(int rnk)
{
  int sbuf[MSG_LEN];
  int rbuf[MSG_LEN];
  sbuf[0] = MSG_LEN * rnk + 1;
  sbuf[1] = sbuf[0] + 1;
  sbuf[2] = sbuf[1] + 1;
  cout << "send buffer in processor " << rnk << ":" << sbuf[0] << ", " << sbuf[1] << ", " << sbuf[2] << endl;;
  MPI_Allreduce(&sbuf[0], &rbuf[0], MSG_LEN, MPI_INT, MPI_PROD, MPI_COMM_WORLD);
  cout << "reduction result in processor " << rnk << ":" << rbuf[0] << ", " << rbuf[1] << ", " << rbuf[2] << endl;;
}
int main()
{
  int myrank, totalproc;
  /*
  cout.precision(1);
  */
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  a_func(myrank);
  MPI_Finalize();
  return 0;
}
