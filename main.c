#include <math.h>
#include <string.h>
#include <sys/time.h>

#define N 20000000
#define NT 10

float x[N*3], y[N*3], alpha;
double x21[N], y21[N];
double time;
int bit;

void getresults(const float *x, const int bit, const double time)
{
  int byte;
  switch(bit){
    case 32:
      byte=3;
      break;
    case 21:
      byte=2;
      break;
    default:
      byte=0;
  }

#pragma acc update host(x[0:3*N])
  int iflag=1;
  const float eps=5e-2;
  
  int i, i_xyz;
  for(i=0; i<N; i++){
    for(i_xyz=0;i_xyz<3;i_xyz++){
      float xtrue=1e0/i*(NT+1);
      if (fabsf((x[i_xyz+3*i]-xtrue)/xtrue)>eps){
        iflag=0;
      }
    }
  }

  if(iflag){
    printf("  results:  [  OK  ]\n");
    printf("  time(ms)= %f\n", time/NT*1e3);
    printf("  BW(GB/s)= %f\n", (4e0*N)*(byte*3)/(time/NT)/1e9);
  }else{
    printf("  results:  [  NG  ]\n");
  }

  return;
}


int main()
{
  int i, i_xyz;
  struct timeval t0, t1;

  printf("N = %d\n",N);
  for(i=0; i<N; i++){
    for(i_xyz=0;i_xyz<3;i_xyz++){
      x[i_xyz+3*i]=1.0f/i;
      y[i_xyz+3*i]=1.0f/i;
    }
  }

  alpha=1.0f;

#pragma acc data copy(x,y) copyin(alpha) create(x21,y21)
{
  convert_array_fp32_to_fp21(N, x, x21);
  convert_array_fp32_to_fp21(N, y, y21);

  printf("OpenACC FP32 SAXPY\n");
  gettimeofday(&t0, NULL);

  for(int it=0; it<NT; it++){
    gpufp32_saxpy(N, x, y, &alpha);
  }
  gettimeofday(&t1, NULL);

  time=(t1.tv_sec-t0.tv_sec)+(t1.tv_usec-t0.tv_usec)*1.0e-6;
  getresults(x, 32, time);
  

  printf("OpenACC FP21 SAXPY\n");
  gettimeofday(&t0, NULL);

  for(int it=0; it<NT; it++){
    gpufp21_saxpy(N, x21, y21, &alpha);
  }

  gettimeofday(&t1, NULL); 
  time=(t1.tv_sec-t0.tv_sec)+(t1.tv_usec-t0.tv_usec)*1.0e-6;
  
  convert_array_fp21_to_fp32(N, x21, x);
  getresults(x, 21, time);
}
}
