#include<stdlib.h>
#define TASKS 100
#define NUMBERS 13
#define PROCESSES 5
#define MAXRAND 55
/*
 *  Pro --> Wk1 --> Wk2 --> ... Wkn --> Con
*/
int work_list[TASKS] = {
                  3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,  47,  53, 59,   61,  67,  71,  73,
                 79,  83,  89,  97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
                181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
                293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
                421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547};
                /*
                557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619};
                */
typedef struct {
  int initial;
  int current;
} message;
int test_data[NUMBERS] = {557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619};
message stream channel[PROCESSES];
void Producer(message stream ochn)
{
  int ix, rnd;
  message msg;
  for (ix = 0; ix < NUMBERS; ++ix)
  {
    rnd = 1 + test_data[ix] % MAXRAND;
    /*
    rnd = 1 + rand() % MAXRAND;
    if (rnd == 26)
    cout << "sent " << rnd << endl;
    */
    msg.initial = rnd;
    msg.current = rnd;
    send(ochn, msg);
    cout << "producer send " << msg.initial << ":" << msg.current << endl;
  }
  msg.initial = 0;
  msg.current = 0;
  send(ochn, msg);
}
void Consumer(int p, message stream ichn)
{
  message msg;
  boolean running = true;
  int ce, cp;
  /*
  cout << "consumer prime " << p << endl;
  */
  ce = 0;
  cp = 0;
  while (running)
  {
    recv(ichn, msg);
    cout << "consumer recv " << msg.initial << ":" << msg.current << endl;
    if (msg.current != 0)
    {
      msg.current -= p;
      if (msg.current == 0)
      {
        cout << "pipeline completed with initial value " << msg.initial << endl;
        ce += 1;
      }
      else if (msg.current > 0)
        cp += 1;
    }
    else
    {
      running = false;
    }
  }
  cout << "assembly line produced " << ce << " working units" << endl;
  cout << "assembly line produced " << cp << " fixable units" << endl;
}
void Worker(int p, message stream ichn, message stream ochn)
{
  message msg;
  boolean running = true;
  /*
  cout << "worker prime " << p << endl;
  */
  while (running)
  {
    recv(ichn, msg);
    cout << myid << " worker recv " << msg.initial << ":" << msg.current << endl;
    if (msg.current > 0)
    {
      msg.current -= p;
      if (msg.current <= 0)
        continue;
    }
    else
    {
      running = false;
    }
    send(ochn, msg);
  }
}
int main()
{
  int ix;
  fork Consumer(work_list[PROCESSES - 1], channel[PROCESSES - 1]);
  for (ix = PROCESSES - 2; ix >= 0;  --ix)
  {
     fork Worker(work_list[ix], channel[ix], channel[ix + 1]);    
  }
  fork Producer(channel[0]);
  for (ix = 0; ix < PROCESSES - 1; ++ix)
  {
     join;
  }
  join;
  join;
}

