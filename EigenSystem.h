static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))


float pythag(float a, float b);
void tred2(float **a, int n, float d[], float e[]);
void tqli(float d[], float e[], int n, float **z);
