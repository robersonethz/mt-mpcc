import utils
import forcespro
import argparse
import os
import numpy as np
import rospkg
import yaml

import sys

# sys.path.insert(0, 'home/robin/Dev/Forcespro/forces_pro_client/')


def build_solver(N: int, Ts: float, cfg: dict):
    """
    Creates the required C-Code for the acados solver

    Parameters
    ----------
    N : int
        Time Horizon
    Ts : float
        Sampling Time
    acados_source_path : str
        Path to acados source location
    model: Callable
        Model function e.g. pacejka_model

    Returns
    -------
    None
    """
    npar = (6*2)+20  # number of parameters per stage
    nstates = 9*2
    ninputs = 3*2
    nvar = nstates+ninputs
    car_dim = 0.07  # move to config?
    half_track_width = 0.46/2 - 0.1  # move to config?
    hu_car = (half_track_width-car_dim)*(half_track_width-car_dim)

    # dimensions
    model = forcespro.nlp.SymbolicModel(N)
    model.N = N        # set horizon length
    model.nvar = nvar  # number of variables
    model.npar = npar  # set number of parameters per stage for solver
    model.neq = nstates      # number of equality constraints

    model.objective = lambda z, p: utils.stage_cost(z, p)
    model.continuous_dynamics = utils.continuous_dynamics

    model.E = np.concatenate(
        [np.eye(nstates), np.zeros((nstates, ninputs))], axis=1)

    # inequalities
    for i in range(0, model.N):
        if i == 0:  # Initial constraints, inputs must be the same for safe and fast, inside track
            model.nh[i] = 5       # number of nonlinear inequality constraints
            model.ineq[i] = lambda z, p: utils.nonlinear_ineq_sameInput(z, p)
            model.hu[i] = [0, 0, 0.001, 0.001, 0.001]
            model.hl[i] = [-10, -10, -0.001, -0.001, -0.001]
        # elif i == model.N-1:  # Final constraints : final safe speed == 0, inside track
        #     model.nh[i] = 3       # number of nonlinear inequality constraints
        #     model.ineq[i] = lambda z, p: utils.nonlinear_ineq_final(z, p)
        #     model.hu[i] = [0, 0, 0.01]
        #     model.hl[i] = [-10, -10, -0.01]
        else:  # usual constraints : contained inside track
            model.nh[i] = 2       # number of nonlinear inequality constraints
            model.ineq[i] = lambda z, p: utils.nonlinear_ineq_standard(z, p)
            model.hu[i] = [0, 0]
            model.hl[i] = [-10, -10]

    # inequalities
    # for i in range(0, model.N):
    #     if i == 0:  # Initial constraints, inputs must be the same for safe and fast, inside track
    #         model.nh[i] = 5       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_sameInput_v2(
    #             z, p)
    #         model.hu[i] = [hu_car, hu_car, 0.001, 0.001, 0.001]
    #         model.hl[i] = [0, 0, -0.001, -0.001, -0.001]
    #     # elif i == model.N-1:  # Final constraints : final safe speed == 0, inside track
    #     #     model.nh[i] = 3       # number of nonlinear inequality constraints
    #     #     model.ineq[i] = lambda z, p: utils.nonlinear_ineq_final(z, p)
    #     #     model.hu[i] = [0, 0, 0.01]
    #     #     model.hl[i] = [-10, -10, -0.01]
    #     else:  # usual constraints : contained inside track
    #         model.nh[i] = 2       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_standard_v2(z, p)
    #         model.hu[i] = [hu_car, hu_car]
    #         model.hl[i] = [0, 0]

    # initial state indeces
    model.xinitidx = range(0, nstates)

    # inequalities lower and upper bounds for state vector defined at head of
    # this subscript
    constraints = cfg["model_bounds"]

    model.lb = np.array([
        constraints["x_min"],
        constraints["y_min"],
        constraints["yaw_min"],
        constraints["vx_min"],
        constraints["vy_min"],
        constraints["dyaw_min"],
        constraints["T_min"],
        constraints["delta_min"],
        constraints["theta_min"],

        constraints["x_min"],
        constraints["y_min"],
        constraints["yaw_min"],
        constraints["vx_min"],
        constraints["vy_min"],
        constraints["dyaw_min"],
        constraints["T_min"],
        constraints["delta_min"],
        constraints["theta_min"],

        constraints["dT_min"],
        constraints["ddelta_min"],
        constraints["dtheta_min"],

        constraints["dT_min"],
        constraints["ddelta_min"],
        constraints["dtheta_min"]
    ])

    model.ub = np.array([
        constraints["x_max"],
        constraints["y_max"],
        constraints["yaw_max"],
        constraints["vx_max"],
        constraints["vy_max"],
        constraints["dyaw_max"],
        constraints["T_max"],
        constraints["delta_max"],
        constraints["theta_max"],

        constraints["x_max"],
        constraints["y_max"],
        constraints["yaw_max"],
        constraints["vx_max"],
        constraints["vy_max"],
        constraints["dyaw_max"],
        constraints["T_max"],
        constraints["delta_max"],
        constraints["theta_max"],

        constraints["dT_max"],
        constraints["ddelta_max"],
        constraints["dtheta_max"],

        constraints["dT_max"],
        constraints["ddelta_max"],
        constraints["dtheta_max"]
    ])

    # Define solver options.
    codeoptions = forcespro.CodeOptions('FORCESNLPsolver')

    codeoptions.maxit = 20    # Maximum number of iterations
    # codeoptions.solver_timeout = 2 # timeout enabled
    # codeoptions.timeout_estimate_coeff = Ts / 2 # Set timeout to half the sampling time

    # Use printlevel = 2 to print progress (but not for timings)
    codeoptions.printlevel = 0
    # 0: no optimization, 1: optimize for size, 2: optimize for speed, 3: optimize for size & speed
    codeoptions.optlevel = 2
    codeoptions.nlp.linear_solver = 'symm_indefinite_fast'
    codeoptions.nlp.integrator.type = 'ERK4'
    codeoptions.nlp.integrator.Ts = Ts
    codeoptions.nlp.integrator.nodes = 2
    codeoptions.nlp.stack_parambounds = 2

    # codeoptions.nlp.checkFunctions = 0
    # codeoptions.noVariableElimination = 1
    codeoptions.overwrite = 1  # 1: overwrite existing solver
    codeoptions.cleanup = 0
    codeoptions.BuildSimulinkBlock = 0
    # codeoptions.nohash = 0
    codeoptions.parallel = 1
    codeoptions.sse = 1
    codeoptions.useFloatingLicense = 1

    solver = model.generate_solver(codeoptions)

    return [model, solver]

