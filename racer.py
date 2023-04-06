import numpy as np
import forcespro.nlp
import yaml
import sys
import generate_forces_solver
import utils_slack as utils
import matplotlib.pyplot as plt
import pickle
import dynamics
from helperObj import helperObj


class racer():
    def __init__(self, generate_new_solver: bool, init_iter=80, modelparams="modelparams.yaml", solverparams="solverparams", max_it_solver=500) -> None:

        self.modelparams = 'model_params.yaml'
        self.init_iter = init_iter

        with open(self.modelparams) as stream:
            model_params = yaml.safe_load(stream)

        with open('solver.yaml') as stream:
            config = yaml.safe_load(stream)

        # Vehicle params
        self.lr = model_params['lr']
        self.lf = model_params['lf']
        self.m = model_params['m']
        self.I = model_params['I']

        # lateral force params
        self.Df = model_params['Df']
        self.Cf = model_params['Cf']
        self.Bf = model_params['Bf']
        self.Dr = model_params['Dr']
        self.Cr = model_params['Cr']
        self.Br = model_params['Br']

        # longitudinal force params
        self.Cm1 = model_params['Cm1']
        self.Cm2 = model_params['Cm2']
        self.Cd = model_params['Cd']
        self.Croll = model_params['Croll']

        # TODO set this into a config file
        self.Q1 = 15000
        self.Q2 = 1000
        self.R1 = 0.01
        self.R2 = 0.01
        self.R3 = 0.01
        self.q = 0.1
        self.half_track_width = 0.46/2

        # Simulation params /!\ MUST BE THE SAME AS generate_forces_solver.py
        self.freq = model_params['freq']
        self.dt = 1/self.freq

        # Load track
        with open('DEMO_TRACK_REVERSE.yaml') as stream:
            data = yaml.safe_load(stream)

        self.c1_track = data['track']
        self.c1_xtrack = self.c1_track['xCoords']
        self.c1_xrate = self.c1_track['xRate']
        self.c1_ytrack = self.c1_track['yCoords']
        self.c1_yrate = self.c1_track['yRate']
        self.c1_arcLength = self.c1_track['arcLength']
        self.c1_tangentAngle = self.c1_track['tangentAngle']
        self.c1_theta_max = max(self.c1_arcLength)
        self.N = 40

        if generate_new_solver:
            self.model, self.solver = generate_forces_solver.build_solver(
                N=self.N, Ts=self.dt, cfg=config, max_it_solver=max_it_solver)
        else:
            self.solver = forcespro.nlp.Solver.from_directory(
                "/home/robin/Dev/mpcc_python/FORCESNLPsolver")
            self.solver.help

        # phi = yaw
        # d = Thrust
        # delta = steering angle
        # theta = advancement on track

        helper = helperObj()

        self.pvars = helper.pvars
        self.uvars = helper.uvars
        self.xvars = helper.xvars
        self.zvars = helper.zvars

        self.z_current = np.zeros((self.N, len(self.zvars)))
        self.c1_f_theta_current = np.zeros((self.N,))

        # sim step tracking
        self.simidx = 0
        self.c1_laps = 0

    def initialize_trajectory(self, xinit):

        # initialization for theta values
        iter = self.init_iter

        # initialize dyamics simulation
        self.dynamics = dynamics.dynamics_simulator(self.modelparams, xinit)

        # retain init position for antena constraint
        self.c1_s0_x = xinit[self.xvars.index('c1_f_posx')]
        self.c1_s0_y = xinit[self.xvars.index('c1_f_posy')]

        # warmstart init
        self.zinit = np.concatenate([[1], np.zeros(len(self.uvars)-1), xinit])
        # will be reshaped after
        self.z_current = np.tile(self.zinit, (self.N, 1))

        # arbitrarily set theta values and assign them to z_current
        c1_f_theta_old = self.zinit[self.zvars.index(
            'c1_f_theta')]*np.ones((self.N,)) + 0.1*np.arange(self.N)
        self.z_current[:, self.zvars.index('c1_f_theta')] = c1_f_theta_old

        c1_s_theta_old = self.zinit[self.zvars.index(
            'c1_s_theta')]*np.ones((self.N,)) + 0.1*np.arange(self.N)
        self.z_current[:, self.zvars.index('c1_s_theta')] = c1_s_theta_old

        # TODO initialize values on track (x,y,phi=yaw) for first iteration
        # for theta in theta_old:
        # idx = utils.get_trackDataIdx_from_theta(theta, self.arcLength)
        for stageidx in range(self.N):
            # get index on track linearization relative to theta
            c1_f_track_idx = utils.get_trackDataIdx_from_theta(
                c1_f_theta_old[stageidx], self.c1_arcLength)
            c1_s_track_idx = utils.get_trackDataIdx_from_theta(
                c1_s_theta_old[stageidx], self.c1_arcLength)

            self.z_current[stageidx, self.zvars.index(
                'c1_f_posx')] = self.c1_xtrack[c1_f_track_idx]
            self.z_current[stageidx, self.zvars.index(
                'c1_f_posy')] = self.c1_ytrack[c1_f_track_idx]
            self.z_current[stageidx, self.zvars.index(
                'c1_f_phi')] = self.c1_tangentAngle[c1_f_track_idx]

            self.z_current[stageidx, self.zvars.index(
                'c1_s_posx')] = self.c1_xtrack[c1_s_track_idx]
            self.z_current[stageidx, self.zvars.index(
                'c1_s_posy')] = self.c1_ytrack[c1_s_track_idx]
            self.z_current[stageidx, self.zvars.index(
                'c1_s_phi')] = self.c1_tangentAngle[c1_s_track_idx]
        # get a convergent Theta
        for index in range(iter):
            # init parameters for each stage of the horizon
            all_parameters = []
            if index % 20 == 0:
                print(f'initialisation : {index}')

            for stageidx in range(self.N):
                # get index on track linearization relative to theta
                c1_f_track_idx = utils.get_trackDataIdx_from_theta(
                    c1_f_theta_old[stageidx], self.c1_arcLength)
                c1_s_track_idx = utils.get_trackDataIdx_from_theta(
                    c1_s_theta_old[stageidx], self.c1_arcLength)

                # store the according parameters
                p_val = np.array([  # fast
                                 self.c1_xtrack[c1_f_track_idx],
                                 self.c1_ytrack[c1_f_track_idx],
                                 self.c1_xrate[c1_f_track_idx],
                                 self.c1_yrate[c1_f_track_idx],
                                 self.c1_arcLength[c1_f_track_idx],
                                 self.c1_tangentAngle[c1_f_track_idx],
                                 # safe
                                 self.c1_xtrack[c1_s_track_idx],
                                 self.c1_ytrack[c1_s_track_idx],
                                 self.c1_xrate[c1_s_track_idx],
                                 self.c1_yrate[c1_s_track_idx],
                                 self.c1_arcLength[c1_s_track_idx],
                                 self.c1_tangentAngle[c1_s_track_idx],
                                 # other params
                                 self.Q1,
                                 self.Q2,
                                 self.R1,
                                 self.R2,
                                 self.R3,
                                 self.q,
                                 self.lr,
                                 self.lf,
                                 self.m,
                                 self.I,
                                 self.Df,
                                 self.Cf,
                                 self.Bf,
                                 self.Dr,
                                 self.Cr,
                                 self.Br,
                                 self.Cm1,
                                 self.Cm2,
                                 self.Cd,
                                 self.Croll,
                                 self.c1_s0_x,
                                 self.c1_s0_y])

                all_parameters.append(p_val)

            all_parameters = np.array(all_parameters)

            # reshape data for the solver
            problem = {"x0": self.z_current.reshape(-1,),
                       "xinit": xinit,
                       "all_parameters": all_parameters.reshape(-1,)}

            # check z0_size, should be (1,12) #TODO remove #STOPPPPPPPPEEEED HEEEEEERE
            z0_old = self.z_current[0, :]

            output, exitflag, info = self.solver.solve(problem)

            # extract theta values
            idx_sol = 0
            for key in output:
                # print(key)
                # if key == 'x0':
                #     pass
                zsol = output[key]
                self.z_current[idx_sol, :] = zsol
                idx_sol = idx_sol+1

            self.c1_f_theta_current = self.z_current[:, self.zvars.index(
                'c1_f_theta')]
            self.c1_s_theta_current = self.z_current[:, self.zvars.index(
                'c1_s_theta')]

            # # compute difference
            # theta_diff = np.sum(np.abs(self.theta_current-theta_old))
            # print(f": theta init difference: {theta_diff}")
            # print("theta values", self.theta_current)
            c1_f_theta_old = self.c1_f_theta_current
            c1_s_theta_old = self.c1_s_theta_current

            self.xinit = self.z_current[0,
                                        self.uvars.index('c1_s_thetadot')+1:]

        return self.z_current

    def update(self):
        # set all slack variables to 0
        self.z_current[:, self.zvars.index('c1_s_slack'):self.zvars.index(
            'c1_f_slack_thetadot')+1] = np.zeros((self.N, 4))

        all_parameters = []

        c1_f_theta_old = self.c1_f_theta_current
        c1_s_theta_old = self.c1_s_theta_current

        self.c1_s0_x = self.xinit[self.xvars.index('c1_f_posx')]
        self.c1_s0_y = self.xinit[self.xvars.index('c1_f_posy')]

        for stageidx in range(self.N):
            # get index on track linearization relative to theta
            c1_f_track_idx = utils.get_trackDataIdx_from_theta(
                c1_f_theta_old[stageidx], self.c1_arcLength)
            c1_s_track_idx = utils.get_trackDataIdx_from_theta(
                c1_s_theta_old[stageidx], self.c1_arcLength)

            # store the according parameters
            p_val = np.array([  # fast
                self.c1_xtrack[c1_f_track_idx],
                self.c1_ytrack[c1_f_track_idx],
                self.c1_xrate[c1_f_track_idx],
                self.c1_yrate[c1_f_track_idx],
                self.c1_arcLength[c1_f_track_idx],
                self.c1_tangentAngle[c1_f_track_idx],
                # safe
                self.c1_xtrack[c1_s_track_idx],
                self.c1_ytrack[c1_s_track_idx],
                self.c1_xrate[c1_s_track_idx],
                self.c1_yrate[c1_s_track_idx],
                self.c1_arcLength[c1_s_track_idx],
                self.c1_tangentAngle[c1_s_track_idx],
                # other params
                self.Q1,
                self.Q2,
                self.R1,
                self.R2,
                self.R3,
                self.q,
                self.lr,
                self.lf,
                self.m,
                self.I,
                self.Df,
                self.Cf,
                self.Bf,
                self.Dr,
                self.Cr,
                self.Br,
                self.Cm1,
                self.Cm2,
                self.Cd,
                self.Croll,
                self.c1_s0_x,
                self.c1_s0_y])

            all_parameters.append(p_val)

        all_parameters = np.array(all_parameters)

        # problem dictionary, arrays have to be flattened
        problem = {"x0": self.z_current.reshape(-1,),
                   "xinit": self.xinit,
                   "all_parameters": all_parameters.reshape(-1,)}
        # solve problem
        output, exitflag, info = self.solver.solve(problem)

        # extract solution
        idx_sol = 0
        for key in output:
            # print(key)
            zsol = output[key]
            self.z_current[idx_sol, :] = zsol
            idx_sol = idx_sol+1

        # #simulate dynamics
        u = self.z_current[0, self.uvars.index(
            'c1_s_slack'):self.uvars.index('c1_s_thetadot')+1]
        xtrue = self.dynamics.tick(u, all_parameters[0, :], self.freq)

        # #shift horizon for next warmstart and insert the new "measured position"
        self.z_current[1, self.uvars.index('c1_s_thetadot')+1:] = xtrue
        # Shift all stages
        self.z_current = np.roll(self.z_current, -1, axis=0)
        # copy last state to be the same as antestage
        self.z_current[-1, :] = self.z_current[-2, :]
        # advance the last prediction for theta
        self.z_current[-1, self.zvars.index('c1_f_theta')] += 0.1
        self.z_current[-1, self.zvars.index('c1_s_theta')] += 0.1

        # log solution
        # self.z_data[self.simidx, :, :] = self.z_current
        self.zinit = self.z_current[0, :]
        self.xinit = self.zinit[self.uvars.index('c1_s_thetadot')+1:]

        # self.zinit_vals[self.simidx, :] = self.zinit

        # update theta
        self.c1_f_theta_current = self.z_current[:, self.zvars.index(
            'c1_f_theta')]
        self.c1_s_theta_current = self.z_current[:, self.zvars.index(
            'c1_s_theta')]

        if self.c1_f_theta_current[0] > self.c1_theta_max/2:
            print("#################################LAP###############################")
            # update laps
            self.c1_laps = self.c1_laps + 1
            print("c1 lap:", self.c1_laps)
            # reset theta
            self.c1_f_theta_current = self.c1_f_theta_current - self.c1_theta_max/2
            self.c1_s_theta_current = self.c1_s_theta_current - self.c1_theta_max/2
            # set theta to z_current for correspondance
            self.z_current[:, self.zvars.index(
                'c1_f_theta')] = self.c1_f_theta_current
            wrapdir = self.dynamics.wrap_phi_c1(self.z_current)
            # reset phi to origininal
            self.z_current[:, self.zvars.index(
                'c1_f_phi')] = self.z_current[:, self.zvars.index('c1_f_phi')] - (wrapdir)*2*3.14159
            self.z_current[:, self.zvars.index(
                'c1_s_phi')] = self.z_current[:, self.zvars.index('c1_f_phi')] - (wrapdir)*2*3.14159
            # reset theta to dynamics object for correspondance
            self.dynamics.set_theta(
                self.c1_f_theta_current[0])
            # # reset safe traj to have the same state as fast traj
            # self.z_current[:, self.zvars.index('s_posx'):self.zvars.index(
            #     's_theta')] = self.z_current[:, self.zvars.index('f_posx'):self.zvars.index('f_theta')]
            print(f'zcurrent = {self.z_current[2,:]}')

        if exitflag == -7:
            print("#################################################reinitialize#######################################################")
            info_dic = [info.solvetime, info.res_ineq,
                        info.it, exitflag, info.pobj]
            z_current_temp = self.z_current
            all_parameters_temp = all_parameters
            self.initialize_trajectory(self.xinit)
            self.simidx = self.simidx + 1

            return z_current_temp, info_dic, all_parameters_temp

        # copy safe traj to fast traj for recursive feasibility

        self.z_current[:, self.zvars.index('c1_f_posx'):self.zvars.index(
            'c1_f_theta')+1] = self.z_current[:, self.zvars.index('c1_s_posx'):self.zvars.index('c1_s_theta')+1]

        # Increment simidx and return log data

        self.simidx = self.simidx + 1
        info_dic = [info.solvetime, info.res_ineq,
                    info.it, exitflag, info.pobj]

        return self.z_current, info_dic, all_parameters
