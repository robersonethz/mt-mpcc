/* This file was automatically generated by CasADi.
   The CasADi copyright holders make no ownership claim of its contents. */
#ifdef __cplusplus
extern "C" {
#endif

/* How to prefix internal symbols */
#ifdef CASADI_CODEGEN_PREFIX
  #define CASADI_NAMESPACE_CONCAT(NS, ID) _CASADI_NAMESPACE_CONCAT(NS, ID)
  #define _CASADI_NAMESPACE_CONCAT(NS, ID) NS ## ID
  #define CASADI_PREFIX(ID) CASADI_NAMESPACE_CONCAT(CODEGEN_PREFIX, ID)
#else
  #define CASADI_PREFIX(ID) FORCESNLPsolver_model_ ## ID
#endif

#include <math.h> 
#include "FORCESNLPsolver_model.h"

#ifndef casadi_real
#define casadi_real FORCESNLPsolver_float
#endif

#ifndef casadi_int
#define casadi_int solver_int32_default
#endif

/* Add prefix to internal symbols */
#define casadi_f0 CASADI_PREFIX(f0)
#define casadi_f1 CASADI_PREFIX(f1)
#define casadi_f2 CASADI_PREFIX(f2)
#define casadi_f3 CASADI_PREFIX(f3)
#define casadi_s0 CASADI_PREFIX(s0)
#define casadi_s1 CASADI_PREFIX(s1)
#define casadi_s2 CASADI_PREFIX(s2)
#define casadi_s3 CASADI_PREFIX(s3)
#define casadi_s4 CASADI_PREFIX(s4)
#define casadi_s5 CASADI_PREFIX(s5)
#define casadi_s6 CASADI_PREFIX(s6)
#define casadi_s7 CASADI_PREFIX(s7)
#define casadi_sq CASADI_PREFIX(sq)

/* Symbol visibility in DLLs */
#if 0
  #if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
    #if defined(STATIC_LINKED)
      #define CASADI_SYMBOL_EXPORT
    #else
      #define __declspec(dllexport)
    #endif
  #elif defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
    #define __attribute__ ((visibility ("default")))
  #else
    #define CASADI_SYMBOL_EXPORT
  #endif
#endif

casadi_real casadi_sq(casadi_real x) { return x*x;}

static const casadi_int casadi_s0[16] = {12, 1, 0, 12, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
static const casadi_int casadi_s1[30] = {26, 1, 0, 26, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
static const casadi_int casadi_s2[5] = {1, 1, 0, 1, 0};
static const casadi_int casadi_s3[21] = {1, 12, 0, 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 6, 0, 0, 0, 0, 0, 0};
static const casadi_int casadi_s4[13] = {9, 1, 0, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const casadi_int casadi_s5[7] = {3, 1, 0, 3, 0, 1, 2};
static const casadi_int casadi_s6[15] = {3, 9, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 1, 2};
static const casadi_int casadi_s7[32] = {9, 9, 0, 3, 6, 7, 12, 16, 20, 20, 20, 20, 2, 3, 4, 2, 3, 4, 5, 3, 4, 5, 6, 7, 3, 4, 5, 7, 3, 4, 5, 7};

/* FORCESNLPsolver_objective_0:(i0[12],i1[26])->(o0,o1[1x12,6nz]) */
static int casadi_f0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real a0, a1, a10, a11, a12, a13, a14, a15, a16, a2, a3, a4, a5, a6, a7, a8, a9;
  a0=arg[1]? arg[1][5] : 0;
  a1=sin(a0);
  a2=arg[1]? arg[1][0] : 0;
  a0=cos(a0);
  a3=arg[0]? arg[0][11] : 0;
  a4=arg[1]? arg[1][4] : 0;
  a5=(a3-a4);
  a5=(a0*a5);
  a2=(a2+a5);
  a5=arg[0]? arg[0][3] : 0;
  a6=(a2-a5);
  a6=(a1*a6);
  a7=arg[1]? arg[1][1] : 0;
  a3=(a3-a4);
  a3=(a1*a3);
  a7=(a7+a3);
  a3=arg[0]? arg[0][4] : 0;
  a4=(a7-a3);
  a4=(a0*a4);
  a6=(a6-a4);
  a4=arg[1]? arg[1][6] : 0;
  a8=(a6*a4);
  a9=(a8*a6);
  a2=(a2-a5);
  a2=(a0*a2);
  a7=(a7-a3);
  a7=(a1*a7);
  a2=(a2+a7);
  a7=arg[1]? arg[1][7] : 0;
  a3=(a2*a7);
  a5=(a3*a2);
  a9=(a9+a5);
  a5=arg[1]? arg[1][11] : 0;
  a10=arg[0]? arg[0][2] : 0;
  a10=(a5*a10);
  a9=(a9-a10);
  a10=arg[0]? arg[0][0] : 0;
  a11=arg[1]? arg[1][8] : 0;
  a12=(a10*a11);
  a13=(a12*a10);
  a9=(a9+a13);
  a13=arg[0]? arg[0][1] : 0;
  a14=arg[1]? arg[1][9] : 0;
  a15=(a13*a14);
  a16=(a15*a13);
  a9=(a9+a16);
  if (res[0]!=0) res[0][0]=a9;
  a11=(a11*a10);
  a12=(a12+a11);
  if (res[1]!=0) res[1][0]=a12;
  a14=(a14*a13);
  a15=(a15+a14);
  if (res[1]!=0) res[1][1]=a15;
  a5=(-a5);
  if (res[1]!=0) res[1][2]=a5;
  a7=(a7*a2);
  a3=(a3+a7);
  a7=(a0*a3);
  a4=(a4*a6);
  a8=(a8+a4);
  a4=(a1*a8);
  a6=(a7+a4);
  a6=(-a6);
  if (res[1]!=0) res[1][3]=a6;
  a8=(a0*a8);
  a3=(a1*a3);
  a6=(a8-a3);
  if (res[1]!=0) res[1][4]=a6;
  a3=(a3-a8);
  a1=(a1*a3);
  a7=(a7+a4);
  a0=(a0*a7);
  a1=(a1+a0);
  if (res[1]!=0) res[1][5]=a1;
  return 0;
}

int FORCESNLPsolver_objective_0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f0(arg, res, iw, w, mem);
}

int FORCESNLPsolver_objective_0_alloc_mem(void) {
  return 0;
}

int FORCESNLPsolver_objective_0_init_mem(int mem) {
  return 0;
}

void FORCESNLPsolver_objective_0_free_mem(int mem) {
}

int FORCESNLPsolver_objective_0_checkout(void) {
  return 0;
}

void FORCESNLPsolver_objective_0_release(int mem) {
}

void FORCESNLPsolver_objective_0_incref(void) {
}

void FORCESNLPsolver_objective_0_decref(void) {
}

casadi_int FORCESNLPsolver_objective_0_n_in(void) { return 2;}

casadi_int FORCESNLPsolver_objective_0_n_out(void) { return 2;}

casadi_real FORCESNLPsolver_objective_0_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

const char* FORCESNLPsolver_objective_0_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    default: return 0;
  }
}

