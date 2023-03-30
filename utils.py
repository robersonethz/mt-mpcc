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

pvars = ['xd', 'yd', 'grad_xd', 'grad_yd', 'theta_hat', 'phi_d', 'Q1', 'Q2', 'R1', 'R2', 'R3',
         'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll']
zvars = ['posx', 'posy', 'phi', 'vx', 'vy', 'omega', 'd',
         'delta', 'theta', 'ddot', 'deltadot', 'thetadot']


def compute_phi(z, s, m):

    harm_arg = 2*math.pi*s*z
    c = np.cos(harm_arg)
    s = np.sin(harm_arg)
    phi = np.vertcat(c, s)

    return phi


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
    posx = x[zvars.index('posx')]
    posy = x[zvars.index('posy')]
    phi = x[zvars.index('phi')]
    vx = x[zvars.index('vx')]
    vy = x[zvars.index('vy')]
    omega = x[zvars.index('omega')]
    d = x[zvars.index('d')]
    delta = x[zvars.index('delta')]
    theta = x[zvars.index('theta')]

    ddot = u[0]
    deltadot = u[1]
    thetadot = u[2]

    # build CasADi expressions for dynamic model
    # front lateral tireforce
    alphaf = -np.arctan2((omega*lf + vy), vx) + delta
    Ffy = Df*np.sin(Cf*np.arctan(Bf*alphaf))

    # rear lateral tireforce
    alphar = np.arctan2((omega*lr - vy), vx)
    Fry = Dr*np.sin(Cr*np.arctan(Br*alphar))

    # rear longitudinal forces
    Frx = (Cm1-Cm2*vx) * d - Croll - Cd*vx*vx

    # let z = [x, u] = [posx, posy, phi, vx, vy, omega, d, delta, theta, ddot, deltadot, thetadot]

    statedot = casadi.vertcat(
        vx * np.cos(phi) - vy * np.sin(phi),  # posxdot
        vx * np.sin(phi) + vy * np.cos(phi),  # posydot
        omega,  # phidot
        1/m * (Frx - Ffy*np.sin(delta) + m*vy*omega),  # vxdot
        1/m * (Fry + Ffy*np.cos(delta) - m*vx*omega),  # vydot
        1/I * (Ffy*lf*np.cos(delta) - Fry*lr),  # omegadot
        ddot,
        deltadot,
        thetadot
    )
    return statedot


def continuous_dynamics_old(x, u, p):
    """Cont. Dynamics. x are the states, u are the inputs p are the parameters."""
    # States
    temp_p = p
    yaw = x[2]
    vx = x[3]
    vy = x[4]
    omega = x[5]
    T = x[6]
    delta = x[7]

    # Inputs
    dT = u[0]
    ddelta = u[1]
    dtheta = u[2]

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

    # dynamics

    alphaf = -np.arctan2((omega*lf + vy), vx) + delta
    Ffy = Df*np.sin(Cf*np.arctan(Bf*alphaf))

    # rear lateral tireforce
    alphar = np.arctan2((omega*lr - vy), vx)
    Fry = Dr*np.sin(Cr*np.arctan(Br*alphar))

    # rear longitudinal forces
    Frx = (Cm1-Cm2*vx) * T - Croll - Cd*vx*vx

    # let z = [x, u] = [posx, posy, phi, vx, vy, omega, d, delta, theta, dT, ddelta, dtheta]

    statedot = casadi.vertcat(
        vx * np.cos(yaw) - vy * np.sin(yaw),  # posxdot
        vx * np.sin(yaw) + vy * np.cos(yaw),  # posydot
        omega,  # phidot
        1/m * (Frx - Ffy*np.sin(delta) + m*vy*omega),  # vxdot
        1/m * (Fry + Ffy*np.cos(delta) - m*vx*omega),  # vydot
        1/I * (Ffy*lf*np.cos(delta) - Fry*lr),  # omegadot
        dT,
        ddelta,
        dtheta
    )
    return statedot


