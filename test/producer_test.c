/* simple Producer/Worker */
#include <string.h>
#define endmarker '\0'
#define MSGLN 25
typedef char[MSGLN] stream msg_t;
char stream chan;
/* char[MSGLN] stream sync_out, sync2; */
char[MSGLN] stream sync_out;
char[MSGLN] stream sync2;
msg_t stream sync0;
void Producer()
{
    char[MSGLN] msg;
    char ival;
    strcpy(msg, "Producer starting");
    send(sync_out, msg);
    for (ival = '1'; ival < '5'; ival += 1)
    {
        /*send next “ival” to stream */
        send(chan, ival);
        strcpy(msg, "sending ");
        msg[8] = ival;
        send(sync_out, msg);
    }
    send(chan, endmarker);
    strcpy(msg, "Producer ending");
    send(sync_out, msg);
}
void Worker( )
{
    char[MSGLN] msg;
    char rval;
    strcpy(msg, "Worker starting");
    send(sync_out, msg);
    recv(chan, rval); /*Read stream*/
    while (rval != '\0')
    {
        strcpy(msg, "received ");
        msg[9] = rval;
        send(sync_out, msg);
        recv(chan, rval);
    }
    strcpy(msg, "Worker ending");
    send(sync_out, msg);
}
void Consumer()
{
    char msg[MSGLN];
    char ch;
    char *cp;
    int i;
    cout << "Consumer starting" << endl;
    recv(sync_out, msg);
    while (msg[0] != endmarker)
    {
        for (i = 0; msg[i] != endmarker; ++i)
        {
            cp = &msg[i];
            cout << *cp;
        }
        cout << endl;
        recv(sync_out, msg);
    }
    cout << "Consumer ending" << endl;
}
int main( )
{
    char[MSGLN] msg;
    sync2 = sync_out;
    sync0 = sync_out;
    strcpy(msg, "main starting");
    send(sync_out, msg);
    FORK Consumer();
    strcpy(msg, "main after Consumer fork");
    send(sync2, msg);
    FORK Worker();
    strcpy(msg, "main after Worker fork");
    send(sync_out, msg);
    FORK Producer();
    strcpy(msg, "main after Producer fork");
    send(sync2, msg);
    join;
    strcpy(msg, "main after join 1");
    send(sync_out, msg);
    join;
    strcpy(msg, "main after join 2");
    send(sync2, msg);
    msg[0] = endmarker;
    send(sync_out, msg);
    join;
    cout << "main ending" << endl;
}