const char* FORCESNLPsolver_objective_0_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_objective_0_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_objective_0_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s2;
    case 1: return casadi_s3;
    default: return 0;
  }
}

int FORCESNLPsolver_objective_0_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 2;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}

/* FORCESNLPsolver_cdyn_0:(i0[9],i1[3],i2[26])->(o0[9],o1[3x9,3nz],o2[9x9,20nz]) */
static int casadi_f1(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real a0, a1, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a2, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a3, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a4, a5, a6, a7, a8, a9;
  a0=arg[0]? arg[0][3] : 0;
  a1=arg[0]? arg[0][2] : 0;
  a2=cos(a1);
  a3=(a0*a2);
  a4=arg[0]? arg[0][4] : 0;
  a5=sin(a1);
  a6=(a4*a5);
  a3=(a3-a6);
  if (res[0]!=0) res[0][0]=a3;
  a3=sin(a1);
  a6=(a0*a3);
  a7=cos(a1);
  a8=(a4*a7);
  a6=(a6+a8);
  if (res[0]!=0) res[0][1]=a6;
  a6=arg[0]? arg[0][5] : 0;
  if (res[0]!=0) res[0][2]=a6;
  a8=arg[2]? arg[2][22] : 0;
  a9=arg[2]? arg[2][23] : 0;
  a10=(a9*a0);
  a8=(a8-a10);
  a10=arg[0]? arg[0][6] : 0;
  a11=(a8*a10);
  a12=arg[2]? arg[2][25] : 0;
  a11=(a11-a12);
  a12=arg[2]? arg[2][24] : 0;
  a13=(a12*a0);
  a14=(a13*a0);
  a11=(a11-a14);
  a14=arg[2]? arg[2][16] : 0;
  a15=arg[2]? arg[2][17] : 0;
  a16=arg[2]? arg[2][18] : 0;
  a17=arg[0]? arg[0][7] : 0;
  a18=arg[2]? arg[2][13] : 0;
  a19=(a6*a18);
  a19=(a19+a4);
  a20=atan2(a19,a0);
  a20=(a17-a20);
  a20=(a16*a20);
  a21=atan(a20);
  a21=(a15*a21);
  a22=sin(a21);
  a22=(a14*a22);
  a23=sin(a17);
  a24=(a22*a23);
  a11=(a11-a24);
  a24=arg[2]? arg[2][14] : 0;
  a25=(a24*a4);
  a26=(a25*a6);
  a11=(a11+a26);
  a11=(a11/a24);
  if (res[0]!=0) res[0][3]=a11;
  a11=arg[2]? arg[2][19] : 0;
  a26=arg[2]? arg[2][20] : 0;
  a27=arg[2]? arg[2][21] : 0;
  a28=arg[2]? arg[2][12] : 0;
  a29=(a6*a28);
  a29=(a29-a4);
  a30=atan2(a29,a0);
  a30=(a27*a30);
  a31=atan(a30);
  a31=(a26*a31);
  a32=sin(a31);
  a32=(a11*a32);
  a33=cos(a17);
  a34=(a22*a33);
  a34=(a32+a34);
  a35=(a24*a0);
  a36=(a35*a6);
  a34=(a34-a36);
  a34=(a34/a24);
  if (res[0]!=0) res[0][4]=a34;
  a34=(a22*a18);
  a36=cos(a17);
  a37=(a34*a36);
  a32=(a32*a28);
  a37=(a37-a32);
  a32=arg[2]? arg[2][15] : 0;
  a37=(a37/a32);
  if (res[0]!=0) res[0][5]=a37;
  a37=arg[1]? arg[1][0] : 0;
  if (res[0]!=0) res[0][6]=a37;
  a37=arg[1]? arg[1][1] : 0;
  if (res[0]!=0) res[0][7]=a37;
  a37=arg[1]? arg[1][2] : 0;
  if (res[0]!=0) res[0][8]=a37;
  a37=1.;
  if (res[1]!=0) res[1][0]=a37;
  if (res[1]!=0) res[1][1]=a37;
  if (res[1]!=0) res[1][2]=a37;
  a38=sin(a1);
  a38=(a0*a38);
  a39=cos(a1);
  a39=(a4*a39);
  a38=(a38+a39);
  a38=(-a38);
  if (res[2]!=0) res[2][0]=a38;
  if (res[2]!=0) res[2][1]=a2;
  a5=(-a5);
  if (res[2]!=0) res[2][2]=a5;
  a5=cos(a1);
  a5=(a0*a5);
  a1=sin(a1);
  a4=(a4*a1);
  a5=(a5-a4);
  if (res[2]!=0) res[2][3]=a5;
  if (res[2]!=0) res[2][4]=a3;
  if (res[2]!=0) res[2][5]=a7;
  if (res[2]!=0) res[2][6]=a37;
  a10=(a10*a9);
  a12=(a0*a12);
  a12=(a12+a13);
  a10=(a10+a12);
  a21=cos(a21);
  a12=casadi_sq(a19);
  a13=casadi_sq(a0);
  a12=(a12+a13);
  a19=(a19/a12);
  a19=(a16*a19);
  a20=casadi_sq(a20);
  a20=(a37+a20);
  a19=(a19/a20);
  a19=(a15*a19);
  a19=(a21*a19);
  a19=(a14*a19);
  a13=(a23*a19);
  a10=(a10+a13);
  a10=(a10/a24);
  a10=(-a10);
  if (res[2]!=0) res[2][7]=a10;
  a12=(a0/a12);
  a10=(a16*a12);
  a10=(a10/a20);
  a10=(a15*a10);
  a10=(a21*a10);
  a10=(a14*a10);
  a13=(a23*a10);
  a9=(a6*a24);
  a13=(a13+a9);
  a13=(a13/a24);
  if (res[2]!=0) res[2][8]=a13;
  a12=(a12*a18);
  a12=(a16*a12);
  a12=(a12/a20);
  a12=(a15*a12);
  a12=(a21*a12);
  a12=(a14*a12);
  a13=(a23*a12);
  a13=(a13+a25);
  a13=(a13/a24);
  if (res[2]!=0) res[2][9]=a13;
  a8=(a8/a24);
  if (res[2]!=0) res[2][10]=a8;
  a16=(a16/a20);
  a15=(a15*a16);
  a21=(a21*a15);
  a14=(a14*a21);
  a23=(a23*a14);
  a21=cos(a17);
  a21=(a22*a21);
  a23=(a23+a21);
  a23=(a23/a24);
  a23=(-a23);
  if (res[2]!=0) res[2][11]=a23;
  a23=(a33*a19);
  a31=cos(a31);
  a21=casadi_sq(a29);
  a15=casadi_sq(a0);
  a21=(a21+a15);
  a29=(a29/a21);
  a29=(a27*a29);
  a30=casadi_sq(a30);
  a37=(a37+a30);
  a29=(a29/a37);
  a29=(a26*a29);
  a29=(a31*a29);
  a29=(a11*a29);
  a23=(a23-a29);
  a6=(a6*a24);
  a23=(a23-a6);
  a23=(a23/a24);
  if (res[2]!=0) res[2][12]=a23;
  a0=(a0/a21);
  a21=(a27*a0);
  a21=(a21/a37);
  a21=(a26*a21);
  a21=(a31*a21);
  a21=(a11*a21);
  a23=(a33*a10);
  a23=(a21+a23);
  a23=(a23/a24);
  a23=(-a23);
  if (res[2]!=0) res[2][13]=a23;
  a0=(a0*a28);
  a27=(a27*a0);
  a27=(a27/a37);
  a26=(a26*a27);
  a31=(a31*a26);
  a11=(a11*a31);
  a31=(a33*a12);
  a31=(a11-a31);
  a31=(a31-a35);
  a31=(a31/a24);
  if (res[2]!=0) res[2][14]=a31;
  a33=(a33*a14);
  a31=sin(a17);
  a22=(a22*a31);
  a33=(a33-a22);
  a33=(a33/a24);
  if (res[2]!=0) res[2][15]=a33;
  a19=(a18*a19);
  a19=(a36*a19);
  a29=(a28*a29);
  a19=(a19+a29);
  a19=(a19/a32);
  if (res[2]!=0) res[2][16]=a19;
  a21=(a28*a21);
  a10=(a18*a10);
  a10=(a36*a10);
  a21=(a21-a10);
  a21=(a21/a32);
  if (res[2]!=0) res[2][17]=a21;
  a12=(a18*a12);
  a12=(a36*a12);
  a28=(a28*a11);
  a12=(a12+a28);
  a12=(a12/a32);
  a12=(-a12);
  if (res[2]!=0) res[2][18]=a12;
  a18=(a18*a14);
  a36=(a36*a18);
  a17=sin(a17);
  a34=(a34*a17);
  a36=(a36-a34);
  a36=(a36/a32);
  if (res[2]!=0) res[2][19]=a36;
  return 0;
}

