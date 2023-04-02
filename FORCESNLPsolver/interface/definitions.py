import numpy
import ctypes

name = "FORCESNLPsolver"
requires_callback = True
lib = "lib/libFORCESNLPsolver.so"
lib_static = "lib/libFORCESNLPsolver.a"
c_header = "include/FORCESNLPsolver.h"
nstages = 20

# Parameter             | Type    | Scalar type      | Ctypes type    | Numpy type   | Shape     | Len
params = \
[("xinit"               , "dense" , ""               , ctypes.c_double, numpy.float64, ( 18,   1),   18),
 ("x0"                  , "dense" , ""               , ctypes.c_double, numpy.float64, (480,   1),  480),
 ("all_parameters"      , "dense" , ""               , ctypes.c_double, numpy.float64, (640,   1),  640),
 ("num_of_threads"      , "dense" , "solver_int32_unsigned", ctypes.c_uint  , numpy.uint32 , (  1,   1),    1),
 ("receive_floating_license", "dense" , "solver_int32_default", ctypes.c_int   , numpy.int32  , (  1,   1),    1)]

# Output                | Type    | Ctypes type    | Numpy type   | Shape     | Len
outputs = \
[("x01"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x02"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x03"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x04"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x05"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x06"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x07"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x08"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x09"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x10"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x11"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x12"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x13"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x14"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x15"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x16"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x17"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x18"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x19"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24),
 ("x20"                 , ""               , ctypes.c_double, numpy.float64,     ( 24,),   24)]

# Info Struct Fields
info = \
[('it', ctypes.c_int),
 ('it2opt', ctypes.c_int),
 ('res_eq', ctypes.c_double),
 ('res_ineq', ctypes.c_double),
 ('rsnorm', ctypes.c_double),
 ('rcompnorm', ctypes.c_double),
 ('pobj', ctypes.c_double),
 ('dobj', ctypes.c_double),
 ('dgap', ctypes.c_double),
 ('rdgap', ctypes.c_double),
 ('mu', ctypes.c_double),
 ('mu_aff', ctypes.c_double),
 ('sigma', ctypes.c_double),
 ('lsit_aff', ctypes.c_int),
 ('lsit_cc', ctypes.c_int),
 ('step_aff', ctypes.c_double),
 ('step_cc', ctypes.c_double),
 ('solvetime', ctypes.c_double),
 ('fevalstime', ctypes.c_double),
 ('solver_id', ctypes.c_int * 8)
]

# Dynamics dimensions
#   nvar    |   neq   |   dimh    |   dimp    |   diml    |   dimu    |   dimhl   |   dimhu    
dynamics_dims = [
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1), 
	(24, 18, 1, 32, 24, 24, 1, 1)
]