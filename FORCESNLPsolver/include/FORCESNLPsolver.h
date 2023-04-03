/*
FORCESNLPsolver : A fast customized optimization solver.

Copyright (C) 2013-2022 EMBOTECH AG [info@embotech.com]. All rights reserved.


This software is intended for simulation and testing purposes only. 
Use of this software for any commercial purpose is prohibited.

This program is distributed in the hope that it will be useful.
EMBOTECH makes NO WARRANTIES with respect to the use of the software 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. 

EMBOTECH shall not have any liability for any damage arising from the use
of the software.

This Agreement shall exclusively be governed by and interpreted in 
accordance with the laws of Switzerland, excluding its principles
of conflict of laws. The Courts of Zurich-City shall have exclusive 
jurisdiction in case of any dispute.

*/

/* Generated by FORCESPRO v6.0.1 on Monday, April 3, 2023 at 12:32:09 PM */
#ifndef FORCESNLPsolver_H
#define FORCESNLPsolver_H

#ifndef SOLVER_STDIO_H
#define SOLVER_STDIO_H
#include <stdio.h>
#endif
#ifndef SOLVER_STRING_H
#define SOLVER_STRING_H
#include <string.h>
#endif


#ifndef SOLVER_STANDARD_TYPES
#define SOLVER_STANDARD_TYPES

typedef signed char solver_int8_signed;
typedef unsigned char solver_int8_unsigned;
typedef char solver_int8_default;
typedef signed short int solver_int16_signed;
typedef unsigned short int solver_int16_unsigned;
typedef short int solver_int16_default;
typedef signed int solver_int32_signed;
typedef unsigned int solver_int32_unsigned;
typedef int solver_int32_default;
typedef signed long long int solver_int64_signed;
typedef unsigned long long int solver_int64_unsigned;
typedef long long int solver_int64_default;

#endif


/* DATA TYPE ------------------------------------------------------------*/
typedef double FORCESNLPsolver_float;
typedef double FORCESNLPsolver_ldl_s_float;
typedef double FORCESNLPsolver_ldl_r_float;
typedef double FORCESNLPsolver_callback_float;

typedef double FORCESNLPsolverinterface_float;

/* SOLVER SETTINGS ------------------------------------------------------*/

/* MISRA-C compliance */
#ifndef MISRA_C_FORCESNLPsolver
#define MISRA_C_FORCESNLPsolver (0)
#endif

/* restrict code */
#ifndef RESTRICT_CODE_FORCESNLPsolver
#define RESTRICT_CODE_FORCESNLPsolver (0)
#endif

/* print level */
#ifndef SET_PRINTLEVEL_FORCESNLPsolver
#define SET_PRINTLEVEL_FORCESNLPsolver    (0)
#endif

/* timing */
#ifndef SET_TIMING_FORCESNLPsolver
#define SET_TIMING_FORCESNLPsolver    (1)
#endif

/* Numeric Warnings */
/* #define PRINTNUMERICALWARNINGS */

/* maximum number of iterations  */
#define SET_MAXIT_FORCESNLPsolver			(20)	

/* scaling factor of line search (FTB rule) */
#define SET_FLS_SCALE_FORCESNLPsolver		(FORCESNLPsolver_float)(0.99)      

/* maximum number of supported elements in the filter */
#define MAX_FILTER_SIZE_FORCESNLPsolver	(20) 

/* maximum number of supported elements in the filter */
#define MAX_SOC_IT_FORCESNLPsolver			(4) 

/* desired relative duality gap */
#define SET_ACC_RDGAP_FORCESNLPsolver		(FORCESNLPsolver_float)(0.0001)

/* desired maximum residual on equality constraints */
#define SET_ACC_RESEQ_FORCESNLPsolver		(FORCESNLPsolver_float)(1E-06)

/* desired maximum residual on inequality constraints */
#define SET_ACC_RESINEQ_FORCESNLPsolver	(FORCESNLPsolver_float)(1E-06)

/* desired maximum violation of complementarity */
#define SET_ACC_KKTCOMPL_FORCESNLPsolver	(FORCESNLPsolver_float)(1E-06)


/* SOLVER RETURN CODES----------------------------------------------------------*/
/* solver has converged within desired accuracy */
#define OPTIMAL_FORCESNLPsolver      (1)

/* maximum number of iterations has been reached */
#define MAXITREACHED_FORCESNLPsolver (0)

/* solver has stopped due to a timeout */
#define TIMEOUT_FORCESNLPsolver   (2)