int FORCESNLPsolver_cdyn_0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f1(arg, res, iw, w, mem);
}

int FORCESNLPsolver_cdyn_0_alloc_mem(void) {
  return 0;
}

int FORCESNLPsolver_cdyn_0_init_mem(int mem) {
  return 0;
}

void FORCESNLPsolver_cdyn_0_free_mem(int mem) {
}

int FORCESNLPsolver_cdyn_0_checkout(void) {
  return 0;
}

void FORCESNLPsolver_cdyn_0_release(int mem) {
}

void FORCESNLPsolver_cdyn_0_incref(void) {
}

void FORCESNLPsolver_cdyn_0_decref(void) {
}

casadi_int FORCESNLPsolver_cdyn_0_n_in(void) { return 3;}

casadi_int FORCESNLPsolver_cdyn_0_n_out(void) { return 3;}

casadi_real FORCESNLPsolver_cdyn_0_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

const char* FORCESNLPsolver_cdyn_0_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    default: return 0;
  }
}

const char* FORCESNLPsolver_cdyn_0_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    case 2: return "o2";
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_cdyn_0_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s4;
    case 1: return casadi_s5;
    case 2: return casadi_s1;
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_cdyn_0_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s4;
    case 1: return casadi_s6;
    case 2: return casadi_s7;
    default: return 0;
  }
}

