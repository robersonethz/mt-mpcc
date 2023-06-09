import numpy
import ctypes

name = "FORCESNLPsolver"
requires_callback = True
lib = "lib/libFORCESNLPsolver.so"
lib_static = "lib/libFORCESNLPsolver.a"
c_header = "include/FORCESNLPsolver.h"
nstages = 40

# Parameter             | Type    | Scalar type      | Ctypes type    | Numpy type   | Shape     | Len
params = \
[("xinit"               , "dense" , ""               , ctypes.c_double, numpy.float64, ( 18,   1),   18),
 ("x0"                  , "dense" , ""               , ctypes.c_double, numpy.float64, (1120,   1), 1120),
 ("all_parameters"      , "dense" , ""               , ctypes.c_double, numpy.float64, (1360,   1), 1360),
 ("num_of_threads"      , "dense" , "solver_int32_unsigned", ctypes.c_uint  , numpy.uint32 , (  1,   1),    1),
 ("receive_floating_license", "dense" , "solver_int32_default", ctypes.c_int   , numpy.int32  , (  1,   1),    1)]

# Output                | Type    | Ctypes type    | Numpy type   | Shape     | Len
outputs = \
[("x01"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x02"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x03"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x04"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x05"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x06"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x07"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x08"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x09"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x10"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x11"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x12"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x13"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x14"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x15"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x16"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x17"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x18"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x19"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x20"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x21"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x22"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x23"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x24"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x25"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x26"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x27"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x28"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x29"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x30"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x31"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x32"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x33"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x34"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x35"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x36"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x37"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x38"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x39"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28),
 ("x40"                 , ""               , ctypes.c_double, numpy.float64,     ( 28,),   28)]

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
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1), 
	(28, 18, 1, 34, 28, 28, 1, 1)
]