/* solver stopped externally */
#define EXIT_EXTERNAL_FORCESNLPsolver (3)

/* wrong number of inequalities error */
#define INVALID_NUM_INEQ_ERROR_FORCESNLPsolver  (-4)

/* factorization error */
#define FACTORIZATION_ERROR_FORCESNLPsolver   (-5)

/* NaN encountered in function evaluations */
#define BADFUNCEVAL_FORCESNLPsolver  (-6)

/* no progress in method possible */
#define NOPROGRESS_FORCESNLPsolver   (-7)

/* regularization error */
#define REGULARIZATION_ERROR_FORCESNLPsolver   (-9)

/* invalid values in parameters */
#define PARAM_VALUE_ERROR_FORCESNLPsolver   (-11)

/* too small timeout given */
#define INVALID_TIMEOUT_FORCESNLPsolver   (-12)

/* thread error */
#define THREAD_FAILURE_FORCESNLPsolver  (-98)

/* locking mechanism error */
#define LOCK_FAILURE_FORCESNLPsolver  (-99)

/* licensing error - solver not valid on this machine */
#define LICENSE_ERROR_FORCESNLPsolver  (-100)

/* Insufficient number of internal memory instances.
 * Increase codeoptions.max_num_mem. */
#define MEMORY_INVALID_FORCESNLPsolver (-101)
/* Number of threads larger than specified.
 * Increase codeoptions.nlp.max_num_threads. */
#define NUMTHREADS_INVALID_FORCESNLPsolver (-102)

/* INTEGRATORS RETURN CODE ------------*/
/* Integrator ran successfully */
#define INTEGRATOR_SUCCESS (11)
/* Number of steps set by user exceeds maximum number of steps allowed */
#define INTEGRATOR_MAXSTEPS_EXCEEDED (12)


/* MEMORY STRUCT --------------------------------------------------------*/
typedef struct FORCESNLPsolver_mem FORCESNLPsolver_mem;
#ifdef __cplusplus
extern "C" {
#endif
/* MEMORY STRUCT --------------------------------------------------------*/
extern FORCESNLPsolver_mem * FORCESNLPsolver_external_mem(void * mem_ptr, solver_int32_unsigned i_mem, size_t mem_size);
extern size_t FORCESNLPsolver_get_mem_size( void );
extern size_t FORCESNLPsolver_get_const_size( void );
#ifdef __cplusplus
}
#endif

/* PARAMETERS -----------------------------------------------------------*/
/* fill this with data before calling the solver! */
typedef struct
{
    /* vector of size 18 */
    FORCESNLPsolver_float xinit[18];

    /* vector of size 960 */
    FORCESNLPsolver_float x0[960];

    /* vector of size 1280 */
    FORCESNLPsolver_float all_parameters[1280];

    /* scalar */
    solver_int32_unsigned num_of_threads;

    /* scalar */
    solver_int32_default receive_floating_license;


} FORCESNLPsolver_params;