int FORCESNLPsolver_cdyn_0_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 3;
  if (sz_res) *sz_res = 3;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}

/* FORCESNLPsolver_cdyn_0rd_0:(i0[9],i1[3],i2[26])->(o0[9]) */
static int casadi_f2(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real a0, a1, a10, a11, a2, a3, a4, a5, a6, a7, a8, a9;
  a0=arg[0]? arg[0][3] : 0;
  a1=arg[0]? arg[0][2] : 0;
  a2=cos(a1);
  a2=(a0*a2);
  a3=arg[0]? arg[0][4] : 0;
  a4=sin(a1);
  a4=(a3*a4);
  a2=(a2-a4);
  if (res[0]!=0) res[0][0]=a2;
  a2=sin(a1);
  a2=(a0*a2);
  a1=cos(a1);
  a1=(a3*a1);
  a2=(a2+a1);
  if (res[0]!=0) res[0][1]=a2;
  a2=arg[0]? arg[0][5] : 0;
  if (res[0]!=0) res[0][2]=a2;
  a1=arg[2]? arg[2][22] : 0;
  a4=arg[2]? arg[2][23] : 0;
  a4=(a4*a0);
  a1=(a1-a4);
  a4=arg[0]? arg[0][6] : 0;
  a1=(a1*a4);
  a4=arg[2]? arg[2][25] : 0;
  a1=(a1-a4);
  a4=arg[2]? arg[2][24] : 0;
  a4=(a4*a0);
  a4=(a4*a0);
  a1=(a1-a4);
  a4=arg[2]? arg[2][16] : 0;
  a5=arg[2]? arg[2][17] : 0;
  a6=arg[2]? arg[2][18] : 0;
  a7=arg[0]? arg[0][7] : 0;
  a8=arg[2]? arg[2][13] : 0;
  a9=(a2*a8);
  a9=(a9+a3);
  a9=atan2(a9,a0);
  a9=(a7-a9);
  a6=(a6*a9);
  a6=atan(a6);
  a5=(a5*a6);
  a5=sin(a5);
  a4=(a4*a5);
  a5=sin(a7);
  a5=(a4*a5);
  a1=(a1-a5);
  a5=arg[2]? arg[2][14] : 0;
  a6=(a5*a3);
  a6=(a6*a2);
  a1=(a1+a6);
  a1=(a1/a5);
  if (res[0]!=0) res[0][3]=a1;
  a1=arg[2]? arg[2][19] : 0;
  a6=arg[2]? arg[2][20] : 0;
  a9=arg[2]? arg[2][21] : 0;
  a10=arg[2]? arg[2][12] : 0;
  a11=(a2*a10);
  a11=(a11-a3);
  a11=atan2(a11,a0);
  a9=(a9*a11);
  a9=atan(a9);
  a6=(a6*a9);
  a6=sin(a6);
  a1=(a1*a6);
  a6=cos(a7);
  a6=(a4*a6);
  a6=(a1+a6);
  a0=(a5*a0);
  a0=(a0*a2);
  a6=(a6-a0);
  a6=(a6/a5);
  if (res[0]!=0) res[0][4]=a6;
  a4=(a4*a8);
  a7=cos(a7);
  a4=(a4*a7);
  a1=(a1*a10);
  a4=(a4-a1);
  a1=arg[2]? arg[2][15] : 0;
  a4=(a4/a1);
  if (res[0]!=0) res[0][5]=a4;
  a4=arg[1]? arg[1][0] : 0;
  if (res[0]!=0) res[0][6]=a4;
  a4=arg[1]? arg[1][1] : 0;
  if (res[0]!=0) res[0][7]=a4;
  a4=arg[1]? arg[1][2] : 0;
  if (res[0]!=0) res[0][8]=a4;
  return 0;
}

