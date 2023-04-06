% FORCESNLPsolver - a fast solver generated by FORCESPRO v6.1.0
%
%   OUTPUT = FORCESNLPsolver(PARAMS) solves a multistage problem
%   subject to the parameters supplied in the following struct:
%       PARAMS.xinit - matrix of size [9x1]
%       PARAMS.x0 - matrix of size [480x1]
%       PARAMS.all_parameters - matrix of size [1040x1]
%       PARAMS.num_of_threads - scalar
%       PARAMS.receive_floating_license - scalar
%
%   OUTPUT returns the values of the last iteration of the solver where
%       OUTPUT.x01 - column vector of length 12
%       OUTPUT.x02 - column vector of length 12
%       OUTPUT.x03 - column vector of length 12
%       OUTPUT.x04 - column vector of length 12
%       OUTPUT.x05 - column vector of length 12
%       OUTPUT.x06 - column vector of length 12
%       OUTPUT.x07 - column vector of length 12
%       OUTPUT.x08 - column vector of length 12
%       OUTPUT.x09 - column vector of length 12
%       OUTPUT.x10 - column vector of length 12
%       OUTPUT.x11 - column vector of length 12
%       OUTPUT.x12 - column vector of length 12
%       OUTPUT.x13 - column vector of length 12
%       OUTPUT.x14 - column vector of length 12
%       OUTPUT.x15 - column vector of length 12
%       OUTPUT.x16 - column vector of length 12
%       OUTPUT.x17 - column vector of length 12
%       OUTPUT.x18 - column vector of length 12
%       OUTPUT.x19 - column vector of length 12
%       OUTPUT.x20 - column vector of length 12
%       OUTPUT.x21 - column vector of length 12
%       OUTPUT.x22 - column vector of length 12
%       OUTPUT.x23 - column vector of length 12
%       OUTPUT.x24 - column vector of length 12
%       OUTPUT.x25 - column vector of length 12
%       OUTPUT.x26 - column vector of length 12
%       OUTPUT.x27 - column vector of length 12
%       OUTPUT.x28 - column vector of length 12
%       OUTPUT.x29 - column vector of length 12
%       OUTPUT.x30 - column vector of length 12
%       OUTPUT.x31 - column vector of length 12
%       OUTPUT.x32 - column vector of length 12
%       OUTPUT.x33 - column vector of length 12
%       OUTPUT.x34 - column vector of length 12
%       OUTPUT.x35 - column vector of length 12
%       OUTPUT.x36 - column vector of length 12
%       OUTPUT.x37 - column vector of length 12
%       OUTPUT.x38 - column vector of length 12
%       OUTPUT.x39 - column vector of length 12
%       OUTPUT.x40 - column vector of length 12
%
%   [OUTPUT, EXITFLAG] = FORCESNLPsolver(PARAMS) returns additionally
%   the integer EXITFLAG indicating the state of the solution with 
%       1 - OPTIMAL solution has been found (subject to desired accuracy)
%       0 - Timeout - maximum number of iterations reached
%      -6 - NaN or INF occured during evaluation of functions and derivatives. Please check your initial guess.
%      -7 - Method could not progress. Problem may be infeasible. Run FORCESdiagnostics on your problem to check for most common errors in the formulation.
%     -98 - Thread error
%     -99 - Locking mechanism error
%    -100 - License error
%    -101 - Insufficient number of internal memory instances
%    -102 - Number of threads larger than specified
%
%   [OUTPUT, EXITFLAG, INFO] = FORCESNLPsolver(PARAMS) returns 
%   additional information about the last iterate:
%       INFO.it - scalar: iteration number
%       INFO.it2opt - scalar: number of iterations needed to optimality (branch-and-bound)
%       INFO.res_eq - scalar: inf-norm of equality constraint residuals
%       INFO.res_ineq - scalar: inf-norm of inequality constraint residuals
%       INFO.rsnorm - scalar: norm of stationarity condition
%       INFO.rcompnorm - scalar: max of all complementarity violations
%       INFO.pobj - scalar: primal objective
%       INFO.dobj - scalar: dual objective
%       INFO.dgap - scalar: duality gap := pobj - dobj
%       INFO.rdgap - scalar: relative duality gap := |dgap / pobj |
%       INFO.mu - scalar: duality measure
%       INFO.mu_aff - scalar: duality measure (after affine step)
%       INFO.sigma - scalar: centering parameter
%       INFO.lsit_aff - scalar: number of backtracking line search steps (affine direction)
%       INFO.lsit_cc - scalar: number of backtracking line search steps (combined direction)
%       INFO.step_aff - scalar: step size (affine direction)
%       INFO.step_cc - scalar: step size (combined direction)
%       INFO.solvetime - scalar: total solve time
%       INFO.fevalstime - scalar: time spent in function evaluations
%       INFO.solver_id - column vector of length 8: solver ID of FORCESPRO solver
%
% See also COPYING
