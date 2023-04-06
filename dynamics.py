import casadi
import numpy as np
import yaml
import utils_slack as utils


class dynamics_simulator():
    def __init__(self, modelparams, x0):

        with open(modelparams) as file:
            params = yaml.load(file, Loader=yaml.FullLoader)

        self.xvars = ['c1_f_posx', 'c1_f_posy', 'c1_f_phi', 'c1_f_vx', 'c1_f_vy', 'c1_f_omega', 'c1_f_d', 'c1_f_delta', 'c1_f_theta',
                      # 'c1_s_posx', 'c1_s_posy', 'c1_s_phi', 'c1_s_vx', 'c1_s_vy', 'c1_s_omega', 'c1_s_d', 'c1_s_delta', 'c1_s_theta'
                      ]

        self.uvars = ['c1_s_slack',
                      'c1_f_ddot', 'c1_f_deltadot', 'c1_f_thetadot',
                      # 'c1_s_ddot', 'c1_s_deltadot', 'c1_s_thetadot'
                      ]

        # state of system
        self.x = x0

    def tick(self, u, all_parameters, freq):
        slack = u[self.uvars.index('c1_s_slack')]
        c1_f_u = u[self.uvars.index(
            'c1_f_ddot'):self.uvars.index('c1_f_thetadot')+1]

        z = np.hstack((np.array([slack]),
                       c1_f_u,
                       # c1_f_u,
                       self.x))

        self.x = utils.dynamics_RK4(
            z, all_parameters, freq).full().transpose().reshape(-1)
        # make sure xtrue is the same for safe and fast traj
        # self.x[self.xvars.index(
        #     'c1_s_posx'):] = self.x[:self.xvars.index('c1_s_posx')]
        # print(f'x fast: {self.x[0:2]}')
        # print(f'x safe: {self.x[9:11]}')
        # print('')
        return self.x

    def set_theta(self, c1_f_theta):
        self.x[self.xvars.index('c1_f_theta')] = c1_f_theta
        # self.x[self.xvars.index('c1_s_theta')] = c1_f_theta

    def wrap_phi(self):
        if self.x[self.xvars.index('c1_f_phi')] > 2 * 3.14159:
            self.x[self.xvars.index('c1_f_phi')] -= 2 * 3.14159
            wrapdir = 1
        elif self.x[self.xvars.index('c1_f_phi')] < -2 * 3.14159:
            self.x[self.xvars.index('c1_f_phi')] += 2 * 3.14159
            wrapdir = -1
        else:
            wrapdir = 0
        return wrapdir
