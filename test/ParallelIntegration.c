/* Parallel Numerical Integration */
#define NUMPROC 40 /*number of processes*/
#define NUMPOINTS 30 /*number of points per process*/
float globalsum = 0.0;
spinlock L;
float f(float t)  /*Function to be integrated*/
{ /*Compute value of f(t)*/
  return t * t;  /* f(x) = x^2 */
}
void Integrate(int myindex, float a, float b, float w)
{
  float localsum = 0;
  float t;
  int j;
  t = a + myindex * (b - a) / NUMPROC; /*My start position*/
  for (j = 1; j <= NUMPOINTS; j++)
  {
    localsum = localsum + f(t); /*Add next point*/
    t = t + w;
  }
  localsum = w * localsum;
  Lock(L);
    globalsum = globalsum + localsum; /*atomic update*/
  Unlock(L);
}
int main( )
{
  /*Initialize values of end points “a” and “b”*/
  float a, b, w;
  float answer;
  int i;
  a = 0.0;
  b = 2.0;
  w = (b - a) / (NUMPROC * NUMPOINTS); /*spacing of points*/
  forall i = 0 to NUMPROC-1 do  /*Create processes*/
    Integrate(i, a, b, w);
  answer = globalsum + w / 2 * (f(b) - f(a)); /*end points*/
  cout.precision(7);
  cout << "integral of x^2 from " << a << " to " << b << " = " << answer << endl;
  return 0;
}
