#include <stdlib.h>
struct DS {
int stream ist;
int *a;
} d1;

int main() {
  int imsg = 2, omsg = 0;
  int stream *isp;
  struct DS *d1p;
  isp = &d1.ist;
  d1p = calloc(1, 16);
  d1p->a = &imsg;
  cout << "integer stream size " << sizeof(struct DS) << endl;
  for (imsg = 1; imsg <= 2; ++imsg)
  {
    cout << "sending " << imsg << endl;
    SEND(d1p->ist, imsg);
    RECV(d1p->ist, omsg);
    cout << "received " << omsg << endl;
  }
  free(d1p);
  return 0;
}
