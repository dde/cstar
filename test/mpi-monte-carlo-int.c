/* MPI Monte Carlo Integration */
ARCHITECTURE MESH2(2); /*20 by 20 Mesh topology*/
#include <mpi.h>
#include <stdlib.h>
#define numiter 100 /*number of random samples*/
MPI_Status status;
float get_random( ) {
  float x;
  /*returns random number in range 0 to 1*/
  x = (float)rand();
  return x / RAND_MAX;
}
float f(float x)
{
  return 1.0;
}
int main( )
{
  float a = 1.0, b = 2.0; /*start and end of interval*/
  int myrank, totalproc, j, k, tag = 1;
  float x, y, sum;
  cout.precision(5);
  MPI_Init( );
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  /* take random samples of f(x) */
  sum = 0;
  for (j = 1; j <= numiter; ++j)
  {
    x = a + (b - a) * get_random( );
    sum = sum + f(x);
  }
  sum = sum / numiter;
  /* collect and average samples from all processes */
  if (myrank > 0)
  {
    cout << "sending sum " << sum << " from " << myrank << endl;
    MPI_Send(&sum, 1, MPI_FLOAT, 0, tag, MPI_COMM_WORLD);
  }
  else
  {
    for (k = 1; k < totalproc; ++k)
    {
      MPI_Recv(&y, 1, MPI_FLOAT, MPI_ANY_SOURCE,
               MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      cout << "recv sum " << y << " from " << status.MPI_SOURCE << endl;
      sum = sum + y;
    }
    cout << "Integral of f(x) from " << a << " to " << b 
         << (b - a) * sum / totalproc << endl;
  }
  MPI_Finalize( );
}
