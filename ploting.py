from matplotlib.animation import PillowWriter
import pickle
import yaml
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


def plot_results(gif_name):

    zvars = ['c1_s_slack',
             'c1_f_ddot', 'c1_f_deltadot', 'c1_f_thetadot',
             'c1_s_ddot', 'c1_s_deltadot', 'c1_s_thetadot',
             'c1_f_posx', 'c1_f_posy', 'c1_f_phi', 'c1_f_vx', 'c1_f_vy', 'c1_f_omega', 'c1_f_d', 'c1_f_delta', 'c1_f_theta',
             'c1_s_posx', 'c1_s_posy', 'c1_s_phi', 'c1_s_vx', 'c1_s_vy', 'c1_s_omega', 'c1_s_d', 'c1_s_delta', 'c1_s_theta']
    pvars = ['c1_f_xd', 'c1_f_yd', 'c1_f_grad_xd', 'c1_f_grad_yd', 'c1_f_theta_hat', 'c1_f_phi_d',
             'c1_s_xd', 'c1_s_yd', 'c1_s_grad_xd', 'c1_s_grad_yd', 'c1_s_theta_hat', 'c1_s_phi_d',
             'Q1', 'Q2', 'R1', 'R2', 'R3', 'q', 'lr', 'lf', 'm', 'I', 'Df', 'Cf', 'Bf', 'Dr', 'Cr', 'Br', 'Cm1', 'Cm2', 'Cd', 'Croll',
             'c1_s0_x', 'c1_s0_y'
             ]

    with open('log_data/log_data_new_cost.pickle', 'rb') as f:
        loaded_obj = pickle.load(f)

    with open('/home/robin/Dev/mpcc_python/DEMO_TRACK.yaml') as stream:
        c1_data = yaml.safe_load(stream)

    half_track_width = 0.46/2

    c1_track = c1_data['track']
    c1_xtrack = c1_track['xCoords']
    c1_xrate = c1_track['xRate']
    c1_ytrack = c1_track['yCoords']
    c1_yrate = c1_track['yRate']
    c1_arcLength = c1_track['arcLength']
    c1_tangentAngle = c1_track['tangentAngle']

    c1_np_xtrack = np.array(c1_xtrack)
    c1_np_xrate = np.array(c1_xrate)
    c1_np_ytrack = np.array(c1_ytrack)
    c1_np_yrate = np.array(c1_yrate)

    z_output = loaded_obj[0]
    parameters_log = loaded_obj[2]

    simlength, horizon, nvars = z_output.shape

    c1_f_x = []
    c1_f_y = []
    c1_hor_f_x = []
    c1_hor_f_y = []
    c1_f_x_center = []
    c1_f_y_center = []

    c1_s_x = []
    c1_s_y = []
    c1_hor_s_x = []
    c1_hor_s_y = []
    c1_s_x_center = []
    c1_s_y_center = []

    for idx in range(simlength):
        z = z_output[idx, :, :]
        p = parameters_log[idx, :, :]
        c1_f_x.append(z[0, zvars.index('c1_f_posx')])
        c1_f_y.append(z[0, zvars.index('c1_f_posy')])
        c1_hor_f_x.append(z[:, zvars.index('c1_f_posx')])
        c1_hor_f_y.append(z[:, zvars.index('c1_f_posy')])
        c1_f_x_center.append(p[:, pvars.index('c1_f_xd')])
        c1_f_y_center.append(p[:, pvars.index('c1_f_yd')])

        c1_s_x.append(z[0, zvars.index('c1_s_posx')])
        c1_s_y.append(z[0, zvars.index('c1_s_posy')])
        c1_hor_s_x.append(z[:, zvars.index('c1_s_posx')])
        c1_hor_s_y.append(z[:, zvars.index('c1_s_posy')])
        c1_s_x_center.append(p[:, pvars.index('c1_s_xd')])
        c1_s_y_center.append(p[:, pvars.index('c1_s_yd')])

        plt.plot(c1_np_xtrack, c1_np_ytrack)
        plt.plot(c1_np_xtrack+half_track_width*c1_np_yrate,
                 c1_np_ytrack-half_track_width*c1_np_xrate, 'black')
        plt.plot(c1_np_xtrack-half_track_width*c1_np_yrate,
                 c1_np_ytrack+half_track_width*c1_np_xrate, 'black')
        plt.scatter(c1_f_x, c1_f_y)
        plt.scatter(c1_s_x_center, c1_s_y_center)
        plt.scatter(c1_hor_f_x, c1_hor_f_y)
        plt.plot(np.array(c1_hor_f_x), np.array(c1_hor_f_y))

        fig, ax = plt.subplots(1, 1)

        car_dim = 0.00  # move to config?
        hu_car = (half_track_width-car_dim)**2

        def animate_s(i):
            ax.clear()
            ax.plot()
            plt.xlim([-2, 2])
            plt.ylim([-1.5, 1.5])
            plt.plot(c1_np_xtrack, c1_np_ytrack)
            plt.plot(c1_np_xtrack+half_track_width*c1_np_yrate,
                     c1_np_ytrack-half_track_width*c1_np_xrate, 'black')
            plt.plot(c1_np_xtrack-half_track_width*c1_np_yrate,
                     c1_np_ytrack+half_track_width*c1_np_xrate, 'black')
            plt.scatter(c1_f_x[i], c1_f_y[i])

            plt.plot(np.array(c1_hor_f_x[i]), np.array(c1_hor_f_y[i]), 'red')
            circle = plt.Circle((c1_f_x[i], c1_f_y[i]),
                                (half_track_width-car_dim), color='yellow', alpha=0.2)
            ax.add_patch(circle)
            plt.scatter(c1_s_x[i], c1_s_y[i])
            plt.plot(np.array(c1_hor_s_x[i]), np.array(c1_hor_s_y[i]), 'green')
            plt.scatter(c1_s_x_center[i], c1_s_y_center[i], c='orange', s=20)
            plt.scatter(c1_hor_s_x[i], c1_hor_s_y[i], c='black', s=5)

            # circle = plt.Circle((c1_f_x[i], c1_f_y[i]),
            #                     0.8, color='blue', alpha=0.2)
            # ax.add_patch(circle)

    ani = FuncAnimation(fig, animate_s, frames=len(c1_f_x),
                        interval=20, repeat=False)
    from matplotlib.animation import PillowWriter
    # Save the animation as an animated GIF
    ani.save(gif_name, dpi=100,
             writer=PillowWriter(fps=10))
