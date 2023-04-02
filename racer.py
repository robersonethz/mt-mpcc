import numpy as np
import forcespro.nlp
import yaml
import sys
import generate_forces_solver
import utils
import matplotlib.pyplot as plt
import pickle
import dynamics


class racer():
    def __init__(self, modelparams="modelparams.yaml", solverparams="solverparams") -> None:

        self.modelparams = '/home/robin/Dev/mpcc_python/model_params.yaml'

        with open('/home/robin/Dev/mpcc_python/model_params.yaml') as stream:
            model_params = yaml.safe_load(stream)

        with open('/home/robin/Dev/mpcc_python/solver.yaml') as stream:
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
        self.q = 10
        self.half_track_width = 0.46/2

        # Simulation params /!\ MUST BE THE SAME AS generate_forces_solver.py
        self.freq = model_params['freq']
        self.dt = 1/self.freq

        # Load track
        with open('/home/robin/Dev/mpcc_python/DEMO_TRACK.yaml') as stream:
            data = yaml.safe_load(stream)

        self.track = data['track']
        self.xtrack = self.track['xCoords']
        self.xrate = self.track['xRate']
        self.ytrack = self.track['yCoords']
        self.yrate = self.track['yRate']
        self.arcLength = self.track['arcLength']
        self.tangentAngle = self.track['tangentAngle']
        self.theta_max = max(self.arcLength)

        self.model, self.solver = generate_forces_solver.build_solver(
            N=20, Ts=self.dt, cfg=config)

        self.N = self.model.N
        self.Nsim = 30  # number of points to simulate, simulation length

        # phi = yaw
        # d = Thrust
        # delta = steering angle
        # theta = advancement on track

        self.xvars = ['f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
                      's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta']

        self.uvars = ['f_ddot', 'f_deltadot', 'f_thetadot',
                      's_ddot', 's_deltadot', 's_thetadot']

        self.pvars = ['f_xd', 'f_yd', 'f_grad_xd', 'f_grad_yd', 'f_theta_hat', 'f_phi_d',
                      's_xd', 's_yd', 's_grad_xd', 's_grad_yd', 's_theta_hat', 's_phi_d',
                      'Q1', 'Q2', 'R1', 'R2', 'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll']

        self.zvars = ['f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
                      's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta',
                      'f_ddot', 'f_deltadot', 'f_thetadot',
                      's_ddot', 's_deltadot', 's_thetadot']

        self.z_current = np.zeros((self.N, len(self.zvars)))
        self.f_theta_current = np.zeros((self.N,))

        # list to store all visited states
        self.zinit_vals = np.zeros((self.Nsim, len(self.zvars)))
        # list containing also the prediction horizons
        self.z_data = np.zeros((self.Nsim, self.N, len(self.zvars)))

        # sim step tracking
        self.simidx = 0
        self.laps = 0

    def initialize_trajectory(self, xinit):

        # initialization for theta values
        iter = 30

        # initialize dyamics simulation
        self.dynamics = dynamics.dynamics_simulator(self.modelparams, xinit)

        # warmstart init
        self.zinit = np.concatenate([xinit, np.zeros(len(self.uvars))])
        # will be reshaped after
        self.z_current = np.tile(self.zinit, (self.N, 1))

        # arbitrarily set theta values and assign them to z_current
        f_theta_old = self.zinit[self.zvars.index(
            'f_theta')]*np.ones((self.N,)) + 0.1*np.arange(self.N)
        self.z_current[:, self.zvars.index('f_theta')] = f_theta_old

        s_theta_old = self.zinit[self.zvars.index(
            's_theta')]*np.ones((self.N,)) + 0.1*np.arange(self.N)
        self.z_current[:, self.zvars.index('s_theta')] = s_theta_old

        # TODO initialize values on track (x,y,phi=yaw) for first iteration
        # for theta in theta_old:
        #     idx = utils.get_trackDataIdx_from_theta(theta, self.arcLength)

        # get a convergent Theta
        for index in range(iter):
            # init parameters for each stage of the horizon
            all_parameters = []

            for stageidx in range(self.N):
                # get index on track linearization relative to theta
                f_track_idx = utils.get_trackDataIdx_from_theta(
                    f_theta_old[stageidx], self.arcLength)
                s_track_idx = utils.get_trackDataIdx_from_theta(
                    s_theta_old[stageidx], self.arcLength)

                # store the according parameters
                p_val = np.array([  # fast
                                 self.xtrack[f_track_idx],
                                 self.ytrack[f_track_idx],
                                 self.xrate[f_track_idx],
                                 self.yrate[f_track_idx],
                                 self.arcLength[f_track_idx],
                                 self.tangentAngle[f_track_idx],
                                 # safe
                                 self.xtrack[s_track_idx],
                                 self.ytrack[s_track_idx],
                                 self.xrate[s_track_idx],
                                 self.yrate[s_track_idx],
                                 self.arcLength[s_track_idx],
                                 self.tangentAngle[s_track_idx],
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
                                 self.Croll])

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

            self.f_theta_current = self.z_current[:, self.zvars.index(
                'f_theta')]
            self.s_theta_current = self.z_current[:, self.zvars.index(
                's_theta')]

            # # compute difference
            # theta_diff = np.sum(np.abs(self.theta_current-theta_old))
            # print(f": theta init difference: {theta_diff}")
            # print("theta values", self.theta_current)
            f_theta_old = self.f_theta_current
            s_theta_old = self.s_theta_current

            self.xinit = self.z_current[0, 0:len(self.xvars)]

        return self.z_current

    def update(self):
        all_parameters = []

        f_theta_old = self.f_theta_current
        s_theta_old = self.s_theta_current

        for stageidx in range(self.N):
            # get index on track linearization relative to theta
            f_track_idx = utils.get_trackDataIdx_from_theta(
                f_theta_old[stageidx], self.arcLength)
            s_track_idx = utils.get_trackDataIdx_from_theta(
                s_theta_old[stageidx], self.arcLength)

            # store the according parameters
            p_val = np.array([  # fast
                self.xtrack[f_track_idx],
                self.ytrack[f_track_idx],
                self.xrate[f_track_idx],
                self.yrate[f_track_idx],
                self.arcLength[f_track_idx],
                self.tangentAngle[f_track_idx],
                # safe
                self.xtrack[s_track_idx],
                self.ytrack[s_track_idx],
                self.xrate[s_track_idx],
                self.yrate[s_track_idx],
                self.arcLength[s_track_idx],
                self.tangentAngle[s_track_idx],
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
                self.Croll])

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
        u = self.z_current[0, len(self.xvars):]
        xtrue = self.dynamics.tick(u, all_parameters[0, :], self.freq)

        # #shift horizon for next warmstart and insert the new "measured position"
        self.z_current[1, :len(self.xvars)] = xtrue
        # TODO check what is doing
        self.z_current = np.roll(self.z_current, -1, axis=0)
        # copy last state to be the same as antestage
        self.z_current[-1, :] = self.z_current[-2, :]
        # advance the last prediction for theta
        self.z_current[-1, self.zvars.index('f_theta')] += 0.1
        self.z_current[-1, self.zvars.index('s_theta')] += 0.1

        # log solution
        # self.z_data[self.simidx, :, :] = self.z_current
        self.zinit = self.z_current[0, :]
        self.xinit = self.zinit[:len(self.xvars)]

        # self.zinit_vals[self.simidx, :] = self.zinit
        #

        # update theta
        self.f_theta_current = self.z_current[:, self.zvars.index('f_theta')]
        self.s_theta_current = self.z_current[:, self.zvars.index('s_theta')]

        if self.f_theta_current[0] > self.theta_max/2:
            print("#################################RESET###############################")
            # update laps
            self.laps = self.laps + 1
            print("lap:", self.laps)
            # reset theta
            self.f_theta_current = self.f_theta_current - self.theta_max/2
            self.s_theta_current = self.s_theta_current - self.theta_max/2
            # set theta to z_current for correspondance
            self.z_current[:, self.zvars.index(
                'f_theta')] = self.f_theta_current
            wrapdir = self.dynamics.wrap_phi()
            # reset phi to origininal
            self.z_current[:, self.zvars.index(
                'f_phi')] = self.z_current[:, self.zvars.index('f_phi')] - (wrapdir)*2*3.14159
            self.z_current[:, self.zvars.index(
                's_phi')] = self.z_current[:, self.zvars.index('s_phi')] - (wrapdir)*2*3.14159
            # reset theta to dynamics object for correspondance
            self.dynamics.set_theta(
                self.f_theta_current[0], self.s_theta_current[0])

        if exitflag == -7:
            print("#################################################reinitialize#######################################################")
            self.reinitialize()  # TODO still to implement

        self.simidx = self.simidx + 1
        time = info.solvetime
        # type_time = type(time)
        return self.z_current, time

    def return_sim_data(self):
        return self.zinit_vals, self.z_data
