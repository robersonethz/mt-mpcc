/*
FORCESNLPsolver : A fast customized optimization solver.

Copyright (C) 2013-2023 EMBOTECH AG [info@embotech.com]. All rights reserved.


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


#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME FORCESNLPsolver_simulinkBlockcompact

#include "simstruc.h"



/* include FORCESPRO functions and defs */
#include "../include/FORCESNLPsolver.h" 
#include "../include/FORCESNLPsolver_memory.h" 

#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

extern solver_int32_default (double *x, double *y, double *l, double *p, double *f, double *nabla_f, double *c, double *nabla_c, double *h, double *nabla_h, double *hess, solver_int32_default stage, solver_int32_default iteration, solver_int32_default threadID);
FORCESNLPsolver_extfunc pt2function_FORCESNLPsolver = &;


/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes =========================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) 
	{
		return; /* Parameter mismatch will be reported by Simulink */
    }

	/* initialize size of continuous and discrete states to zero */
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

	/* initialize input ports - there are 5 in total */
    if (!ssSetNumInputPorts(S, 5)) return;
    	
	/* Input Port 0 */
    ssSetInputPortMatrixDimensions(S,  0, 18, 1);
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 0, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/
	
	/* Input Port 1 */
    ssSetInputPortMatrixDimensions(S,  1, 1000, 1);
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 1, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 1, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/
	
	/* Input Port 2 */
    ssSetInputPortMatrixDimensions(S,  2, 1360, 1);
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 2, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 2, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/
	
	/* Input Port 3 */
    ssSetInputPortMatrixDimensions(S,  3, 1, 1);
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 3, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 3, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/
	
	/* Input Port 4 */
    ssSetInputPortMatrixDimensions(S,  4, 1, 1);
    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 4, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 4, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/
 


	/* initialize output ports - there are 1 in total */
    if (!ssSetNumOutputPorts(S, 1)) return;    
		
	/* Output Port 0 */
    ssSetOutputPortMatrixDimensions(S,  0, 1000, 1);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */


	/* set sampling time */
    ssSetNumSampleTimes(S, 1);

	/* set internal memory of block */
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
	/* SS_OPTION_USE_TLC_WITH_ACCELERATOR removed */ 
	/* SS_OPTION_USE_TLC_WITH_ACCELERATOR removed */ 
    /* ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
		             SS_OPTION_WORKS_WITH_CODE_REUSE)); */
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE );
}

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct        *S, 
                                         int_T            port,
                                         const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)
static void mdlSetOutputPortDimensionInfo(SimStruct        *S, 
                                          int_T            port, 
                                          const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif
# define MDL_SET_INPUT_PORT_FRAME_DATA
static void mdlSetInputPortFrameData(SimStruct  *S, 
                                     int_T      port,
                                     Frame_T    frameData)
{
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, solver_int32_default port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, solver_int32_default port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
    ssSetInputPortDataType( S, 0, SS_DOUBLE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}

/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
	solver_int32_default i, j, k;
	
	/* file pointer for printing */
	FILE *fp = NULL;

	/* Simulink data */
	const real_T *xinit = (const real_T*) ssGetInputPortSignal(S,0);
	const real_T *x0 = (const real_T*) ssGetInputPortSignal(S,1);
	const real_T *all_parameters = (const real_T*) ssGetInputPortSignal(S,2);
	const real_T *num_of_threads = (const real_T*) ssGetInputPortSignal(S,3);
	const real_T *receive_floating_license = (const real_T*) ssGetInputPortSignal(S,4);
	
    real_T *outputs = (real_T*) ssGetOutputPortSignal(S,0);
	

	/* Solver data */
	static FORCESNLPsolver_params params;
	static FORCESNLPsolver_output output;
	static FORCESNLPsolver_info info;
    static FORCESNLPsolver_mem * mem;
	solver_int32_default solver_exitflag;

	/* Copy inputs */
	for(i = 0; i < 18; i++)
	{
		params.xinit[i] = (double) xinit[i];
	}

	for(i = 0; i < 1000; i++)
	{
		params.x0[i] = (double) x0[i];
	}

	for(i = 0; i < 1360; i++)
	{
		params.all_parameters[i] = (double) all_parameters[i];
	}

	params.num_of_threads = (solver_int32_unsigned) num_of_threads[0];

	params.receive_floating_license = (solver_int32_default) receive_floating_license[0];

	

    #if SET_PRINTLEVEL_FORCESNLPsolver > 0
		/* Prepare file for printfs */
        fp = fopen("stdout_temp","w+");
		if( fp == NULL ) 
		{
			mexErrMsgTxt("freopen of stdout did not work.");
		}
		rewind(fp);
	#endif

    if (mem == NULL)
    {
        mem = FORCESNLPsolver_internal_mem(0);
    }

	/* Call solver */
	solver_exitflag = FORCESNLPsolver_solve(&params, &output, &info, mem, fp , pt2function_FORCESNLPsolver);

	#if SET_PRINTLEVEL_FORCESNLPsolver > 0
		/* Read contents of printfs printed to file */
		rewind(fp);
		while( (i = fgetc(fp)) != EOF ) 
		{
			ssPrintf("%c",i);
		}
		fclose(fp);
	#endif

	/* Copy outputs */
	for(i = 0; i < 25; i++)
	{
		outputs[i] = (real_T) output.x01[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[25 + i] = (real_T) output.x02[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[50 + i] = (real_T) output.x03[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[75 + i] = (real_T) output.x04[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[100 + i] = (real_T) output.x05[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[125 + i] = (real_T) output.x06[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[150 + i] = (real_T) output.x07[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[175 + i] = (real_T) output.x08[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[200 + i] = (real_T) output.x09[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[225 + i] = (real_T) output.x10[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[250 + i] = (real_T) output.x11[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[275 + i] = (real_T) output.x12[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[300 + i] = (real_T) output.x13[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[325 + i] = (real_T) output.x14[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[350 + i] = (real_T) output.x15[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[375 + i] = (real_T) output.x16[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[400 + i] = (real_T) output.x17[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[425 + i] = (real_T) output.x18[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[450 + i] = (real_T) output.x19[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[475 + i] = (real_T) output.x20[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[500 + i] = (real_T) output.x21[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[525 + i] = (real_T) output.x22[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[550 + i] = (real_T) output.x23[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[575 + i] = (real_T) output.x24[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[600 + i] = (real_T) output.x25[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[625 + i] = (real_T) output.x26[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[650 + i] = (real_T) output.x27[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[675 + i] = (real_T) output.x28[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[700 + i] = (real_T) output.x29[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[725 + i] = (real_T) output.x30[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[750 + i] = (real_T) output.x31[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[775 + i] = (real_T) output.x32[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[800 + i] = (real_T) output.x33[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[825 + i] = (real_T) output.x34[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[850 + i] = (real_T) output.x35[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[875 + i] = (real_T) output.x36[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[900 + i] = (real_T) output.x37[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[925 + i] = (real_T) output.x38[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[950 + i] = (real_T) output.x39[i];
	}

	for(i = 0; i < 25; i++)
	{
		outputs[975 + i] = (real_T) output.x40[i];
	}

	
}


/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


