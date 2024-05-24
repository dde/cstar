/* aggregating using streams */
itoa(int i, char *out)
{
  int ox = 0;
  int p10[] = {10000, 1000, 100, 10};
  int d, ix;
  boolean nz;
  if (i < 0)
  {
    *(out + ox) = '-';
    ++ox;
    i = -i;
  }
  nz = false;
  for (ix = 0; ix < 4; ++ix)
  {
    if (nz || i >= p10[ix])
    {
      d = i / p10[ix];
      *(out + ox) = '0' + d;
      ++ox;
      if (d != 0)
        i -= d * p10[ix];
      nz = true;
    }
  }
  *(out + ox) = '0' + i;
  ++ox;
  *(out + ox) = '\0';
}
#define LOOPS 2
#define PROCESSES 2
typedef struct {
  int addr;
  int valu;
  float aggr;
} aggmsg_t;
aggmsg_t stream aga[PROCESSES + 1];
void Aggregate(int prct)
{
  int n = 0;
  float sum = 0;
  float avg;
  aggmsg_t msg;
  cout << myid << " en agg" << endl;
  while (true)
  {
    while (n < prct)
    {
      recv(aga[0], msg);
      if (msg.addr == 0)
      {
        cout << myid << " ex msg" << endl;
        return;
      }
      sum = sum + (float)msg.valu;
      n += 1;
    }
    avg = sum / (float)prct;
    msg.aggr = avg;
    msg.valu = 0;
    while (n > 0)
    {
      msg.addr = n;
      send(aga[n], msg);
      n -= 1;
    }
    sum = 0;
  }
  cout << myid << " ex agg" << endl;
}
void process(int i, int j)
{
  aggmsg_t pmsg;
  pmsg.addr = i;
  pmsg.valu = j * PROCESSES + i;
  pmsg.aggr = 0.0;
  send(aga[0], pmsg);
  recv(aga[i], pmsg);
  cout << "process " << myid << " aggr " << pmsg.aggr << endl;
}
void initStreamAgg()
{
  return;
}
int main()
{
  int i, j;
  aggmsg_t emsg;
  cout.precision(3);
  fork Aggregate(PROCESSES);
  for (j = 0; j < LOOPS; ++j)
  {
    forall i = 1 to PROCESSES do
      process(i, j);
  }
  emsg.addr = 0;
  emsg.valu = 0;
  emsg.aggr = 0.0;
  send(aga[0], emsg);
  join;
  cout << "finished" << endl;
  return 0;
}