def cost_function_pacejka(z, p):
    """Cost function for the model. Z are states and inputs stacked together, p are parameters."""

    # States
    xp = z[zvars.index('posx')]
    yp = z[zvars.index('posy')]
    theta = z[zvars.index('theta')]

    # Inputs
    dT = z[zvars.index('ddot')]
    ddelta = z[zvars.index('deltadot')]
    dtheta = z[zvars.index('thetadot')]
    # Parameters
    xd = p[pvars.index('xd')]
    yd = p[pvars.index('yd')]
    grad_xd = p[pvars.index('grad_xd')]
    grad_yd = p[pvars.index('grad_yd')]
    theta_hat = p[pvars.index('theta_hat')]
    phi_d = p[pvars.index('phi_d')]
    Q1 = p[pvars.index('Q1')]
    Q2 = p[pvars.index('Q2')]
    R1 = p[pvars.index('R1')]
    R2 = p[pvars.index('R2')]
    R3 = p[pvars.index('R3')]
    q = p[pvars.index('q')]

    # cost
    # TODO rework this part to be more lisible

    eC = casadi.sin(phi_d)*(xp-xd-grad_xd*(theta-theta_hat)) - \
        casadi.cos(phi_d)*(yp-yd-grad_yd*(theta-theta_hat))
    eL = -casadi.cos(phi_d)*(xp-xd-grad_xd*(theta-theta_hat)) - \
        casadi.sin(phi_d)*(yp-yd-grad_yd*(theta-theta_hat))

    c_eC = eC*eC*Q1
    c_eL = eL*eL*Q2
    c_theta = -q*theta
    c_dT = dT*dT*R1
    c_ddelta = ddelta*ddelta*R2
    c_dtheta = dtheta*dtheta*R3

    return c_eC + c_eL + c_theta + c_dT + c_ddelta + c_dtheta


def stage_cost(z, p):
    # extract parameters
    xd = p[pvars.index('xd')]
    yd = p[pvars.index('yd')]
    phi_d = p[pvars.index('phi_d')]
    sin_phit = np.sin(phi_d)
    cos_phit = np.cos(phi_d)
    theta_hat = p[pvars.index('theta_hat')]
    Q1 = p[pvars.index('Q1')]
    Q2 = p[pvars.index('Q2')]
    q = p[pvars.index('q')]
    R1 = p[pvars.index('R1')]
    R2 = p[pvars.index('R2')]

    # extract states
    posx = z[zvars.index('posx')]
    posy = z[zvars.index('posy')]
    theta = z[zvars.index('theta')]

    # extract inputs
    ddot = z[zvars.index('ddot')]
    deltadot = z[zvars.index('deltadot')]
    thetadot = z[zvars.index('thetadot')]

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
    x = z[0:9]
    u = z[9:12]

    dt = 1/freq
    k1 = continuous_dynamics(x, u, p)
    k2 = continuous_dynamics(x + (dt / 2.0) * k1, u, p)
    k3 = continuous_dynamics(x + (dt / 2.0) * k2, u, p)
    k4 = continuous_dynamics(x + dt * k3, u, p)

    next_state = x + (dt / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4)

    return next_state


def nonlinear_ineq(z, p):
    # pvars = ['xd', 'yd', 'grad_xd', 'grad_yd', 'theta_hat', 'phi_d', 'Q1', 'Q2', 'R1', 'R2', 'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll']
    # zvars = ['posx', 'posy', 'phi', 'vx', 'vy', 'omega', 'd', 'delta', 'theta', 'ddot', 'deltadot', 'thetadot']

    # extract parameters
    xt = p[pvars.index('xd')]
    yt = p[pvars.index('yd')]
    phit = p[pvars.index('phi_d')]
    sin_phit = np.sin(phit)
    cos_phit = np.cos(phit)
    theta_hat = p[pvars.index('theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    posx = z[zvars.index('posx')]
    posy = z[zvars.index('posy')]
    theta = z[zvars.index('theta')]

    # compute approximate linearized contouring and lag error
    xt_hat = xt + cos_phit * (theta - theta_hat)
    yt_hat = yt + sin_phit * (theta - theta_hat)

    # inside track <=> tval <= 0
    tval = (xt_hat-posx)**2 + (yt_hat-posy)**2 - (half_track_width-widthcar)**2

    return tval


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
    if z[zvars.index('phi')] > 2 * 3.14159:
        wrapdir = 1
    elif z[zvars.index('phi')] < -2 * 3.14159:
        wrapdir = -1
    else:
        wrapdir = 0
    return wrapdir
