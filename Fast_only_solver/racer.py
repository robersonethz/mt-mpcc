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

        self.xvars = ['posx', 'posy', 'phi', 'vx',
                      'vy', 'omega', 'd', 'delta', 'theta']
        self.uvars = ['ddot', 'deltadot', 'thetadot']
        self.pvars = ['xd', 'yd', 'grad_xd', 'grad_yd', 'theta_hat', 'phi_d', 'Q1', 'Q2', 'R1', 'R2',
                      'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll']

        self.zvars = ['posx', 'posy', 'phi', 'vx', 'vy', 'omega',
                      'd', 'delta', 'theta', 'ddot', 'deltadot', 'thetadot']

        self.z_current = np.zeros((self.N, len(self.zvars)))
        self.theta_current = np.zeros((self.N,))

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
        self.zinit = np.concatenate([xinit, np.array([0, 0, 0])])
        # will be reshaped after
        self.z_current = np.tile(self.zinit, (self.N, 1))

        # arbitrarily set theta values and assign them to z_current
        theta_old = self.zinit[self.zvars.index(
            'theta')]*np.ones((self.N,)) + 0.1*np.arange(self.N)
        self.z_current[:, self.zvars.index('theta')] = theta_old

        # TODO initialize values on track (x,y,phi=yaw) for first iteration
        # for theta in theta_old:
        #     idx = utils.get_trackDataIdx_from_theta(theta, self.arcLength)

        # get a convergent Theta
        for index in range(iter):
            all_parameters = []
            for stageidx in range(self.N):
                track_idx = utils.get_trackDataIdx_from_theta(
                    theta_old[stageidx], self.arcLength)

                p_val = np.array([self.xtrack[track_idx],
                                 self.ytrack[track_idx],
                                 self.xrate[track_idx],
                                 self.yrate[track_idx],
                                 self.arcLength[track_idx],
                                 self.tangentAngle[track_idx],
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

            problem = {"x0": self.z_current.reshape(-1,),
                       "xinit": xinit,
                       "all_parameters": all_parameters.reshape(-1,)}

            z0_old = self.z_current[0, :]  # check z0_size, should be (1,12)

            output, exitflag, info = self.solver.solve(problem)

            # extract theta values
            idx_sol = 0
            for key in output:
                # print(key)
                # if key == 'x0':
                #     pass
                zsol = output[key]  # TODO verify: each key is a stage
                usol = zsol[9:12]
                self.z_current[idx_sol, :] = zsol
                idx_sol = idx_sol+1

            self.theta_current = self.z_current[:, self.zvars.index('theta')]

            # # compute difference
            # theta_diff = np.sum(np.abs(self.theta_current-theta_old))
            # print(f": theta init difference: {theta_diff}")
            # print("theta values", self.theta_current)
            theta_old = self.theta_current
            self.xinit = self.z_current[0, 0:9]
            # self.z_current[0, self.zvars.index('posx')] = xinit[0]

            # prepare for plotting
            np_xtrack = np.array(self.xtrack)
            np_xrate = np.array(self.xrate)
            np_ytrack = np.array(self.ytrack)
            np_yrate = np.array(self.yrate)

            list_log = {'z_current': self.z_current,
                        # 'info': info,
                        'np_xtrack': np_xtrack,
                        'np_xrate': np_xrate,
                        'np_ytrack': np_ytrack,
                        'np_yrate': np_yrate}

            with open('log_data.pickle', 'wb') as f:
                pickle.dump(list_log, f)

        return self.z_current

    def update(self):
        all_parameters = []

        theta_old = self.theta_current

        for stageidx in range(self.N):
            track_idx = utils.get_trackDataIdx_from_theta(
                theta_old[stageidx], self.arcLength)

            p_val = np.array([self.xtrack[track_idx],
                              self.ytrack[track_idx],
                              self.xrate[track_idx],
                              self.yrate[track_idx],
                              self.arcLength[track_idx],
                              self.tangentAngle[track_idx],
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
        u = self.z_current[0, 9:]
        xtrue = self.dynamics.tick(u, all_parameters[0, :], self.freq)

        # #shift horizon for next warmstart and insert the new "measured position"
        self.z_current[1, 0:9] = xtrue
        # TODO check what is doing
        self.z_current = np.roll(self.z_current, -1, axis=0)
        # copy last state to be the same as antestage
        self.z_current[-1, :] = self.z_current[-2, :]
        # advance the last prediction for theta
        self.z_current[-1, self.zvars.index('theta')] += 0.1

        # log solution
        # self.z_data[self.simidx, :, :] = self.z_current
        self.zinit = self.z_current[0, :]
        self.xinit = self.zinit[:9]

        # self.zinit_vals[self.simidx, :] = self.zinit
        #

        # update theta
        self.theta_current = self.z_current[:, self.zvars.index('theta')]

        if self.theta_current[0] > self.theta_max/2:
            print("#################################RESET###############################")
            self.laps = self.laps + 1
            print("lap:", self.laps)
            self.theta_current = self.theta_current - self.theta_max/2
            self.z_current[:, self.zvars.index('theta')] = self.theta_current
            wrapdir = self.dynamics.wrap_phi()
            self.z_current[:, self.zvars.index(
                'phi')] = self.z_current[:, self.zvars.index('phi')] - (wrapdir)*2*3.14159
            self.dynamics.set_theta(self.theta_current[0])

        if exitflag == -7:
            print("#################################################reinitialize#######################################################")
            self.reinitialize()

        self.simidx = self.simidx + 1
        time = info.solvetime
        type_time = type(time)
        return self.z_current, time

    def return_sim_data(self):
        return self.zinit_vals, self.z_data
