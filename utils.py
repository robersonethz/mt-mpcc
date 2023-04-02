"""Function (Model Prediction, Cost, ...) for the forces solver.

The variables x, u and p have the following content:

    # States
    xp = x[0]
    yp = x[1]
    yaw = x[2]
    vx = x[3]
    vy = x[4]
    omega = x[5]
    T = x[6]
    delta = x[7]
    theta = x[8]

    x : [0: x, 1: y, 2: yaw, 3: vx, 4: vy, 5: dyaw, 6: torque, 7: steer, 8: Theta,

    # Inputs
    dT = u[0]
    ddelta = u[1]
    dtheta = u[2]

    # Parameters
    xd = p[0]
    yd = p[1]
    grad_xd = p[2]
    grad_yd = p[3]
    theta_hat = p[4]
    phi_d = p[5]
    Q1 = p[6]
    Q2 = p[7]
    R1 = p[8]
    R2 = p[9]
    R3 = p[10]
    q = p[11]
    lr = p[12]
    lf = p[13]
    m = p[14]
    I = p[15]
    Df = p[16]
    Cf = p[17]
    Bf = p[18]
    Dr = p[19]
    Cr = p[20]
    Br = p[21]
    Cm1 = p[22]
    Cm2 = p[23]
    Cd = p[24]
    Croll = p[25]
"""
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

zvars = ['f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
         's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta',
         'f_ddot', 'f_deltadot', 'f_thetadot',
         's_ddot', 's_deltadot', 's_thetadot']


def continuous_dynamics(x, u, p):

    # extract params
    lr = p[pvars.index('lr')]
    lf = p[pvars.index('lf')]
    m = p[pvars.index('m')]
    I = p[pvars.index('I')]
    Df = p[pvars.index('Df')]
    Cf = p[pvars.index('Cf')]
    Bf = p[pvars.index('Bf')]
    Dr = p[pvars.index('Dr')]
    Cr = p[pvars.index('Cr')]
    Br = p[pvars.index('Br')]
    Cm1 = p[pvars.index('Cm1')]
    Cm2 = p[pvars.index('Cm2')]
    Cd = p[pvars.index('Cd')]
    Croll = p[pvars.index('Croll')]

    # extract states and inputs
    # FAST
    f_posx = x[xvars.index('f_posx')]
    f_posy = x[xvars.index('f_posy')]
    f_phi = x[xvars.index('f_phi')]
    f_vx = x[xvars.index('f_vx')]
    f_vy = x[xvars.index('f_vy')]
    f_omega = x[xvars.index('f_omega')]
    f_d = x[xvars.index('f_d')]
    f_delta = x[xvars.index('f_delta')]
    f_theta = x[xvars.index('f_theta')]

    f_ddot = u[uvars.index('f_ddot')]
    f_deltadot = u[uvars.index('f_deltadot')]
    f_thetadot = u[uvars.index('f_thetadot')]

    # SAFE
    s_posx = x[xvars.index('s_posx')]
    s_posy = x[xvars.index('s_posy')]
    s_phi = x[xvars.index('s_phi')]
    s_vx = x[xvars.index('s_vx')]
    s_vy = x[xvars.index('s_vy')]
    s_omega = x[xvars.index('s_omega')]
    s_d = x[xvars.index('s_d')]
    s_delta = x[xvars.index('s_delta')]
    s_theta = x[xvars.index('s_theta')]

    s_ddot = u[uvars.index('s_ddot')]
    s_deltadot = u[uvars.index('s_deltadot')]
    s_thetadot = u[uvars.index('s_thetadot')]

    # build CasADi expressions for dynamic model
    # front lateral tireforce
    f_alphaf = -np.arctan2((f_omega*lf + f_vy), f_vx) + f_delta
    f_Ffy = Df*np.sin(Cf*np.arctan(Bf*f_alphaf))

    # rear lateral tireforce
    f_alphar = np.arctan2((f_omega*lr - f_vy), f_vx)
    f_Fry = Dr*np.sin(Cr*np.arctan(Br*f_alphar))

    # rear longitudinal forces
    f_Frx = (Cm1-Cm2*f_vx) * f_d - Croll - Cd*f_vx*f_vx

    s_alphaf = -np.arctan2((s_omega*lf + s_vy), s_vx) + s_delta
    s_Ffy = Df*np.sin(Cf*np.arctan(Bf*s_alphaf))

    # rear lateral tireforce
    s_alphar = np.arctan2((s_omega*lr - s_vy), s_vx)
    s_Fry = Dr*np.sin(Cr*np.arctan(Br*s_alphar))

    # rear longitudinal forces
    s_Frx = (Cm1-Cm2*s_vx) * s_d - Croll - Cd*s_vx*s_vx

    statedot = casadi.vertcat(
        f_vx * np.cos(f_phi) - f_vy * np.sin(f_phi),  # posxdot
        f_vx * np.sin(f_phi) + f_vy * np.cos(f_phi),  # posydot
        f_omega,  # phidot
        1/m * (f_Frx - f_Ffy*np.sin(f_delta) + m*f_vy*f_omega),  # vxdot
        1/m * (f_Fry + f_Ffy*np.cos(f_delta) - m*f_vx*f_omega),  # vydot
        1/I * (f_Ffy*lf*np.cos(f_delta) - f_Fry*lr),  # omegadot
        f_ddot,
        f_deltadot,
        f_thetadot,

        s_vx * np.cos(s_phi) - s_vy * np.sin(s_phi),  # posxdot
        s_vx * np.sin(s_phi) + s_vy * np.cos(s_phi),  # posydot
        s_omega,  # phidot
        1/m * (s_Frx - s_Ffy*np.sin(s_delta) + m*s_vy*s_omega),  # vxdot
        1/m * (s_Fry + s_Ffy*np.cos(s_delta) - m*s_vx*s_omega),  # vydot
        1/I * (s_Ffy*lf*np.cos(s_delta) - s_Fry*lr),  # omegadot
        s_ddot,
        s_deltadot,
        s_thetadot
    )
    return statedot


