
import casadi
import math
import numpy as np
from casadi import atan, sin, cos

xvars = ['f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
         's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta']

uvars = ['f_ddot', 'f_deltadot', 'f_thetadot',
         's_ddot', 's_deltadot', 's_thetadot']


pvars = ['f_xd', 'f_yd', 'f_grad_xd', 'f_grad_yd', 'f_theta_hat', 'f_phi_d',
         's_xd', 's_yd', 's_grad_xd', 's_grad_yd', 's_theta_hat', 's_phi_d',
         'Q1', 'Q2', 'R1', 'R2', 'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll']

zvars = ['s_slack',
         'f_ddot', 'f_deltadot', 'f_thetadot',
         's_ddot', 's_deltadot', 's_thetadot',
         'f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
         's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta'
         ]
