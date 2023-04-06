class helperObj():
    def __init__(self) -> None:
        pass

        self.xvars = ['c1_f_posx', 'c1_f_posy', 'c1_f_phi', 'c1_f_vx', 'c1_f_vy', 'c1_f_omega', 'c1_f_d', 'c1_f_delta', 'c1_f_theta',
                      'c1_s_posx', 'c1_s_posy', 'c1_s_phi', 'c1_s_vx', 'c1_s_vy', 'c1_s_omega', 'c1_s_d', 'c1_s_delta', 'c1_s_theta']

        self.uvars = ['c1_s_slack', 'c1_f_slack_ddot', 'c1_f_slack_deltadot', 'c1_f_slack_thetadot',
                      'c1_f_ddot', 'c1_f_deltadot', 'c1_f_thetadot',
                      'c1_s_ddot', 'c1_s_deltadot', 'c1_s_thetadot']

        self.pvars = ['c1_f_xd', 'c1_f_yd', 'c1_f_grad_xd', 'c1_f_grad_yd', 'c1_f_theta_hat', 'c1_f_phi_d',
                      'c1_s_xd', 'c1_s_yd', 'c1_s_grad_xd', 'c1_s_grad_yd', 'c1_s_theta_hat', 'c1_s_phi_d',
                      'Q1', 'Q2', 'R1', 'R2', 'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll', 'c1_s0_x', 'c1_s0_y']

        self.zvars = self.uvars + self.xvars
