
import casadi
import math
import numpy as np
from casadi import atan, sin, cos

xvars = ['c1_f_posx', 'c1_f_posy', 'c1_f_phi', 'c1_f_vx', 'c1_f_vy', 'c1_f_omega', 'c1_f_d', 'c1_f_delta', 'c1_f_theta',
         # 'c1_s_posx', 'c1_s_posy', 'c1_s_phi', 'c1_s_vx', 'c1_s_vy', 'c1_s_omega', 'c1_s_d', 'c1_s_delta', 'c1_s_theta'
         ]

uvars = [  # 'c1_s_slack',
    'c1_f_ddot', 'c1_f_deltadot', 'c1_f_thetadot',
    # 'c1_s_ddot', 'c1_s_deltadot', 'c1_s_thetadot'
]


pvars = ['c1_f_xd', 'c1_f_yd', 'c1_f_grad_xd', 'c1_f_grad_yd', 'c1_f_theta_hat', 'c1_f_phi_d',
         # 'c1_s_xd', 'c1_s_yd', 'c1_s_grad_xd', 'c1_s_grad_yd', 'c1_s_theta_hat', 'c1_s_phi_d',
         'Q1', 'Q2', 'R1', 'R2', 'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll',
         # 'c1_s0_x', 'c1_s0_y'
         ]

zvars = [  # 'c1_s_slack',
    'c1_f_ddot', 'c1_f_deltadot', 'c1_f_thetadot',
    # 'c1_s_ddot', 'c1_s_deltadot', 'c1_s_thetadot',
    'c1_f_posx', 'c1_f_posy', 'c1_f_phi', 'c1_f_vx', 'c1_f_vy', 'c1_f_omega', 'c1_f_d', 'c1_f_delta', 'c1_f_theta',
    # 'c1_s_posx', 'c1_s_posy', 'c1_s_phi', 'c1_s_vx', 'c1_s_vy', 'c1_s_omega', 'c1_s_d', 'c1_s_delta', 'c1_s_theta'
]


