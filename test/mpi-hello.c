ARCHITECTURE RING(2);
#include <mpi.h>
int myrank, totalproc; 

main( ) {
  cout.precision(6);
  MPI_Init( );
  cout << "clock1 " << clock << endl;
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  cout << "clock2 " << clock << endl;
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  cout << "clock3 " << clock << endl;
  cout << "Hello World from process " << myrank
       << " out of " << totalproc << endl;
  cout << "clock4 " << clock << endl;
  MPI_Finalize( );
  cout << "clock5 " << clock << endl;
}
