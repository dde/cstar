/* simple Producer/Consumer */
#include <string.h>
#define endmarker '\0'
#define MSGLN 25
char stream chan;
char[MSGLN] stream sync_out;
char[MSGLN] msg;
spinlock mlock;
void Producer()
{
  char ival;
  /*
  cout << "Producer starting" << endl;
  */
  lock(mlock);
  strcpy(msg, "Producer starting");
  send(sync_out, msg);
  unlock(mlock);
  send(chan, endmarker);
  /*
  cout << "Producer ending" << endl;
  */
  lock(mlock);
  strcpy(msg, "Producer ending");
  send(sync_out, msg);
  unlock(mlock);
}
void Consumer( )
{
  char rval;
  /*
  cout << "Consumer starting" << endl;
  */
  lock(mlock);
  strcpy(msg, "Consumer starting");
  send(sync_out, msg);
  unlock(mlock);
  recv(chan, rval); /*Read stream*/
  lock(mlock);
  strcpy(msg, "Consumer ending");
  send(sync_out, msg);
  unlock(mlock);
  /*
  cout << "Consumer ending" << endl;
  msg[0] = '\0';
  send(sync_out, msg);
  */
}
void Out()
{
  char msg[MSGLN];
  char ch;
  char *cp;
  int i;
  cout << "Out starting" << endl;
  recv(sync_out, msg);
  while (msg[0] != endmarker)
  {
    for (i = 0; msg[i] != endmarker; ++i)
    {
      /*
      cout << msg[i];
      cp = &msg[i];
      cout << *cp;
      */
      cout << msg[i];
    }
    cout << endl;
    recv(sync_out, msg);
  }
  cout << "Out ending" << endl;
}
int main( )
{
  lock(mlock);
  strcpy(msg, "main starting");
  send(sync_out, msg);
  unlock(mlock);
  FORK Out();
  FORK Producer();
  lock(mlock);
  strcpy(msg, "main after Producer fork");
  send(sync_out, msg);
  unlock(mlock);
  FORK Consumer();
  lock(mlock);
  strcpy(msg, "main after Consumer fork");
  send(sync_out, msg);
  unlock(mlock);
  join;
  lock(mlock);
  strcpy(msg, "main after join 1");
  send(sync_out, msg);
  unlock(mlock);
  join;
  lock(mlock);
  strcpy(msg, "main after join 2");
  send(sync_out, msg);
  strcpy(msg, "main ending");
  send(sync_out, msg);
  msg[0] = '\0';
  send(sync_out, msg);
  unlock(mlock);
  join;
}
