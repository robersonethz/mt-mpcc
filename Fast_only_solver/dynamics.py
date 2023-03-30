import casadi
import numpy as np
import yaml
import utils


class dynamics_simulator():
    def __init__(self, modelparams, x0):

        with open(modelparams) as file:
            params = yaml.load(file, Loader=yaml.FullLoader)

        self.xvars = ['posx', 'posy', 'phi', 'vx',
                      'vy', 'omega', 'd', 'delta', 'theta']
        self.uvars = ['ddot', 'deltadot', 'thetadot']

        # state of system
        self.x = x0

    def old_tick(self, u):
        T_int = self.Ts/self.nodes
        xtemp = self.x
        for idx in range(self.nodes):
            xtemp = self._integrate(T_int, u)
        return self.x

    def tick(self, u, all_parameters, freq):
        z = np.hstack((self.x, u))
        self.x = utils.dynamics_RK4(
            z, all_parameters, freq).full().transpose().reshape(-1)
        return self.x

    def set_theta(self, theta):
        self.x[self.xvars.index('theta')] = theta

    def wrap_phi(self):
        if self.x[self.xvars.index('phi')] > 2 * 3.14159:
            self.x[self.xvars.index('phi')] -= 2 * 3.14159
            wrapdir = 1
        elif self.x[self.xvars.index('phi')] < -2 * 3.14159:
            self.x[self.xvars.index('phi')] += 2 * 3.14159
            wrapdir = -1
        else:
            wrapdir = 0
        return wrapdir
