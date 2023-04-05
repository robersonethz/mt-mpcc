import casadi
import numpy as np
import yaml
import utils_slack as utils


class dynamics_simulator():
    def __init__(self, modelparams, x0):

        with open(modelparams) as file:
            params = yaml.load(file, Loader=yaml.FullLoader)

        self.xvars = ['f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
                      's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta']

        self.uvars = ['s_slack',
                      'f_ddot', 'f_deltadot', 'f_thetadot',
                      's_ddot', 's_deltadot', 's_thetadot']

        # state of system
        self.x = x0

    def tick(self, u, all_parameters, freq):
        slack = u[self.uvars.index('s_slack')]
        f_u = u[self.uvars.index('f_ddot'):self.uvars.index('f_thetadot')+1]
        z = np.hstack((np.array([slack]), f_u, f_u, self.x))
        self.x = utils.dynamics_RK4(
            z, all_parameters, freq).full().transpose().reshape(-1)
        # make sure xtrue is the same for safe and fast traj
        # self.x[self.xvars.index(
        #     's_posx'):] = self.x[:self.xvars.index('s_posx')]
        # print(f'x fast: {self.x[0:2]}')
        # print(f'x safe: {self.x[9:11]}')
        # print('')
        return self.x

    def set_theta(self, f_theta):
        self.x[self.xvars.index('f_theta')] = f_theta
        self.x[self.xvars.index('s_theta')] = f_theta

    def wrap_phi(self):
        if self.x[self.xvars.index('f_phi')] > 2 * 3.14159:
            self.x[self.xvars.index('f_phi')] -= 2 * 3.14159
            wrapdir = 1
        elif self.x[self.xvars.index('f_phi')] < -2 * 3.14159:
            self.x[self.xvars.index('f_phi')] += 2 * 3.14159
            wrapdir = -1
        else:
            wrapdir = 0
        return wrapdir