def stage_cost(z, p):
    # extract parameters
    xd = p[pvars.index('f_xd')]
    yd = p[pvars.index('f_yd')]
    phi_d = p[pvars.index('f_phi_d')]
    sin_phit = np.sin(phi_d)
    cos_phit = np.cos(phi_d)
    theta_hat = p[pvars.index('f_theta_hat')]
    Q1 = p[pvars.index('Q1')]
    Q2 = p[pvars.index('Q2')]
    q = p[pvars.index('q')]
    R1 = p[pvars.index('R1')]
    R2 = p[pvars.index('R2')]

    # extract states
    posx = z[zvars.index('f_posx')]
    posy = z[zvars.index('f_posy')]
    theta = z[zvars.index('f_theta')]

    # extract inputs
    ddot = z[zvars.index('f_ddot')]
    deltadot = z[zvars.index('f_deltadot')]
    thetadot = z[zvars.index('f_thetadot')]

    # compute approximate linearized contouring and lag error
    xt_hat = xd + cos_phit * (theta - theta_hat)
    yt_hat = yd + sin_phit * (theta - theta_hat)

    e_cont = sin_phit * (xt_hat - posx) - cos_phit * (yt_hat - posy)
    e_lag = cos_phit * (xt_hat - posx) + sin_phit * (yt_hat - posy)

    cost = e_cont * Q1 * e_cont + e_lag * Q2 * e_lag - q * \
        thetadot + ddot * R1 * ddot + deltadot * R2 * deltadot

    return cost


def dynamics_RK4(z, p, freq):
    """Runge Kutta 4 Approximation of car dynamics. z are stacked states and inputs, p the parameters and freq the frequency"""
    x = z[:len(xvars)]
    u = z[len(xvars):]

    dt = 1/freq
    k1 = continuous_dynamics(x, u, p)
    k2 = continuous_dynamics(x + (dt / 2.0) * k1, u, p)
    k3 = continuous_dynamics(x + (dt / 2.0) * k2, u, p)
    k4 = continuous_dynamics(x + dt * k3, u, p)

    next_state = x + (dt / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4)

    return next_state


def nonlinear_ineq(z, p):

    # extract parameters
    f_xt = p[pvars.index('f_xd')]
    f_yt = p[pvars.index('f_yd')]
    f_phit = p[pvars.index('f_phi_d')]
    f_sin_phit = np.sin(f_phit)
    f_cos_phit = np.cos(f_phit)
    f_theta_hat = p[pvars.index('f_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    f_posx = z[zvars.index('f_posx')]
    f_posy = z[zvars.index('f_posy')]
    f_theta = z[zvars.index('f_theta')]

    # compute approximate linearized contouring and lag error
    f_xt_hat = f_xt + f_cos_phit * (f_theta - f_theta_hat)
    f_yt_hat = f_yt + f_sin_phit * (f_theta - f_theta_hat)

    # inside track <=> tval <= 0
    f_tval = (f_xt_hat-f_posx)**2 + (f_yt_hat-f_posy)**2 - \
        (half_track_width-widthcar)**2

    return f_tval


def inequality_constraint(z, p):
    x = z[0]
    y = z[1]
    xd = p[0]
    yd = p[1]
    h = (x - xd)*(x - xd) + (y - yd)*(y - yd)
    return h


def get_trackDataIdx_from_theta(theta, arcLength):

    idx = 0
    temp = 100
    while abs(arcLength[idx] - theta) < temp:
        temp = abs(arcLength[idx] - theta)
        idx = idx + 1

    if idx != 0:
        idx = idx-1
    return idx


def wrap_phi(z):
    if z[zvars.index('f_phi')] > 2 * 3.14159:
        wrapdir = 1
    elif z[zvars.index('f_phi')] < -2 * 3.14159:
        wrapdir = -1
    else:
        wrapdir = 0
    return wrapdir
