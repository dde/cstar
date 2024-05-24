ARCHITECTURE MESH2(2);
#include <mpi.h>
#define MSG_LEN 3
void r_func(int rnk, int root)
{
  int sbuf[MSG_LEN];
  int rbuf[MSG_LEN];
  sbuf[0] = MSG_LEN * rnk;
  sbuf[1] = sbuf[0] + 1;
  sbuf[2] = sbuf[1] + 2;
  if (rnk == root)
    cout << "root processor is " << root << endl;
  MPI_Reduce(&sbuf[0], &rbuf[0], MSG_LEN, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
  if (rnk == root)
  {
    cout << "reduction result in root " << rbuf[0] << ", " << rbuf[1] << ", " << rbuf[2] << endl;;
  }
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
  r_func(myrank, 0);
  MPI_Finalize();
  return 0;
}