int FORCESNLPsolver_cdyn_0rd_0(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f2(arg, res, iw, w, mem);
}

int FORCESNLPsolver_cdyn_0rd_0_alloc_mem(void) {
  return 0;
}

int FORCESNLPsolver_cdyn_0rd_0_init_mem(int mem) {
  return 0;
}

void FORCESNLPsolver_cdyn_0rd_0_free_mem(int mem) {
}

int FORCESNLPsolver_cdyn_0rd_0_checkout(void) {
  return 0;
}

void FORCESNLPsolver_cdyn_0rd_0_release(int mem) {
}

void FORCESNLPsolver_cdyn_0rd_0_incref(void) {
}

void FORCESNLPsolver_cdyn_0rd_0_decref(void) {
}

casadi_int FORCESNLPsolver_cdyn_0rd_0_n_in(void) { return 3;}

casadi_int FORCESNLPsolver_cdyn_0rd_0_n_out(void) { return 1;}

casadi_real FORCESNLPsolver_cdyn_0rd_0_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

const char* FORCESNLPsolver_cdyn_0rd_0_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    case 2: return "i2";
    default: return 0;
  }
}

const char* FORCESNLPsolver_cdyn_0rd_0_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_cdyn_0rd_0_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s4;
    case 1: return casadi_s5;
    case 2: return casadi_s1;
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_cdyn_0rd_0_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s4;
    default: return 0;
  }
}

