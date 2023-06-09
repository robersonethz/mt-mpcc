import numpy as np
import matplotlib.pyplot as plt
import pickle
import racer as rc

racer_agent = rc.racer()
z_curr = racer_agent.initialize_trajectory(
    xinit=np.array([0.15, -1.05, 0, 1, 0, 0, 0, 0, 0]))
sim_length = 800

z_output = []
log_info = []

for i in range(sim_length):
    z_return, info = racer_agent.update()
    z_output.append(z_return)
    log_info.append(info)
    # print(z_return[0, 0:2])


list_log = {'z_output': z_output,
            'log_info': log_info
            }


with open('log_data.pickle', 'wb') as f:
    pickle.dump(list_log, f)
