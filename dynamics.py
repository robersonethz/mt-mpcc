import casadi
import numpy as np
import yaml
import utils_slack as utils
from helperObj import helperObj


class dynamics_simulator():
    def __init__(self, modelparams, x0):

        with open(modelparams) as file:
            params = yaml.load(file, Loader=yaml.FullLoader)

        helper = helperObj()

        self.pvars = helper.pvars
        self.uvars = helper.uvars
        self.xvars = helper.xvars
        self.zvars = helper.zvars

        # state of system
        self.x = x0

    def tick(self, u, all_parameters, freq):
        # helper to construct the correct z vector:
        slacks = u[self.uvars.index('c1_s_slack')
                                    :self.uvars.index('c1_f_slack_thetadot')+1]
        c1_f_u = u[self.uvars.index(
            'c1_f_ddot'):self.uvars.index('c1_f_thetadot')+1]
        # initialize z vector
        z = np.hstack((slacks, c1_f_u, c1_f_u, self.x))
        # update x
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
        self.x[self.xvars.index('c1_s_theta')] = c1_f_theta

    def wrap_phi_c1(self):
        if self.x[self.xvars.index('c1_f_phi')] > 2 * 3.14159:
            self.x[self.xvars.index('c1_f_phi')] -= 2 * 3.14159
            wrapdir = 1
        elif self.x[self.xvars.index('c1_f_phi')] < -2 * 3.14159:
            self.x[self.xvars.index('c1_f_phi')] += 2 * 3.14159
            wrapdir = -1
        else:
            wrapdir = 0
        return wrapdir