int FORCESNLPsolver_cdyn_0rd_0_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 3;
  if (sz_res) *sz_res = 1;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}

/* FORCESNLPsolver_objective_1:(i0[12],i1[26])->(o0,o1[1x12,6nz]) */
static int casadi_f3(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem) {
  casadi_real a0, a1, a10, a11, a12, a13, a14, a15, a16, a2, a3, a4, a5, a6, a7, a8, a9;
  a0=arg[1]? arg[1][5] : 0;
  a1=sin(a0);
  a2=arg[1]? arg[1][0] : 0;
  a0=cos(a0);
  a3=arg[0]? arg[0][11] : 0;
  a4=arg[1]? arg[1][4] : 0;
  a5=(a3-a4);
  a5=(a0*a5);
  a2=(a2+a5);
  a5=arg[0]? arg[0][3] : 0;
  a6=(a2-a5);
  a6=(a1*a6);
  a7=arg[1]? arg[1][1] : 0;
  a3=(a3-a4);
  a3=(a1*a3);
  a7=(a7+a3);
  a3=arg[0]? arg[0][4] : 0;
  a4=(a7-a3);
  a4=(a0*a4);
  a6=(a6-a4);
  a4=arg[1]? arg[1][6] : 0;
  a8=(a6*a4);
  a9=(a8*a6);
  a2=(a2-a5);
  a2=(a0*a2);
  a7=(a7-a3);
  a7=(a1*a7);
  a2=(a2+a7);
  a7=arg[1]? arg[1][7] : 0;
  a3=(a2*a7);
  a5=(a3*a2);
  a9=(a9+a5);
  a5=arg[1]? arg[1][11] : 0;
  a10=arg[0]? arg[0][2] : 0;
  a10=(a5*a10);
  a9=(a9-a10);
  a10=arg[0]? arg[0][0] : 0;
  a11=arg[1]? arg[1][8] : 0;
  a12=(a10*a11);
  a13=(a12*a10);
  a9=(a9+a13);
  a13=arg[0]? arg[0][1] : 0;
  a14=arg[1]? arg[1][9] : 0;
  a15=(a13*a14);
  a16=(a15*a13);
  a9=(a9+a16);
  if (res[0]!=0) res[0][0]=a9;
  a11=(a11*a10);
  a12=(a12+a11);
  if (res[1]!=0) res[1][0]=a12;
  a14=(a14*a13);
  a15=(a15+a14);
  if (res[1]!=0) res[1][1]=a15;
  a5=(-a5);
  if (res[1]!=0) res[1][2]=a5;
  a7=(a7*a2);
  a3=(a3+a7);
  a7=(a0*a3);
  a4=(a4*a6);
  a8=(a8+a4);
  a4=(a1*a8);
  a6=(a7+a4);
  a6=(-a6);
  if (res[1]!=0) res[1][3]=a6;
  a8=(a0*a8);
  a3=(a1*a3);
  a6=(a8-a3);
  if (res[1]!=0) res[1][4]=a6;
  a3=(a3-a8);
  a1=(a1*a3);
  a7=(a7+a4);
  a0=(a0*a7);
  a1=(a1+a0);
  if (res[1]!=0) res[1][5]=a1;
  return 0;
}

