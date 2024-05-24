/* MPI Monte Carlo Integration */
ARCHITECTURE HYPERCUBE(7); 
#include <mpi.h>
#include <stdlib.h>
#define TOTALPROCS 128
/*
 * generate and return a random, unique, communication group destination,
 * Track names generated through the passeed array
*/
char unique_dest(int slts[], int procs)
{
  int id, ct;
  id = rand() % procs;
  ct = 0;
  while (ct < procs)
  {
    if (slts[id] == -1)
    {
      slts[id] = 1;
      return id;
    }
    id = (id + 1) % procs;
    ct += 1;
  }
  return -1;  /* return when no more destinations */
}
void initial(int slts[], int count)
{
  int k;
  for (k = 0; k < count; ++k)
  {
    slts[k] = -1;
  }
}
boolean verify(int slts[], int count)
{
  int k;
  boolean filled = false;
  filled = true;
  for (k = 0; k < count; ++k)
  {
    if (slts[k] == -1)
    {
      cout << "slot " << k << " is still open" << endl;
      filled = false;
    }
  }
  return filled;
}
void reorder(int slts[], int lst[], int count)
{
  int k;
  for (k = 0; k < count; ++k)
  {
    lst[slts[k]] = k;
  }
}
void dispOrder(int lst[], int count)
{
  int k, perline = 16;;
  for (k = 0; k < count; ++k)
  {
    cout << " " << lst[k];
    if (k % perline == (perline - 1))
      cout << endl;
  }
  if (k % perline != perline)
    cout << endl;
}
int main()
{
  int myrank, totalproc, j, k, final, dest, tag = 0;
  MPI_Status status;
  int slots[TOTALPROCS];
  int list[TOTALPROCS];
  cout.precision(5);
  MPI_Init( );
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  if (TOTALPROCS != totalproc)
  {
    cout << "ARCHITECTURE inconsistency - ending" << endl;
    return -1;
  }
  if (myrank == 0)
  {
    initial(slots, totalproc);
    dest = unique_dest(slots, totalproc);
    /*
    cout << "dest " << dest << endl;
    */
    /* send to first dest */
    MPI_Send(&slots, totalproc, MPI_INT, dest, tag, MPI_COMM_WORLD);
  }
  /* all processes */
  MPI_Recv(&slots, totalproc, MPI_INT, MPI_ANY_SOURCE,
               MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  dest = unique_dest(slots, totalproc);
  if (dest < 0) /* no more empty slots */
  {
    final = status.MPI_SOURCE;
    tag = status.MPI_TAG;
    slots[myrank] = tag;
    cout << myrank << " is the last processor" << endl;
    verify(slots, totalproc);
    reorder(slots, list, totalproc);
    /*
    dispOrder(list, totalproc);
    */
    tag = 0;
    cout << myrank << " initiating termination to " << list[tag] << endl;
    /*
    MPI_Send(&final, 1, MPI_INT, (myrank + 1) % totalproc, totalproc, MPI_COMM_WORLD);
    */
    MPI_Send(&list, totalproc, MPI_INT, list[tag], totalproc + tag, MPI_COMM_WORLD); /* termination */
  }
  else
  {
    tag = status.MPI_TAG;
    slots[myrank] = tag;
    MPI_Send(&slots, totalproc, MPI_INT, dest, tag + 1, MPI_COMM_WORLD); /* send to next dest */
    MPI_Recv(&list, totalproc, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    tag = status.MPI_TAG - totalproc;
    if (tag == totalproc - 2)
    {
      cout << myrank << " final process terminating" << endl;
    }
    else
    {
      ++tag;
      cout << myrank << " sending termination to " << list[tag] << endl;
      /*
      MPI_Send(&final, 1, MPI_INT, (myrank + 1) % totalproc, totalproc, MPI_COMM_WORLD);
      */
      MPI_Send(&list, totalproc, MPI_INT, list[tag], totalproc + tag, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize( );
}
