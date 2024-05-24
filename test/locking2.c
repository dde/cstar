#define IMAX 13
#define PROCS 16
spinlock ct_lock;
int counter;
void p1()
{
  int ix;
  /*
  cout << "process " << self << " started" << endl;
  */
  for (ix = 0; ix < IMAX; ++ix)
  {
    lock(ct_lock);
    counter = counter + 1;
    unlock(ct_lock);
  }
  cout << "process " << myid << " incremented the counter " << IMAX << " times" << endl;
}
int main()
{
  int i;
  cout << endl;
  counter = 0;
  cout << "starting counter is " << counter << endl;
  forall i = 1 to PROCS do
    p1();
  cout << "final counter is " << counter << endl;
  return 0;
}