int FORCESNLPsolver_objective_1(const casadi_real** arg, casadi_real** res, casadi_int* iw, casadi_real* w, int mem){
  return casadi_f3(arg, res, iw, w, mem);
}

int FORCESNLPsolver_objective_1_alloc_mem(void) {
  return 0;
}

int FORCESNLPsolver_objective_1_init_mem(int mem) {
  return 0;
}

void FORCESNLPsolver_objective_1_free_mem(int mem) {
}

int FORCESNLPsolver_objective_1_checkout(void) {
  return 0;
}

void FORCESNLPsolver_objective_1_release(int mem) {
}

void FORCESNLPsolver_objective_1_incref(void) {
}

void FORCESNLPsolver_objective_1_decref(void) {
}

casadi_int FORCESNLPsolver_objective_1_n_in(void) { return 2;}

casadi_int FORCESNLPsolver_objective_1_n_out(void) { return 2;}

casadi_real FORCESNLPsolver_objective_1_default_in(casadi_int i){
  switch (i) {
    default: return 0;
  }
}

const char* FORCESNLPsolver_objective_1_name_in(casadi_int i){
  switch (i) {
    case 0: return "i0";
    case 1: return "i1";
    default: return 0;
  }
}

const char* FORCESNLPsolver_objective_1_name_out(casadi_int i){
  switch (i) {
    case 0: return "o0";
    case 1: return "o1";
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_objective_1_sparsity_in(casadi_int i) {
  switch (i) {
    case 0: return casadi_s0;
    case 1: return casadi_s1;
    default: return 0;
  }
}

const casadi_int* FORCESNLPsolver_objective_1_sparsity_out(casadi_int i) {
  switch (i) {
    case 0: return casadi_s2;
    case 1: return casadi_s3;
    default: return 0;
  }
}

int FORCESNLPsolver_objective_1_work(casadi_int *sz_arg, casadi_int* sz_res, casadi_int *sz_iw, casadi_int *sz_w) {
  if (sz_arg) *sz_arg = 2;
  if (sz_res) *sz_res = 2;
  if (sz_iw) *sz_iw = 0;
  if (sz_w) *sz_w = 0;
  return 0;
}


#ifdef __cplusplus
} /* extern "C" */
#endif