car_dim = 0.07  # move to config?
half_track_width = 0.46/2 - 0.1  # move to config?
hu_car = (half_track_width-car_dim)


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
    c1_f_posx = x[xvars.index('c1_f_posx')]
    c1_f_posy = x[xvars.index('c1_f_posy')]
    c1_f_phi = x[xvars.index('c1_f_phi')]
    c1_f_vx = x[xvars.index('c1_f_vx')]
    c1_f_vy = x[xvars.index('c1_f_vy')]
    c1_f_omega = x[xvars.index('c1_f_omega')]
    c1_f_d = x[xvars.index('c1_f_d')]
    c1_f_delta = x[xvars.index('c1_f_delta')]
    c1_f_theta = x[xvars.index('c1_f_theta')]

    c1_f_ddot = u[uvars.index('c1_f_ddot')]
    c1_f_deltadot = u[uvars.index('c1_f_deltadot')]
    c1_f_thetadot = u[uvars.index('c1_f_thetadot')]

    # build CasADi expressions for dynamic model
    # front lateral tireforce
    c1_f_alphaf = -np.arctan2((c1_f_omega*lf + c1_f_vy), c1_f_vx) + c1_f_delta
    c1_f_Ffy = Df*np.sin(Cf*np.arctan(Bf*c1_f_alphaf))

    # rear lateral tireforce
    c1_f_alphar = np.arctan2((c1_f_omega*lr - c1_f_vy), c1_f_vx)
    c1_f_Fry = Dr*np.sin(Cr*np.arctan(Br*c1_f_alphar))

    # rear longitudinal forces
    c1_f_Frx = (Cm1-Cm2*c1_f_vx) * c1_f_d - Croll - Cd*c1_f_vx*c1_f_vx

    # # SAFE
    # c1_s_posx = x[xvars.index('c1_s_posx')]
    # c1_s_posy = x[xvars.index('c1_s_posy')]
    # c1_s_phi = x[xvars.index('c1_s_phi')]
    # c1_s_vx = x[xvars.index('c1_s_vx')]
    # c1_s_vy = x[xvars.index('c1_s_vy')]
    # c1_s_omega = x[xvars.index('c1_s_omega')]
    # c1_s_d = x[xvars.index('c1_s_d')]
    # c1_s_delta = x[xvars.index('c1_s_delta')]
    # c1_s_theta = x[xvars.index('c1_s_theta')]

    # c1_s_ddot = u[uvars.index('c1_s_ddot')]
    # c1_s_deltadot = u[uvars.index('c1_s_deltadot')]
    # c1_s_thetadot = u[uvars.index('c1_s_thetadot')]

    # c1_s_alphaf = -np.arctan2((c1_s_omega*lf + c1_s_vy), c1_s_vx) + c1_s_delta
    # c1_s_Ffy = Df*np.sin(Cf*np.arctan(Bf*c1_s_alphaf))

    # # rear lateral tireforce
    # c1_s_alphar = np.arctan2((c1_s_omega*lr - c1_s_vy), c1_s_vx)
    # c1_s_Fry = Dr*np.sin(Cr*np.arctan(Br*c1_s_alphar))

    # # rear longitudinal forces
    # c1_s_Frx = (Cm1-Cm2*c1_s_vx) * c1_s_d - Croll - Cd*c1_s_vx*c1_s_vx

    statedot = casadi.vertcat(
        # FAST
        c1_f_vx * np.cos(c1_f_phi) - c1_f_vy * np.sin(c1_f_phi),  # posxdot
        c1_f_vx * np.sin(c1_f_phi) + c1_f_vy * np.cos(c1_f_phi),  # posydot
        c1_f_omega,  # phidot
        1/m * (c1_f_Frx - c1_f_Ffy*np.sin(c1_f_delta) + \
               m*c1_f_vy*c1_f_omega),  # vxdot
        1/m * (c1_f_Fry + c1_f_Ffy*np.cos(c1_f_delta) - \
               m*c1_f_vx*c1_f_omega),  # vydot
        1/I * (c1_f_Ffy*lf*np.cos(c1_f_delta) - c1_f_Fry*lr),  # omegadot
        c1_f_ddot,
        c1_f_deltadot,
        c1_f_thetadot,
        # # SAFE
        # c1_s_vx * np.cos(c1_s_phi) - c1_s_vy * np.sin(c1_s_phi),  # posxdot
        # c1_s_vx * np.sin(c1_s_phi) + c1_s_vy * np.cos(c1_s_phi),  # posydot
        # c1_s_omega,  # phidot
        # 1/m * (c1_s_Frx - c1_s_Ffy*np.sin(c1_s_delta) + \
        #        m*c1_s_vy*c1_s_omega),  # vxdot
        # 1/m * (c1_s_Fry + c1_s_Ffy*np.cos(c1_s_delta) - \
        #        m*c1_s_vx*c1_s_omega),  # vydot
        # 1/I * (c1_s_Ffy*lf*np.cos(c1_s_delta) - c1_s_Fry*lr),  # omegadot
        # c1_s_ddot,
        # c1_s_deltadot,
        # c1_s_thetadot
    )
    return statedot