### OLD GENEREATION ###
# objective
    # model.objective = utils.cost_function_pacejka # option as in matlab
    # equalities
    # def rk4_with_freq(z, p):
    #     return utils.dynamics_RK4(z,p,freq=1 / Ts)

    # model.eq = rk4_with_freq

    # define outputs and generate solver
    # outputs = [
    #     ('s0', 0 , range(0, 12)), #state at 0
    #     ('theta', range(0, N), 8),
    #     ('dtheta', range(0, N), 11),
    #     ('x', range(0, N), 0),
    #     ('y', range(0, N), 1),

    #     ('horizon', range(0, N), range(0, 12))]
    # Generate c code
    # solver = model.generate_solver(codeoptions, outputs)


# if __name__ == "__main__":
#     parser = argparse.ArgumentParser(description='Create a new Forces MPCC solver for the pacejka model')
#     parser.add_argument('--config', type=str, help='Name of the configuration file', default="solver.yaml")
#     args = parser.parse_args()

#     rospack = rospkg.RosPack()
#     # commented out to be able to run it without ROS/Docker.
#     # TODO, change this back
#     # controller_path = rospack.get_path('forces_pacejka_mpcc_solver')
#     # os.chdir( controller_path + "/src" )

#     with open(f"../config/{args.config}") as f:
#         cfg = yaml.load(f, Loader=yaml.loader.SafeLoader)
#         build_solver(cfg["solver_creation"]["N"], cfg["solver_creation"]["Ts"], cfg)
if __name__ == "__main__":
    N = 20
    Tf = 1
    with open('/home/robin/Dev/mpcc_python/solver.yaml') as stream:
        config = yaml.safe_load(stream)

    solver = build_solver(N=20, Ts=0.3333, cfg=config)
