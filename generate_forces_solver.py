import utils_slack as utils
# import utils
import forcespro
import argparse
import os
import numpy as np
import rospkg
import yaml

import sys

# sys.path.insert(0, 'home/robin/Dev/Forcespro/forces_pro_client/')


def build_solver(N: int, Ts: float, cfg: dict, max_it_solver):
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
    npar = 26  # number of parameters per stage
    nstates = 9
    ninputs = 3
    nslack = 1
    nvar = nslack+ninputs+nstates
    car_dim = 0.00  # move to config?
    half_track_width = 0.46/2  # move to config?
    hu_car = (half_track_width-car_dim)**2
    r_antena = 0.8

    # dimensions
    model = forcespro.nlp.SymbolicModel(N)
    model.N = N        # set horizon length
    model.nvar = nvar  # number of variables
    model.npar = npar  # set number of parameters per stage for solver
    model.neq = nstates      # number of equality constraints

    model.objective = lambda z, p: utils.stage_cost(z, p)
    model.continuous_dynamics = utils.continuous_dynamics

    model.E = np.concatenate(
        [np.zeros((nstates, nslack+ninputs)), np.eye(nstates)], axis=1)

    # # inequalities
    # for i in range(0, model.N):
    #     if i == 0:  # Initial constraints, inputs must be the same for safe and fast, inside track
    #         model.nh[i] = 4       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_sameInput(z, p)
    #         # without slack: set first to 0
    #         model.hu[i] = [100, 0.001, 0.001, 0.001]
    #         model.hl[i] = [-10, -0.001, -0.001, -0.001]
    #     elif i == model.N-1:  # Final constraints : final safe speed == 0, inside track
    #         model.nh[i] = 2       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_final(z, p)
    #         model.hu[i] = [100, 0.01]  # without slack: set first to 0
    #         model.hl[i] = [-10, -0.01]
    #     else:  # usual constraints : contained inside track
    #         model.nh[i] = 1       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_standard(z, p)
    #         model.hu[i] = [100]  # without slack: set first to 0
    #         model.hl[i] = [-10]

    # inequalities
    # for i in range(0, model.N):
    #     if i == 0:  # Initial constraints, inputs must be the same for safe and fast, inside track
    #         model.nh[i] = 5       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_sameInput_v2(
    #             z, p)
    #         model.hu[i] = [0, 0.001, 0.001, 0.001, r_antena**2]
    #         model.hl[i] = [-100, -0.001, -0.001, -0.001, 0]
    #     elif i == model.N-1:  # Final constraints : final safe speed == 0, inside track
    #         model.nh[i] = 3       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_final_v2(z, p)
    #         model.hu[i] = [0, 0.01, r_antena**2]
    #         model.hl[i] = [-100, -0.01, 0]
    #     else:  # usual constraints : contained inside track
    #         model.nh[i] = 2       # number of nonlinear inequality constraints
    #         model.ineq[i] = lambda z, p: utils.nonlinear_ineq_standard_v2(z, p)
    #         model.hu[i] = [0, r_antena**2]
    #         model.hl[i] = [-100, 0]

    # inequalities
    car_dim = 0.00  # move to config?
    half_track_width = 0.46/2  # move to config?
    hu_car = (half_track_width-car_dim)**2
    model.nh = 1
    model.ineq = lambda z, p: utils.nonlinear_ineq_standard_v2(z, p)
    model.hu = [hu_car]
    model.hl = [0]

    # initial state indeces
    model.xinitidx = np.arange(nslack+ninputs, nvar)

    # inequalities lower and upper bounds for state vector defined at head of
    # this subscript
    constraints = cfg["model_bounds"]

    model.lb = np.array([
        0,  # slack_var TODO: move to config
        # constraints["dT_min"],
        # constraints["ddelta_min"],
        # constraints["dtheta_min"],

        constraints["dT_min"],
        constraints["ddelta_min"],
        constraints["dtheta_min"],

        # constraints["x_min"],
        # constraints["y_min"],
        # constraints["yaw_min"],
        # constraints["vx_min"],
        # constraints["vy_min"],
        # constraints["dyaw_min"],
        # constraints["T_min"],
        # constraints["delta_min"],
        # constraints["theta_min"],

        constraints["x_min"],
        constraints["y_min"],
        constraints["yaw_min"],
        constraints["vx_min"],
        constraints["vy_min"],
        constraints["dyaw_min"],
        constraints["T_min"],
        constraints["delta_min"],
        constraints["theta_min"]

    ])

    model.ub = np.array([
        1000,  # slack_var TODO: move to config
        # constraints["dT_max"],
        # constraints["ddelta_max"],
        # constraints["dtheta_max"],

        constraints["dT_max"],
        constraints["ddelta_max"],
        constraints["dtheta_max"],

        # constraints["x_max"],
        # constraints["y_max"],
        # constraints["yaw_max"],
        # constraints["vx_max"],
        # constraints["vy_max"],
        # constraints["dyaw_max"],
        # constraints["T_max"],
        # constraints["delta_max"],
        # constraints["theta_max"],

        constraints["x_max"],
        constraints["y_max"],
        constraints["yaw_max"],
        constraints["vx_max"],
        constraints["vy_max"],
        constraints["dyaw_max"],
        constraints["T_max"],
        constraints["delta_max"],
        constraints["theta_max"],


    ])

    # Define solver options.
    codeoptions = forcespro.CodeOptions('FORCESNLPsolver')

    codeoptions.maxit = max_it_solver    # Maximum number of iterations
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


if __name__ == "__main__":
    N = 20
    Tf = 1
    with open('solver.yaml') as stream:
        config = yaml.safe_load(stream)

    solver = build_solver(N=20, Ts=0.3333, cfg=config, max_it_solver=100)
