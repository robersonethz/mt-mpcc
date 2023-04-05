from matplotlib.animation import PillowWriter
import pickle
import yaml
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


def plot_results(gif_name):

    zvars = ['s_slack',
             'f_ddot', 'f_deltadot', 'f_thetadot',
             's_ddot', 's_deltadot', 's_thetadot',
             'f_posx', 'f_posy', 'f_phi', 'f_vx', 'f_vy', 'f_omega', 'f_d', 'f_delta', 'f_theta',
             's_posx', 's_posy', 's_phi', 's_vx', 's_vy', 's_omega', 's_d', 's_delta', 's_theta',
             ]

    with open('log_data/log_data_new.pickle', 'rb') as f:
        loaded_obj = pickle.load(f)

    with open('/home/robin/Dev/mpcc_python/DEMO_TRACK.yaml') as stream:
        data = yaml.safe_load(stream)

    half_track_width = 0.46/2

    track = data['track']
    xtrack = track['xCoords']
    xrate = track['xRate']
    ytrack = track['yCoords']
    yrate = track['yRate']
    arcLength = track['arcLength']
    tangentAngle = track['tangentAngle']

    np_xtrack = np.array(xtrack)
    np_xrate = np.array(xrate)
    np_ytrack = np.array(ytrack)
    np_yrate = np.array(yrate)

    z_output = loaded_obj[0]
    simlength, horizon, nvars = z_output.shape

    f_x = []
    f_y = []
    hor_f_x = []
    hor_f_y = []
    s_x = []
    s_y = []
    hor_s_x = []
    hor_s_y = []

    for idx in range(simlength):
        z = z_output[idx, :, :]
        f_x.append(z[0, zvars.index('f_posx')])
        f_y.append(z[0, zvars.index('f_posy')])
        hor_f_x.append(z[1:, zvars.index('f_posx')])
        hor_f_y.append(z[1:, zvars.index('f_posy')])
        s_x.append(z[0, zvars.index('s_posx')])
        s_y.append(z[0, zvars.index('s_posy')])
        hor_s_x.append(z[:, zvars.index('s_posx')])
        hor_s_y.append(z[:, zvars.index('s_posy')])

    plt.plot(np_xtrack, np_ytrack)
    plt.plot(np_xtrack+half_track_width*np_yrate,
             np_ytrack-half_track_width*np_xrate, 'black')
    plt.plot(np_xtrack-half_track_width*np_yrate,
             np_ytrack+half_track_width*np_xrate, 'black')
    plt.scatter(f_x, f_y)
    plt.plot(np.array(hor_f_x), np.array(hor_f_y))

    fig, ax = plt.subplots(1, 1)

    def animate_s(i):
        ax.clear()
        ax.plot()
        plt.xlim([-2, 2])
        plt.ylim([-1.5, 1.5])
        plt.plot(np_xtrack, np_ytrack)
        plt.plot(np_xtrack+half_track_width*np_yrate,
                 np_ytrack-half_track_width*np_xrate, 'black')
        plt.plot(np_xtrack-half_track_width*np_yrate,
                 np_ytrack+half_track_width*np_xrate, 'black')
        plt.scatter(f_x[i], f_y[i])
        plt.plot(np.array(hor_f_x[i]), np.array(hor_f_y[i]), 'red')
        plt.scatter(s_x[i], s_y[i])
        plt.plot(np.array(hor_s_x[i]), np.array(hor_s_y[i]), 'green')
        circle = plt.Circle((f_x[i], f_y[i]), 0.8, color='blue', alpha=0.2)
        ax.add_patch(circle)

    ani = FuncAnimation(fig, animate_s, frames=len(f_x),
                        interval=20, repeat=False)
    from matplotlib.animation import PillowWriter
    # Save the animation as an animated GIF
    ani.save(gif_name, dpi=100,
             writer=PillowWriter(fps=20))
