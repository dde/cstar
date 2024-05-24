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
  cout << "Producer starting" << endl;
  send(chan, endmarker);
  cout << "Producer ending" << endl;
}
void Consumer( )
{
  char[MSGLN] msg;
  char rval;
  cout << "Consumer starting" << endl;
  recv(chan, rval); /*Read stream*/
  msg[0] = endmarker;
  send(sync_out, msg);
  cout << "Consumer ending" << endl;
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
      */
      cp = &msg[i];
      cout << *cp;
    }
    cout << endl;
    recv(sync_out, msg);
  }
  cout << "Out ending" << endl;
}
int main( )
{
  cout << "main starting" << endl;
  FORK Producer();
  cout << "main after Producer fork" << endl;
  FORK Consumer();
  cout << "main after Consumer fork" << endl;
  FORK Out();
  cout << "main after Out fork" << endl;
  join;
  cout << "main after join 1" << endl;
  join;
  cout << "main after join 2" << endl;
  join;
  cout << "main ending" << endl;
}
