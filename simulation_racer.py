import numpy as np
import matplotlib.pyplot as plt
import pickle
import racer as rc
import ploting

### PARAMETERS FOR SIMULATION ###

sim_length = 80
init_it = 80
# solver
generate_new_solver = False
max_it_solver = 500


# SIMULATION

racer_agent = rc.racer(
    generate_new_solver=generate_new_solver, init_iter=init_it, max_it_solver=max_it_solver)
c1_xinit = np.array([0.15, -1.05, np.pi, 1, 0, 0, 0, 0, 0])

nvar = 25
horizon = 40

z_log = np.zeros((sim_length, horizon, nvar))
info_log = np.zeros((sim_length, 5))
parameters_log = np.zeros((sim_length, horizon, 34))

print('Init traj')

z_curr = racer_agent.initialize_trajectory(
    np.tile(c1_xinit, 2))


for i in range(sim_length):
    z_return, info, all_parameters = racer_agent.update()

    z_log[i, :, :] = z_return
    info_log[i, :] = info
    parameters_log[i, :, :] = all_parameters

    if i % 10 == 0:
        print(f'Simulation index: {i}')

    # f_posx = z_log[i, 0, 7]
    # s_posx = z_log[i, 0, 16]
    # if abs(f_posx-s_posx) > 0.001:
    #     print("Not the same position, problem!")

    # print(f'from log : f_posx : {f_posx:.2f}, s_posx : {s_posx:.2f}')

print(f'Saving data')
list_log = [z_log, info_log, parameters_log]


with open('log_data/log_data_new_cost.pickle', 'wb') as f:
    pickle.dump(list_log, f)
print('Begin plotting')
ploting.plot_results('log_data/animation_new_cost.gif')