/* OUTPUTS --------------------------------------------------------------*/
/* the desired variables are put here by the solver */
typedef struct
{
    /* column vector of length 24 */
    FORCESNLPsolver_float x01[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x02[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x03[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x04[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x05[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x06[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x07[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x08[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x09[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x10[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x11[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x12[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x13[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x14[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x15[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x16[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x17[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x18[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x19[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x20[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x21[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x22[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x23[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x24[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x25[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x26[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x27[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x28[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x29[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x30[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x31[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x32[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x33[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x34[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x35[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x36[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x37[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x38[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x39[24];

    /* column vector of length 24 */
    FORCESNLPsolver_float x40[24];


} FORCESNLPsolver_output;


/* SOLVER INFO ----------------------------------------------------------*/
/* diagnostic data from last interior point step */
typedef struct
{
    /* scalar: iteration number */
    solver_int32_default it;

    /* scalar: number of iterations needed to optimality (branch-and-bound) */
    solver_int32_default it2opt;

    /* scalar: inf-norm of equality constraint residuals */
    FORCESNLPsolver_float res_eq;

    /* scalar: inf-norm of inequality constraint residuals */
    FORCESNLPsolver_float res_ineq;

    /* scalar: norm of stationarity condition */
    FORCESNLPsolver_float rsnorm;

    /* scalar: max of all complementarity violations */
    FORCESNLPsolver_float rcompnorm;

    /* scalar: primal objective */
    FORCESNLPsolver_float pobj;

    /* scalar: dual objective */
    FORCESNLPsolver_float dobj;

    /* scalar: duality gap := pobj - dobj */
    FORCESNLPsolver_float dgap;

    /* scalar: relative duality gap := |dgap / pobj | */
    FORCESNLPsolver_float rdgap;

    /* scalar: duality measure */
    FORCESNLPsolver_float mu;

    /* scalar: duality measure (after affine step) */
    FORCESNLPsolver_float mu_aff;

    /* scalar: centering parameter */
    FORCESNLPsolver_float sigma;

    /* scalar: number of backtracking line search steps (affine direction) */
    solver_int32_default lsit_aff;

    /* scalar: number of backtracking line search steps (combined direction) */
    solver_int32_default lsit_cc;

    /* scalar: step size (affine direction) */
    FORCESNLPsolver_float step_aff;

    /* scalar: step size (combined direction) */
    FORCESNLPsolver_float step_cc;

    /* scalar: total solve time */
    FORCESNLPsolver_float solvetime;

    /* scalar: time spent in function evaluations */
    FORCESNLPsolver_float fevalstime;

    /* column vector of length 8: solver ID of FORCESPRO solver */
    solver_int32_default solver_id[8];




} FORCESNLPsolver_info;







/* SOLVER FUNCTION DEFINITION -------------------------------------------*/
/* Time of Solver Generation: (UTC) Monday, April 3, 2023 12:32:13 PM */
/* User License expires on: (UTC) Wednesday, August 2, 2023 10:00:00 PM (approx.) (at the time of code generation) */
/* Solver Static License expires on: (UTC) Wednesday, August 2, 2023 10:00:00 PM (approx.) */
/* Solver Id: 4d0d2b0c-8473-48ea-b03c-d678dc384896 */
/* examine exitflag before using the result! */
#ifdef __cplusplus
extern "C" {
#endif		

typedef solver_int32_default (*FORCESNLPsolver_extfunc)(FORCESNLPsolver_float* x, FORCESNLPsolver_float* y, FORCESNLPsolver_float* lambda, FORCESNLPsolver_float* params, FORCESNLPsolver_float* pobj, FORCESNLPsolver_float* g, FORCESNLPsolver_float* c, FORCESNLPsolver_float* Jeq, FORCESNLPsolver_float* h, FORCESNLPsolver_float* Jineq, FORCESNLPsolver_float* H, solver_int32_default stage, solver_int32_default iterations, solver_int32_default threadID);

extern solver_int32_default FORCESNLPsolver_solve(FORCESNLPsolver_params *params, FORCESNLPsolver_output *output, FORCESNLPsolver_info *info, FORCESNLPsolver_mem *mem, FILE *fs, FORCESNLPsolver_extfunc evalextfunctions_FORCESNLPsolver);



/*Integrator declarations */
typedef const solver_int32_default* (*cDynJacXsparsity)( solver_int32_default i );
typedef const solver_int32_default* (*cDynJacUsparsity)( solver_int32_default i );
typedef solver_int32_default (*fConDynamics)( const FORCESNLPsolver_callback_float** arg, FORCESNLPsolver_callback_float** res, solver_int32_default* iw, FORCESNLPsolver_callback_float* w, solver_int32_default mem );
typedef solver_int32_default (*fConJacStateDynamics)( const FORCESNLPsolver_callback_float** arg, FORCESNLPsolver_callback_float** res, solver_int32_default* iw, FORCESNLPsolver_callback_float* w, solver_int32_default mem );
typedef solver_int32_default (*fConJacInputDynamics)( const FORCESNLPsolver_callback_float** arg, FORCESNLPsolver_callback_float** res, solver_int32_default* iw, FORCESNLPsolver_callback_float* w, solver_int32_default mem );

void FORCESNLPsolver_rkfour_0(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_1(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_2(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_3(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_4(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_5(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_6(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_7(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_8(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_9(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_10(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_11(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_12(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_13(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_14(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_15(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_16(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_17(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_18(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_19(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_20(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_21(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_22(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_23(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_24(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_25(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_26(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_27(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_28(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_29(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_30(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_31(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_32(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_33(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_34(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_35(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_36(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_37(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);


void FORCESNLPsolver_rkfour_38(const FORCESNLPsolver_callback_float * const z, const FORCESNLPsolver_callback_float * const p, FORCESNLPsolver_float * const c, FORCESNLPsolver_float * const jacc,
            fConDynamics cDyn0rd, fConDynamics cDyn, const solver_int32_default threadID);









#ifdef __cplusplus
}
#endif

#endif
