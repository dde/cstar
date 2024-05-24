ARCHITECTURE MESH2(2);
#include <mpi.h>
void b_func(int rnk)
{
  cout << "clock before barrier " << clock << " in " << rnk << endl;
  MPI_Barrier(MPI_COMM_WORLD);
  cout << "clock after barrier " << clock << " in " << rnk << endl;
}
int main()
{
  int myrank, totalproc;
  cout.precision(3);
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  b_func(myrank);
  MPI_Finalize();
  return 0;
}
