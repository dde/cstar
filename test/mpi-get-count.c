ARCHITECTURE LINE(2);
#include <mpi.h>
#define MSGLEN 10
void get_count(int rnk, int sndr)
{
  char snd[MSGLEN] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
  char rcv[MSGLEN];
  int tag, flg;
  int ix, jx;
  MPI_Status status;
  if (rnk == 0)
  {

    for (ix = 1; ix < MSGLEN; ++ix)
    {
      MPI_Send(&snd[1], ix, MPI_CHAR, rnk + 1, ix, MPI_COMM_WORLD);
    }
  }
  else if (rnk == 1)
  {
    cout << endl;
    for (ix = 1; ix < MSGLEN; ++ix)
    {
      MPI_Iprobe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &flg, &status);
      if (flg == 0)
      {
        cout << "no waiting message" << endl;
        duration(10);
      }
      MPI_Recv(&rcv[0], MSGLEN, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
      MPI_Get_count(&status, MPI_CHAR, &tag);
      if (tag != status.MPI_TAG)
      {
        cout << "tag != status.MPI_TAG - tag " << tag << " status " << status.MPI_TAG << endl;
      }
      cout << "received ";
      for (jx = 0; jx < tag; ++jx)
      {
        cout << rcv[jx];
      }
      cout << endl;
    }
  }
  else
    return;
}
int main()
{
  int myrank, totalproc;
  cout.precision(3);
  MPI_Init();
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  get_count(myrank, 0);
  MPI_Finalize();
  return 0;
}
