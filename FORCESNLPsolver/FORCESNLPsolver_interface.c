/*
 * AD tool to FORCESPRO Template - missing information to be filled in by createADTool.m 
 * (C) embotech AG, Zurich, Switzerland, 2013-2023. All rights reserved.
 *
 * This file is part of the FORCESPRO client, and carries the same license.
 */ 

#ifdef __cplusplus
extern "C" {
#endif
    
#include "include/FORCESNLPsolver.h"

#ifndef NULL
#define NULL ((void *) 0)
#endif

#include "FORCESNLPsolver_model.h"



/* copies data from sparse matrix into a dense one */
static void FORCESNLPsolver_sparse2fullcopy(solver_int32_default nrow, solver_int32_default ncol, const solver_int32_default *colidx, const solver_int32_default *row, FORCESNLPsolver_callback_float *data, FORCESNLPsolver_float *out)
{
    solver_int32_default i, j;
    
    /* copy data into dense matrix */
    for(i=0; i<ncol; i++)
    {
        for(j=colidx[i]; j<colidx[i+1]; j++)
        {
            out[i*nrow + row[j]] = ((FORCESNLPsolver_float) data[j]);
        }
    }
}




/* AD tool to FORCESPRO interface */
extern solver_int32_default FORCESNLPsolver_adtool2forces(FORCESNLPsolver_float *x,        /* primal vars                                         */
                                 FORCESNLPsolver_float *y,        /* eq. constraint multiplers                           */
                                 FORCESNLPsolver_float *l,        /* ineq. constraint multipliers                        */
                                 FORCESNLPsolver_float *p,        /* parameters                                          */
                                 FORCESNLPsolver_float *f,        /* objective function (scalar)                         */
                                 FORCESNLPsolver_float *nabla_f,  /* gradient of objective function                      */
                                 FORCESNLPsolver_float *c,        /* dynamics                                            */
                                 FORCESNLPsolver_float *nabla_c,  /* Jacobian of the dynamics (column major)             */
                                 FORCESNLPsolver_float *h,        /* inequality constraints                              */
                                 FORCESNLPsolver_float *nabla_h,  /* Jacobian of inequality constraints (column major)   */
                                 FORCESNLPsolver_float *hess,     /* Hessian (column major)                              */
                                 solver_int32_default stage,     /* stage number (0 indexed)                           */
								 solver_int32_default iteration, /* iteration number of solver                         */
								 solver_int32_default threadID   /* Id of caller thread                                */)
{
    /* AD tool input and output arrays */
    const FORCESNLPsolver_callback_float *in[4];
    FORCESNLPsolver_callback_float *out[7];
    

    /* Allocate working arrays for AD tool */
    
    FORCESNLPsolver_callback_float w[65];
	
    /* temporary storage for AD tool sparse output */
    FORCESNLPsolver_callback_float this_f = (FORCESNLPsolver_callback_float) 0.0;
    FORCESNLPsolver_float nabla_f_sparse[13];
    FORCESNLPsolver_float h_sparse[5];
    FORCESNLPsolver_float nabla_h_sparse[11];
    FORCESNLPsolver_float c_sparse[1];
    FORCESNLPsolver_float nabla_c_sparse[1];
            
    
    /* pointers to row and column info for 
     * column compressed format used by AD tool */
    solver_int32_default nrow, ncol;
    const solver_int32_default *colind, *row;
    
    /* set inputs for AD tool */
    in[0] = x;
    in[1] = p;
    in[2] = l;
    in[3] = y;

	if ((0 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_0(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_0_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_0_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_0_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_0_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_0(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_0, FORCESNLPsolver_cdyn_0, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_0(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_0_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_0_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_0_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_0_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_0_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_0_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_0_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_0_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((1 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_1(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_1_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_1_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_1_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_1_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_1(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_1, FORCESNLPsolver_cdyn_1, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_1(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_1_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_1_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_1_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_1_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_1_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_1_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_1_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_1_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((2 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_2(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_2_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_2_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_2_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_2_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_2(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_2, FORCESNLPsolver_cdyn_2, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_2(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_2_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_2_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_2_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_2_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_2_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_2_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_2_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_2_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((3 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_3(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_3_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_3_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_3_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_3_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_3(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_3, FORCESNLPsolver_cdyn_3, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_3(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_3_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_3_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_3_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_3_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_3_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_3_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_3_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_3_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((4 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_4(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_4_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_4_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_4_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_4_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_4(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_4, FORCESNLPsolver_cdyn_4, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_4(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_4_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_4_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_4_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_4_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_4_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_4_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_4_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_4_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((5 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_5(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_5_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_5_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_5_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_5_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_5(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_5, FORCESNLPsolver_cdyn_5, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_5(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_5_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_5_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_5_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_5_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_5_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_5_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_5_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_5_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((6 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_6(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_6_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_6_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_6_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_6_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_6(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_6, FORCESNLPsolver_cdyn_6, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_6(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_6_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_6_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_6_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_6_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_6_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_6_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_6_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_6_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((7 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_7(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_7_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_7_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_7_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_7_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_7(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_7, FORCESNLPsolver_cdyn_7, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_7(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_7_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_7_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_7_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_7_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_7_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_7_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_7_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_7_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((8 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_8(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_8_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_8_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_8_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_8_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_8(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_8, FORCESNLPsolver_cdyn_8, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_8(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_8_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_8_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_8_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_8_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_8_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_8_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_8_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_8_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((9 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_9(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_9_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_9_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_9_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_9_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_9(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_9, FORCESNLPsolver_cdyn_9, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_9(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_9_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_9_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_9_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_9_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_9_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_9_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_9_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_9_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((10 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_10(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_10_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_10_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_10_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_10_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_10(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_10, FORCESNLPsolver_cdyn_10, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_10(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_10_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_10_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_10_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_10_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_10_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_10_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_10_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_10_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((11 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_11(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_11_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_11_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_11_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_11_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_11(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_11, FORCESNLPsolver_cdyn_11, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_11(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_11_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_11_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_11_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_11_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_11_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_11_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_11_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_11_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((12 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_12(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_12_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_12_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_12_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_12_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_12(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_12, FORCESNLPsolver_cdyn_12, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_12(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_12_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_12_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_12_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_12_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_12_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_12_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_12_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_12_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((13 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_13(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_13_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_13_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_13_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_13_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_13(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_13, FORCESNLPsolver_cdyn_13, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_13(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_13_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_13_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_13_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_13_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_13_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_13_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_13_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_13_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((14 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_14(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_14_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_14_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_14_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_14_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_14(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_14, FORCESNLPsolver_cdyn_14, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_14(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_14_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_14_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_14_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_14_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_14_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_14_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_14_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_14_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((15 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_15(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_15_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_15_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_15_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_15_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_15(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_15, FORCESNLPsolver_cdyn_15, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_15(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_15_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_15_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_15_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_15_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_15_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_15_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_15_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_15_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((16 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_16(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_16_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_16_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_16_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_16_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_16(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_16, FORCESNLPsolver_cdyn_16, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_16(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_16_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_16_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_16_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_16_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_16_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_16_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_16_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_16_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((17 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_17(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_17_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_17_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_17_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_17_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_17(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_17, FORCESNLPsolver_cdyn_17, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_17(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_17_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_17_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_17_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_17_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_17_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_17_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_17_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_17_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((18 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_18(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_18_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_18_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_18_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_18_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_18(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_18, FORCESNLPsolver_cdyn_18, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_18(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_18_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_18_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_18_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_18_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_18_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_18_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_18_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_18_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((19 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_19(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_19_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_19_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_19_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_19_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_19(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_19, FORCESNLPsolver_cdyn_19, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_19(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_19_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_19_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_19_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_19_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_19_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_19_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_19_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_19_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((20 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_20(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_20_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_20_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_20_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_20_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_20(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_20, FORCESNLPsolver_cdyn_20, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_20(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_20_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_20_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_20_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_20_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_20_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_20_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_20_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_20_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((21 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_21(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_21_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_21_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_21_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_21_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_21(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_21, FORCESNLPsolver_cdyn_21, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_21(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_21_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_21_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_21_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_21_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_21_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_21_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_21_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_21_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((22 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_22(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_22_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_22_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_22_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_22_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_22(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_22, FORCESNLPsolver_cdyn_22, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_22(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_22_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_22_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_22_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_22_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_22_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_22_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_22_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_22_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((23 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_23(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_23_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_23_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_23_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_23_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_23(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_23, FORCESNLPsolver_cdyn_23, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_23(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_23_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_23_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_23_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_23_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_23_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_23_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_23_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_23_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((24 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_24(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_24_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_24_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_24_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_24_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_24(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_24, FORCESNLPsolver_cdyn_24, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_24(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_24_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_24_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_24_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_24_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_24_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_24_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_24_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_24_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((25 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_25(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_25_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_25_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_25_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_25_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_25(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_25, FORCESNLPsolver_cdyn_25, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_25(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_25_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_25_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_25_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_25_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_25_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_25_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_25_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_25_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((26 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_26(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_26_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_26_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_26_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_26_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_26(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_26, FORCESNLPsolver_cdyn_26, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_26(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_26_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_26_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_26_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_26_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_26_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_26_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_26_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_26_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((27 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_27(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_27_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_27_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_27_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_27_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_27(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_27, FORCESNLPsolver_cdyn_27, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_27(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_27_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_27_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_27_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_27_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_27_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_27_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_27_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_27_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((28 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_28(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_28_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_28_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_28_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_28_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_28(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_28, FORCESNLPsolver_cdyn_28, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_28(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_28_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_28_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_28_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_28_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_28_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_28_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_28_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_28_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((29 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_29(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_29_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_29_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_29_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_29_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_29(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_29, FORCESNLPsolver_cdyn_29, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_29(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_29_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_29_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_29_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_29_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_29_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_29_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_29_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_29_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((30 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_30(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_30_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_30_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_30_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_30_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_30(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_30, FORCESNLPsolver_cdyn_30, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_30(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_30_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_30_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_30_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_30_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_30_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_30_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_30_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_30_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((31 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_31(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_31_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_31_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_31_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_31_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_31(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_31, FORCESNLPsolver_cdyn_31, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_31(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_31_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_31_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_31_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_31_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_31_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_31_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_31_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_31_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((32 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_32(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_32_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_32_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_32_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_32_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_32(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_32, FORCESNLPsolver_cdyn_32, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_32(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_32_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_32_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_32_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_32_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_32_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_32_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_32_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_32_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((33 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_33(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_33_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_33_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_33_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_33_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_33(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_33, FORCESNLPsolver_cdyn_33, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_33(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_33_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_33_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_33_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_33_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_33_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_33_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_33_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_33_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((34 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_34(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_34_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_34_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_34_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_34_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_34(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_34, FORCESNLPsolver_cdyn_34, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_34(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_34_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_34_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_34_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_34_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_34_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_34_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_34_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_34_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((35 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_35(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_35_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_35_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_35_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_35_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_35(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_35, FORCESNLPsolver_cdyn_35, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_35(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_35_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_35_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_35_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_35_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_35_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_35_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_35_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_35_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((36 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_36(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_36_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_36_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_36_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_36_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_36(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_36, FORCESNLPsolver_cdyn_36, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_36(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_36_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_36_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_36_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_36_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_36_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_36_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_36_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_36_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((37 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_37(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_37_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_37_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_37_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_37_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_37(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_37, FORCESNLPsolver_cdyn_37, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_37(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_37_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_37_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_37_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_37_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_37_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_37_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_37_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_37_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((38 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_38(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_38_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_38_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_38_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_38_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		FORCESNLPsolver_rkfour_38(x, p, c, nabla_c, FORCESNLPsolver_cdyn_0rd_38, FORCESNLPsolver_cdyn_38, threadID);
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_38(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_38_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_38_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_38_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_38_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_38_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_38_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_38_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_38_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
	if ((39 == stage))
	{
		
		
		out[0] = &this_f;
		out[1] = nabla_f_sparse;
		FORCESNLPsolver_objective_39(in, out, NULL, w, 0);
		if( nabla_f )
		{
			nrow = FORCESNLPsolver_objective_39_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_objective_39_sparsity_out(1)[1];
			colind = FORCESNLPsolver_objective_39_sparsity_out(1) + 2;
			row = FORCESNLPsolver_objective_39_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_f_sparse, nabla_f);
		}
		
		out[0] = h_sparse;
		out[1] = nabla_h_sparse;
		FORCESNLPsolver_inequalities_39(in, out, NULL, w, 0);
		if( h )
		{
			nrow = FORCESNLPsolver_inequalities_39_sparsity_out(0)[0];
			ncol = FORCESNLPsolver_inequalities_39_sparsity_out(0)[1];
			colind = FORCESNLPsolver_inequalities_39_sparsity_out(0) + 2;
			row = FORCESNLPsolver_inequalities_39_sparsity_out(0) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, h_sparse, h);
		}
		if( nabla_h )
		{
			nrow = FORCESNLPsolver_inequalities_39_sparsity_out(1)[0];
			ncol = FORCESNLPsolver_inequalities_39_sparsity_out(1)[1];
			colind = FORCESNLPsolver_inequalities_39_sparsity_out(1) + 2;
			row = FORCESNLPsolver_inequalities_39_sparsity_out(1) + 2 + (ncol + 1);
			FORCESNLPsolver_sparse2fullcopy(nrow, ncol, colind, row, nabla_h_sparse, nabla_h);
		}
	}
    
    /* add to objective */
    if (f != NULL)
    {
        *f += ((FORCESNLPsolver_float) this_f);
    }

    return 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif
