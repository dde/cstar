ARCHITECTURE RING(4);
#include <mpi.h>
int myrank, totalproc; 
/*
int MPI_Cart_create(
  MPI_Comm comm,   original communication group
  int ndims,       number of cartesian dimensions
  int *dims,       array with size of each dimension
  int *wrap,       array indicating if wraparound
  int reorder,     whether process rank may change
  MPI_Comm *cart   handle to cartesian topology
);
*/
/* translate cartesian coordinates to process rank*/
/*
int MPI_Cart_rank(
  MPI_Comm comm,   handle of the cartesian topology
  int *coords,     array with cartesian coordinates
  int *rank        pointer to the process rank
)
*/
/* translate process rank to cartesian coordinates */
/*
int MPI_Cart_coords(
  MPI_Comm comm,   handle of the cartesian topology
  int rank,        rank of the process
  int ndims,       number of cartestian dimensions
  int *coords      array with cartesian coordinates
*/
/* get process Cartesian coordinates */
/*
int MPI_Cart_get(
  MPI_Comm comm,   handle of the cartesian topology
  int ndims,       number of cartesian dimensions
  int *dims,       array with size of each dimension
  int *wrap,       whether each dimension is wraparound
  int *coords       array with cartesian coordinates
)
*/
int ncg_dims[2] = {2, 2};
int ncg_wrap[2] = {1, 1};
MPI_Comm ncg;
void create()
{
  MPI_Cart_create(MPI_COMM_WORLD, 2, &ncg_dims[0], &ncg_wrap[0], 0, &ncg);
}
void process()
{
  int crank;
  int dims;
  int sdim, sdir;
  int cdims[2];
  int rrnk, srnk;
  float wtime;
  cout.precision(3);
  MPI_Cartdim_get(ncg, &dims);
  cout << "process world rank " << myid << " cart dimensions " << dims << endl;
  MPI_Cart_get(ncg, 2, &ncg_dims[0], &ncg_wrap[0], &cdims[0]);
  cout << "process world rank " << myid << " cart coords (" << cdims[0] << "," << cdims[1] << ")" << endl;
  MPI_Cart_rank(ncg, &cdims[0], &crank);
  cout << "process world rank " << myid << " cart rank " << crank << " from cart coords" << endl;
  MPI_Cart_coords(ncg, crank, 2, &cdims[0]);
  cout << "process cart rank " << crank << " to cart coords (" << cdims[0] << "," << cdims[1] << ")" << endl;
  srnk = crank;
  sdim = 0;
  sdir = 1;
  MPI_Cart_Shift(ncg, sdim, sdir, &srnk, &rrnk);
  cout << "shift from my cart rank " << crank << " dimension " << sdim << " direction " << sdir << " receiver " << rrnk << endl;


  wtime = MPI_Wtime();
  cout << "MPI WTime " << wtime << endl;
  MPI_Comm_free(&ncg);
}

main( ) {
  MPI_Init( );
  create();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  cout << "MPI_Cart_create test world rank " << myrank << " processors " << totalproc << endl;
  process();
  MPI_Finalize( );
}