def stage_cost(z, p):
    # extract parameters
    c1_xd = p[pvars.index('c1_f_xd')]
    c1_yd = p[pvars.index('c1_f_yd')]
    c1_phi_d = p[pvars.index('c1_f_phi_d')]
    c1_sin_phit = np.sin(c1_phi_d)
    c1_cos_phit = np.cos(c1_phi_d)
    c1_theta_hat = p[pvars.index('c1_f_theta_hat')]
    Q1 = p[pvars.index('Q1')]
    Q2 = p[pvars.index('Q2')]
    q = p[pvars.index('q')]
    R1 = p[pvars.index('R1')]
    R2 = p[pvars.index('R2')]

    # extract states
    c1_posx = z[zvars.index('c1_f_posx')]
    c1_posy = z[zvars.index('c1_f_posy')]
    c1_theta = z[zvars.index('c1_f_theta')]

    # extract inputs
    # c1_s_slack = z[zvars.index('c1_s_slack')]
    c1_ddot = z[zvars.index('c1_f_ddot')]
    c1_deltadot = z[zvars.index('c1_f_deltadot')]
    c1_thetadot = z[zvars.index('c1_f_thetadot')]

    # c1_s_vx = z[zvars.index('c1_s_vx')]
    # Q_s = 10  # TODO move to config

    # compute approximate linearized contouring and lag error
    c1_xt_hat = c1_xd + c1_cos_phit * (c1_theta - c1_theta_hat)
    c1_yt_hat = c1_yd + c1_sin_phit * (c1_theta - c1_theta_hat)

    c1_e_cont = c1_sin_phit * (c1_xt_hat - c1_posx) - \
        c1_cos_phit * (c1_yt_hat - c1_posy)
    c1_e_lag = c1_cos_phit * (c1_xt_hat - c1_posx) + \
        c1_sin_phit * (c1_yt_hat - c1_posy)

    c1_cost = c1_e_cont * Q1 * c1_e_cont + c1_e_lag * Q2 * c1_e_lag - q * \
        c1_thetadot + c1_ddot * R1 * c1_ddot + c1_deltadot * R2 * \
        c1_deltadot  # + c1_s_slack*100 + c1_s_slack**2*100

    return c1_cost


def dynamics_RK4(z, p, freq):
    """Runge Kutta 4 Approximation of car dynamics. z are stacked states and inputs, p the parameters and freq the frequency"""
    u = z[:len(uvars)]
    x = z[len(uvars):]

    dt = 1/freq
    k1 = continuous_dynamics(x, u, p)
    k2 = continuous_dynamics(x + (dt / 2.0) * k1, u, p)
    k3 = continuous_dynamics(x + (dt / 2.0) * k2, u, p)
    k4 = continuous_dynamics(x + dt * k3, u, p)

    next_state = x + (dt / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4)

    return next_state


