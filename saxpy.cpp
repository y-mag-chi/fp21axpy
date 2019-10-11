#include <stdio.h>
#include <math.h>
#include "./fp21component.h"

extern "C"{

void convert_array_fp32_to_fp21(int n, float *a32, fp21x3 *a21){
  int i;
  float tmp1,tmp2,tmp3;
  #pragma acc parallel loop default(none) present(a32,a21) private(i,tmp1,tmp2,tmp3)
  for(i=0; i<n; i++){
    tmp1=a32[0+3*i];
    tmp2=a32[1+3*i];
    tmp3=a32[2+3*i];
    a21[i]=convert_floatxyz_to_fp21x3(tmp1,tmp2,tmp3);
  }
}


void convert_array_fp21_to_fp32(int n, fp21x3 *a21, float *a32){
  int i;
  #pragma acc parallel loop default(none) present(a32,a21) private(i)
  for(i=0; i<n; i++){
    a32[0+3*i]=convert_fp21x3_to_float3_x(a21[i]);
    a32[1+3*i]=convert_fp21x3_to_float3_y(a21[i]);
    a32[2+3*i]=convert_fp21x3_to_float3_z(a21[i]);
  }
}


void gpufp32_saxpy(int n, float *a, float *b, float *alpha){
  int i, i_xyz;
  #pragma acc parallel loop collapse(2) present(a,b,alpha) private(i,i_xyz) 
  for(i=0;i<n;i++){
    for(i_xyz=0;i_xyz<3;i_xyz++){
      a[i_xyz+i*3]=a[i_xyz+i*3]*(*alpha)+b[i_xyz+i*3];
    }
  }
}


void gpufp21_saxpy(int n, fp21x3 *a21, fp21x3 *b21, float *alpha){
  int i;
  float a0,a1,a2,b0,b1,b2;
  #pragma acc parallel loop present(a21,b21,alpha) private(i,a0,a1,a2,b0,b1,b2) 
  for(i=0;i<n;i++){
    a0=convert_fp21x3_to_float3_x(a21[i]);
    a1=convert_fp21x3_to_float3_y(a21[i]);
    a2=convert_fp21x3_to_float3_z(a21[i]);
    b0=convert_fp21x3_to_float3_x(b21[i]);
    b1=convert_fp21x3_to_float3_y(b21[i]);
    b2=convert_fp21x3_to_float3_z(b21[i]);
    a0=a0*(*alpha)+b0;
    a1=a1*(*alpha)+b1;
    a2=a2*(*alpha)+b2;
    a21[i]=convert_floatxyz_to_fp21x3(a0,a1,a2);
  }
}

}
