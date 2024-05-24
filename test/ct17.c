/* simple Producer/Consumer */
#include <string.h>
#define endmarker '\0'
#define MSGLN 25
char stream chan;
char[MSGLN] stream sync_out;
void Producer()
{
  char[MSGLN] msg;
  char ival;
  /*
  cout << "Producer starting" << endl;
  */
  strcpy(msg, "Producer starting");
  send(sync_out, msg);
  send(chan, endmarker);
  /*
  cout << "Producer ending" << endl;
  */
  strcpy(msg, "Producer ending");
  send(sync_out, msg);
}
void Consumer( )
{
  char[MSGLN] msg;
  char rval;
  /*
  cout << "Consumer starting" << endl;
  */
  strcpy(msg, "Consumer starting");
  send(sync_out, msg);
  recv(chan, rval); /*Read stream*/
  strcpy(msg, "Consumer ending");
  send(sync_out, msg);
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
  char msg[MSGLN];
  FORK Out();
  strcpy(msg, "main starting");
  send(sync_out, msg);
  FORK Producer();
  strcpy(msg, "main after Producer fork");
  send(sync_out, msg);
  FORK Consumer();
  strcpy(msg, "main after Consumer fork");
  send(sync_out, msg);
  join;
  strcpy(msg, "main after join 1");
  send(sync_out, msg);
  join;
  strcpy(msg, "main after join 2");
  send(sync_out, msg);
  strcpy(msg, "main ending");
  send(sync_out, msg);
  msg[0] = '\0';
  send(sync_out, msg);
  join;
}