def nonlinear_ineq_sameInput(z, p):

    # extract parameters
    c1_f_xt = p[pvars.index('c1_f_xd')]
    c1_f_yt = p[pvars.index('c1_f_yd')]
    c1_f_phit = p[pvars.index('c1_f_phi_d')]
    c1_f_sin_phit = np.sin(c1_f_phit)
    c1_f_cos_phit = np.cos(c1_f_phit)
    c1_f_theta_hat = p[pvars.index('c1_f_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    c1_f_posx = z[zvars.index('c1_f_posx')]
    c1_f_posy = z[zvars.index('c1_f_posy')]
    c1_f_theta = z[zvars.index('c1_f_theta')]

    # compute approximate linearized contouring and lag error
    c1_f_xt_hat = c1_f_xt + c1_f_cos_phit * (c1_f_theta - c1_f_theta_hat)
    c1_f_yt_hat = c1_f_yt + c1_f_sin_phit * (c1_f_theta - c1_f_theta_hat)

    c1_s_xt = p[pvars.index('c1_s_xd')]
    c1_s_yt = p[pvars.index('c1_s_yd')]
    c1_s_phit = p[pvars.index('c1_s_phi_d')]
    c1_s_sin_phit = np.sin(c1_s_phit)
    c1_s_cos_phit = np.cos(c1_s_phit)
    c1_s_theta_hat = p[pvars.index('c1_s_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    c1_s_posx = z[zvars.index('c1_s_posx')]
    c1_s_posy = z[zvars.index('c1_s_posy')]
    c1_s_theta = z[zvars.index('c1_s_theta')]

    # compute approximate linearized contouring and lag error
    c1_s_xt_hat = c1_s_xt + c1_s_cos_phit * (c1_s_theta - c1_s_theta_hat)
    c1_s_yt_hat = c1_s_yt + c1_s_sin_phit * (c1_s_theta - c1_s_theta_hat)

    c1_s_slack = z[zvars.index('c1_s_slack')]

    # inside track <=> tval <= 0
    c1_f_tval = (c1_f_xt_hat-c1_f_posx)**2 + (c1_f_yt_hat-c1_f_posy)**2 - \
        (half_track_width-widthcar)**2

    # inside track <=> tval <= 0
    c1_s_tval = (c1_s_xt_hat-c1_s_posx)**2 + (c1_s_yt_hat-c1_s_posy)**2 - \
        (half_track_width-widthcar)**2 + c1_s_slack

    # Same input
    c1_f_ddot = z[zvars.index('c1_f_ddot')]
    c1_f_deltadot = z[zvars.index('c1_f_deltadot')]
    c1_f_thetadot = z[zvars.index('c1_f_thetadot')]
    c1_s_ddot = z[zvars.index('c1_s_ddot')]
    c1_s_deltadot = z[zvars.index('c1_s_deltadot')]
    c1_s_thetadot = z[zvars.index('c1_s_thetadot')]

    c1_ddot_cond = c1_f_ddot - c1_s_ddot
    c1_deltadot_cond = c1_f_deltadot - c1_s_deltadot
    c1_thetadot_cond = c1_f_thetadot - c1_s_thetadot

    return casadi.vertcat(  # c1_f_tval,
        c1_s_tval,
        c1_ddot_cond,
        c1_deltadot_cond,
        c1_thetadot_cond
    )


def nonlinear_ineq_standard(z, p):

    # extract parameters
    c1_f_xt = p[pvars.index('c1_f_xd')]
    c1_f_yt = p[pvars.index('c1_f_yd')]
    c1_f_phit = p[pvars.index('c1_f_phi_d')]
    c1_f_sin_phit = np.sin(c1_f_phit)
    c1_f_cos_phit = np.cos(c1_f_phit)
    c1_f_theta_hat = p[pvars.index('c1_f_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    c1_f_posx = z[zvars.index('c1_f_posx')]
    c1_f_posy = z[zvars.index('c1_f_posy')]
    c1_f_theta = z[zvars.index('c1_f_theta')]

    # compute approximate linearized contouring and lag error
    c1_f_xt_hat = c1_f_xt + c1_f_cos_phit * (c1_f_theta - c1_f_theta_hat)
    c1_f_yt_hat = c1_f_yt + c1_f_sin_phit * (c1_f_theta - c1_f_theta_hat)

    c1_s_xt = p[pvars.index('c1_s_xd')]
    c1_s_yt = p[pvars.index('c1_s_yd')]
    c1_s_phit = p[pvars.index('c1_s_phi_d')]
    c1_s_sin_phit = np.sin(c1_s_phit)
    c1_s_cos_phit = np.cos(c1_s_phit)
    c1_s_theta_hat = p[pvars.index('c1_s_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    c1_s_posx = z[zvars.index('c1_s_posx')]
    c1_s_posy = z[zvars.index('c1_s_posy')]
    c1_s_theta = z[zvars.index('c1_s_theta')]

    c1_s_slack = z[zvars.index('c1_s_slack')]

    # compute approximate linearized contouring and lag error
    c1_s_xt_hat = c1_s_xt + c1_s_cos_phit * (c1_s_theta - c1_s_theta_hat)
    c1_s_yt_hat = c1_s_yt + c1_s_sin_phit * (c1_s_theta - c1_s_theta_hat)

    # inside track <=> tval <= 0
    c1_f_tval = (c1_f_xt_hat-c1_f_posx)**2 + (c1_f_yt_hat-c1_f_posy)**2 - \
        (half_track_width-widthcar)**2

    # inside track <=> tval <= 0
    c1_s_tval = (c1_s_xt_hat-c1_s_posx)**2 + (c1_s_yt_hat-c1_s_posy)**2 - \
        (half_track_width-widthcar)**2 + c1_s_slack

    return casadi.vertcat(  # c1_f_tval,
        c1_s_tval
    )


def nonlinear_ineq_final(z, p):

    # extract parameters
    c1_f_xt = p[pvars.index('c1_f_xd')]
    c1_f_yt = p[pvars.index('c1_f_yd')]
    c1_f_phit = p[pvars.index('c1_f_phi_d')]
    c1_f_sin_phit = np.sin(c1_f_phit)
    c1_f_cos_phit = np.cos(c1_f_phit)
    c1_f_theta_hat = p[pvars.index('c1_f_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    c1_f_posx = z[zvars.index('c1_f_posx')]
    c1_f_posy = z[zvars.index('c1_f_posy')]
    c1_f_theta = z[zvars.index('c1_f_theta')]

    # compute approximate linearized contouring and lag error
    c1_f_xt_hat = c1_f_xt + c1_f_cos_phit * (c1_f_theta - c1_f_theta_hat)
    c1_f_yt_hat = c1_f_yt + c1_f_sin_phit * (c1_f_theta - c1_f_theta_hat)

    c1_s_xt = p[pvars.index('c1_s_xd')]
    c1_s_yt = p[pvars.index('c1_s_yd')]
    c1_s_phit = p[pvars.index('c1_s_phi_d')]
    c1_s_sin_phit = np.sin(c1_s_phit)
    c1_s_cos_phit = np.cos(c1_s_phit)
    c1_s_theta_hat = p[pvars.index('c1_s_theta_hat')]
    half_track_width = 0.46/2  # TODO move to config
    lf = p[pvars.index('lf')]
    lr = p[pvars.index('lr')]

    lencar = lf+lr
    widthcar = lencar/2

    # extract relevant states
    c1_s_posx = z[zvars.index('c1_s_posx')]
    c1_s_posy = z[zvars.index('c1_s_posy')]
    c1_s_theta = z[zvars.index('c1_s_theta')]

    # compute approximate linearized contouring and lag error
    c1_s_xt_hat = c1_s_xt + c1_s_cos_phit * (c1_s_theta - c1_s_theta_hat)
    c1_s_yt_hat = c1_s_yt + c1_s_sin_phit * (c1_s_theta - c1_s_theta_hat)

    # inside track <=> tval <= 0
    c1_f_tval = (c1_f_xt_hat-c1_f_posx)**2 + (c1_f_yt_hat-c1_f_posy)**2 - \
        (half_track_width-widthcar)**2

    c1_s_slack = z[zvars.index('c1_s_slack')]

    # inside track <=> tval <= 0
    c1_s_tval = (c1_s_xt_hat-c1_s_posx)**2 + (c1_s_yt_hat-c1_s_posy)**2 - \
        (half_track_width-widthcar)**2 + c1_s_slack

    c1_s_vx = z[zvars.index('c1_s_vx')]
    c1_s_vy = z[zvars.index('c1_s_vy')]

    return casadi.vertcat(  # c1_f_tval,
        c1_s_tval,
        c1_s_vx
        #   c1_s_vy
    )


def nonlinear_ineq_sameInput_v2(z, p):

    c1_f_posx = z[zvars.index('c1_f_posx')]
    c1_f_posy = z[zvars.index('c1_f_posy')]
    c1_f_xd = p[pvars.index('c1_f_xd')]
    c1_f_yd = p[pvars.index('c1_f_yd')]
    c1_f_tval = (c1_f_posx-c1_f_xd)*(c1_f_posx-c1_f_xd) + \
        (c1_f_posy-c1_f_yd)*(c1_f_posy-c1_f_yd)

    c1_s_posx = z[zvars.index('c1_s_posx')]
    c1_s_posy = z[zvars.index('c1_s_posy')]
    c1_s_xd = p[pvars.index('c1_s_xd')]
    c1_s_yd = p[pvars.index('c1_s_yd')]

    c1_s_slack = z[zvars.index('c1_s_slack')]

    c1_s_tval = (c1_s_posx-c1_s_xd)**2 + (c1_s_posy -
                                          c1_s_yd)**2 - (hu_car+c1_s_slack)**2

    # Same input
    c1_f_ddot = z[zvars.index('c1_f_ddot')]
    c1_f_deltadot = z[zvars.index('c1_f_deltadot')]
    c1_f_thetadot = z[zvars.index('c1_f_thetadot')]
    c1_s_ddot = z[zvars.index('c1_s_ddot')]
    c1_s_deltadot = z[zvars.index('c1_s_deltadot')]
    c1_s_thetadot = z[zvars.index('c1_s_thetadot')]

    c1_ddot_cond = c1_f_ddot - c1_s_ddot
    c1_deltadot_cond = c1_f_deltadot - c1_s_deltadot
    c1_thetadot_cond = c1_f_thetadot - c1_s_thetadot

    c1_s0_x = p[pvars.index('c1_s0_x')]
    c1_s0_y = p[pvars.index('c1_s0_y')]

    c1_s_antena = (c1_s0_x-c1_s_posx)**2 + (c1_s0_y-c1_s_posy)**2

    return casadi.vertcat(  # c1_f_tval,
        c1_s_tval,
        c1_ddot_cond,
        c1_deltadot_cond,
        c1_thetadot_cond,
        c1_s_antena
    )


def nonlinear_ineq_standard_v2(z, p):
    c1_f_posx = z[zvars.index('c1_f_posx')]
    c1_f_posy = z[zvars.index('c1_f_posy')]
    c1_f_xd = p[pvars.index('c1_f_xd')]
    c1_f_yd = p[pvars.index('c1_f_yd')]
    c1_f_tval = (c1_f_posx-c1_f_xd)*(c1_f_posx-c1_f_xd) + \
        (c1_f_posy-c1_f_yd)*(c1_f_posy-c1_f_yd)

    # c1_s_posx = z[zvars.index('c1_s_posx')]
    # c1_s_posy = z[zvars.index('c1_s_posy')]
    # c1_s_xd = p[pvars.index('c1_s_xd')]
    # c1_s_yd = p[pvars.index('c1_s_yd')]

    # c1_s_slack = z[zvars.index('c1_s_slack')]

    # c1_s_tval = (c1_s_posx-c1_s_xd)**2 + (c1_s_posy -
    #                                       c1_s_yd)**2 - (hu_car+c1_s_slack)**2

    # c1_s0_x = p[pvars.index('c1_s0_x')]
    # c1_s0_y = p[pvars.index('c1_s0_y')]

    # c1_s_antena = (c1_s0_x-c1_s_posx)**2 + (c1_s0_y-c1_s_posy)**2

    # Do not return c1_f_tval : cost should be enough
    return casadi.vertcat(  # c1_f_tval,
        c1_f_tval
        # c1_s_tval,
        # c1_s_antena
    )


def nonlinear_ineq_final_v2(z, p):
    c1_f_posx = z[zvars.index('c1_f_posx')]
    c1_f_posy = z[zvars.index('c1_f_posy')]
    c1_f_xd = p[pvars.index('c1_f_xd')]
    c1_f_yd = p[pvars.index('c1_f_yd')]
    c1_f_tval = (c1_f_posx-c1_f_xd)*(c1_f_posx-c1_f_xd) + \
        (c1_f_posy-c1_f_yd)*(c1_f_posy-c1_f_yd)

    c1_s_posx = z[zvars.index('c1_s_posx')]
    c1_s_posy = z[zvars.index('c1_s_posy')]
    c1_s_xd = p[pvars.index('c1_s_xd')]
    c1_s_yd = p[pvars.index('c1_s_yd')]

    c1_s_slack = z[zvars.index('c1_s_slack')]

    c1_s_tval = (c1_s_posx-c1_s_xd)**2 + (c1_s_posy -
                                          c1_s_yd)**2 - (hu_car+c1_s_slack)**2

    c1_s_vx = z[zvars.index('c1_s_vx')]
    # Do not return c1_f_tval : cost should be enough

    c1_s0_x = p[pvars.index('c1_s0_x')]
    c1_s0_y = p[pvars.index('c1_s0_y')]

    c1_s_antena = (c1_s0_x-c1_s_posx)**2 + (c1_s0_y-c1_s_posy)**2

    return casadi.vertcat(  # c1_f_tval,
        c1_s_tval,
        c1_s_vx,
        c1_s_antena
    )


def get_trackDataIdx_from_theta(theta, arcLength):

    idx = 0
    temp = 100
    while abs(arcLength[idx] - theta) < temp:
        temp = abs(arcLength[idx] - theta)
        idx = idx + 1

    if idx != 0:
        idx = idx-1
    return idx


def wrap_phi_c1(z):
    if z[zvars.index('c1_f_phi')] > 2 * 3.14159:
        wrapdir = 1
    elif z[zvars.index('c1_f_phi')] < -2 * 3.14159:
        wrapdir = -1
    else:
        wrapdir = 0
    return wrapdir
