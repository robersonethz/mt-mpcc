import numpy as np
import matplotlib.pyplot as plt
import pickle
import racer as rc

racer_agent = rc.racer()
xinit = np.array([0.15, -1.05, 0, 1, 0, 0, 0, 0, 0])

z_curr = racer_agent.initialize_trajectory(
    np.tile(xinit, 2))
sim_length = 800

z_output = []
log_info = []
all_parameters_output = []

for i in range(sim_length):
    z_return, info, all_parameters = racer_agent.update()
    z_output.append(z_return)
    all_parameters_output.append(all_parameters)
    log_info.append(info)
    # print(z_return[0, 0:2])


list_log = {'z_output': z_output,
            'all_parameters_output': all_parameters_output,
            'log_info': log_info
            }


with open('log_data/log_data.pickle', 'wb') as f:
    pickle.dump(list_log, f)
