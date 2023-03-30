import utils
import generate_forces_solver
import yaml
import numpy as np
import matplotlib.pyplot as plt
import pickle

with open('/home/robin/Dev/mpcc_python/model_params.yaml') as stream:
    model_params = yaml.safe_load(stream)
with open('/home/robin/Dev/mpcc_python/solver.yaml') as stream:
    config = yaml.safe_load(stream)

# Vehicle params
lr = model_params['lr']
lf = model_params['lf']
m = model_params['m']
I = model_params['I']

# lateral force params
Df = model_params['Df']
Cf = model_params['Cf']
Bf = model_params['Bf']
Dr = model_params['Dr']
Cr = model_params['Cr']
Br = model_params['Br']

# longitudinal force params
Cm1 = model_params['Cm1']
Cm2 = model_params['Cm2']
Cd = model_params['Cd']
Croll = model_params['Croll']

# Simulation params /!\ MUST BE THE SAME AS generate_forces_solver.py
freq = model_params['freq']
dt = 1/freq


# Load track
with open('/home/robin/Dev/mpcc_python/DEMO_TRACK.yaml') as stream:
    data = yaml.safe_load(stream)

track = data['track']
xtrack = track['xCoords']
xrate = track['xRate']
ytrack = track['yCoords']
yrate = track['yRate']
arcLength = track['arcLength']
tangentAngle = track['tangentAngle']

#generate solver
model, codeoptions, outputs_gen, solver = generate_forces_solver.build_solver(N=20, Ts=dt, cfg=config)

# set weights for cost function 
Q = np.array([[20, 0],[0, 1000]]) # weights for contouring and lag error
R = 10*np.eye(3) # weights for changes in torque, steer and theta
R[0,0] = 10
R[1,1] = 10 # change individual weight if necessary
q = 1;

# get initial arclengths
problem = {}
problem['x0'] = np.zeros(model.nvar*model.N) #transpose?
# [x y yaw vx vy dyaw theta torque steer]
#z = [0: x, 1: y, 2: yaw, 3: vx, 4: vy, 5: dyaw, 6: torque, 7: steer, 8: Theta, 9: dtorque, 10: dsteer, 11: dtheta]
problem['xinit'] = np.array([0.15, -1.05, 0, 1, 0, 0, 0, 0, 0]) #include also first inputs in z vector (3 last variables)
next_state = np.zeros(12)
next_state[0:9] = problem['xinit']

problem['all_parameters'] = np.zeros(model.npar*model.N)

theta = np.zeros(model.N)
theta_eff = np.zeros(model.N)

# iterate until initial Theta and dTheta converges

for i in range(100): #was 100
    outputs, exitflag, info = solver.solve(problem)
    theta = outputs['theta']
    dtheta = outputs['dtheta']
    for j in range(model.N):
        
        # theta at stage j
        # iterate through arcLength to find the closest one to theta[j]
        idx = 0
        temp = 100
        while(abs(arcLength[idx] - theta[j]) < temp):
           temp = abs(arcLength[idx] - theta[j])
           idx = idx + 1
        
        if idx != 0:
            idx -= 1
        
        # print(idx)
        problem['x0'][model.nvar*(j)+8] = theta[j]
        problem['x0'][model.nvar*(j)+11] = dtheta[j]
        
        if j>1: # save previous parameters
            problem['all_parameters'][model.npar*(j-1)] = xtrack[idx]
            problem['all_parameters'][model.npar*(j-1)+1] = ytrack[idx]
            problem['all_parameters'][model.npar*(j-1)+2] = xrate[idx]
            problem['all_parameters'][model.npar*(j-1)+3] = yrate[idx]
            problem['all_parameters'][model.npar*(j-1)+4] = arcLength[idx]
            problem['all_parameters'][model.npar*(j-1)+5] = tangentAngle[idx]
            theta_eff[j-1] = arcLength[idx]
        
        # save static params (are rewritten every time in this overhead)
        problem['all_parameters'][model.npar*(j)+6] = Q[0,0]
        problem['all_parameters'][model.npar*(j)+7] = Q[1,1]
        problem['all_parameters'][model.npar*(j)+8] = R[0,0]
        problem['all_parameters'][model.npar*(j)+9] = R[1,1]
        problem['all_parameters'][model.npar*(j)+10] = R[2,2]
        problem['all_parameters'][model.npar*(j)+11] = q
        # problem['all_parameters'][model.npar*(j)+12] = freq
        problem['all_parameters'][model.npar*(j)+12] = lr
        problem['all_parameters'][model.npar*(j)+13] = lf
        problem['all_parameters'][model.npar*(j)+14] = m
        problem['all_parameters'][model.npar*(j)+15] = I
        problem['all_parameters'][model.npar*(j)+16] = Df
        problem['all_parameters'][model.npar*(j)+17] = Cf
        problem['all_parameters'][model.npar*(j)+18] = Bf
        problem['all_parameters'][model.npar*(j)+19] = Dr
        problem['all_parameters'][model.npar*(j)+20] = Cr
        problem['all_parameters'][model.npar*(j)+21] = Br
        problem['all_parameters'][model.npar*(j)+22] = Cm1
        problem['all_parameters'][model.npar*(j)+23] = Cm2
        problem['all_parameters'][model.npar*(j)+24] = Cd
        problem['all_parameters'][model.npar*(j)+25] = Croll
    
    # last stage params are equal to penultimate params
    problem['all_parameters'][model.npar*(model.N-1)] = problem['all_parameters'][model.npar*(model.N-2)]
    problem['all_parameters'][model.npar*(model.N-1)+1] = problem['all_parameters'][model.npar*(model.N-2)+1]
    problem['all_parameters'][model.npar*(model.N-1)+2] = problem['all_parameters'][model.npar*(model.N-2)+2]
    problem['all_parameters'][model.npar*(model.N-1)+3] = problem['all_parameters'][model.npar*(model.N-2)+3]
    problem['all_parameters'][model.npar*(model.N-1)+4] = problem['all_parameters'][model.npar*(model.N-2)+4]
    problem['all_parameters'][model.npar*(model.N-1)+5] = problem['all_parameters'][model.npar*(model.N-2)+5]
    theta_eff[model.N-1] = theta_eff[model.N-2]

# run simulation
sim_length = 20 # number of time steps to simulate
u = np.zeros(3)

# logging initialization
state = np.zeros((sim_length, model.nvar))
last_arc_length = max(arcLength)/2 # is at half, because track has been added to itself to account for laps
exitflags = np.zeros(sim_length)
solvetimes = np.zeros(sim_length)
its = np.zeros(sim_length)

# flag, which is set after each lap to reset
reset = 0;

# helper to advance state
p_help = np.zeros(model.npar)
p_help[12] = lr
p_help[13] = lf
# p_help[15] = freq

for i in range(sim_length):
    state[i,0] = next_state[0]
    state[i,1] = next_state[1]
    state[i,2] = next_state[2]
    state[i,3] = next_state[3]
    state[i,4] = next_state[4]
    state[i,5] = next_state[5]
    state[i,6] = next_state[6]
    state[i,7] = next_state[7]
    state[i,8] = next_state[8]
    
    outputs, exitflag, info = solver.solve(problem)

    exitflags[i] = exitflag
    solvetimes[i] = info.solvetime
    its[i] = info.it

    u[0] = outputs['s0'][9]
    u[1] = outputs['s0'][10]
    u[2] = outputs['s0'][11]
#z = [0: x, 1: y, 2: yaw, 3: vx, 4: vy, 5: dyaw, 6: torque, 7: steer, 8: Theta, 9: dtorque, 10: dsteer, 11: dtheta]

    state[i,9] = u[0]
    state[i,10] = u[1]
    state[i,11] = u[2]

    parameters = problem['all_parameters'][model.npar*(j-1):model.npar*j]

    next_state = utils.advanceState_pacejka(next_state, u, parameters);

    if next_state[8] > last_arc_length:
        next_state[8] = np.mod(next_state[8], last_arc_length) #if the vehicle goes past the start, reset arcLength
        reset = 1
    
    problem['xinit'] = next_state[0:9] # initial state for solver next iteration is the advanced state based on x01
    problem['x0'] = np.tile(next_state, model.N) #TODO Check for dimensions...

    theta = outputs['theta']

    for j in range(model.N): # iterate over all stages and get closest arc length
        if reset: # if past the start reset (maybe better if closeness to start is checked)
            theta[j] = np.mod(theta[j], max(arcLength)/2)
        
        
        idx = 0
        temp = 100
        while abs(arcLength[idx] - theta[j]) < temp:
            temp = abs(arcLength[idx] - theta[j])
            idx = idx + 1
        
        if idx != 0:
            idx = idx-1
        
        
        if j>1:
            problem['all_parameters'][model.npar*(j-1)] = xtrack[idx] #assign linearization parameters for closest theta
            problem['all_parameters'][model.npar*(j-1)+1] = ytrack[idx] # assign linearization parameters for closest theta
            problem['all_parameters'][model.npar*(j-1)+2] = xrate[idx] #assign linearization parameters for closest theta
            problem['all_parameters'][model.npar*(j-1)+3] = yrate[idx] # assign linearization parameters for closest theta
            problem['all_parameters'][model.npar*(j-1)+4] = arcLength[idx] # assign linearization parameters for closest theta
            problem['all_parameters'][model.npar*(j-1)+5] = tangentAngle[idx] # assign linearization parameters for closest theta
            #TODO Check index
    problem['all_parameters'][model.npar*(model.N-1)] = problem['all_parameters'][model.npar*(model.N-2)]
    problem['all_parameters'][model.npar*(model.N-1)+1] = problem['all_parameters'][model.npar*(model.N-2)+1]
    problem['all_parameters'][model.npar*(model.N-1)+2] = problem['all_parameters'][model.npar*(model.N-2)+2]
    problem['all_parameters'][model.npar*(model.N-1)+3] = problem['all_parameters'][model.npar*(model.N-2)+3]
    problem['all_parameters'][model.npar*(model.N-1)+4] = problem['all_parameters'][model.npar*(model.N-2)+4]
    problem['all_parameters'][model.npar*(model.N-1)+5] = problem['all_parameters'][model.npar*(model.N-2)+5]
    reset = 0 #is set at every lap

half_track_width = 0.46/2

np_xtrack = np.array(xtrack)
np_xrate = np.array(xrate)
np_ytrack = np.array(ytrack)
np_yrate = np.array(yrate)

list_log = {'state': state,
            'last_arc_length': last_arc_length, 
            'exitflags': exitflags, 
            'solvetimes': solvetimes, 
            'its': its, 
            'np_xtrack': np_xtrack, 
            'np_xrate': np_xrate, 
            'np_ytrack': np_ytrack, 
            'np_yrate': np_yrate} 



with open('log_data.pickle', 'wb') as f:
    pickle.dump(list_log, f)


# plt.figure(0)

# plt.plot(np_xtrack, np_ytrack)
# plt.plot(np_xtrack+half_track_width*np_yrate,np_ytrack-half_track_width*np_xrate,'black');
# plt.plot(np_xtrack-half_track_width*np_yrate,np_ytrack+half_track_width*np_xrate,'black');x = state[:,0]
# x = state[:,0]
# y = state[:,1]
# plt.scatter(x,y)
# plt.show()

# #z = [0: x, 1: y, 2: yaw, 3: vx, 4: vy, 5: dyaw, 6: torque, 7: steer, 8: Theta, 9: dtorque, 10: dsteer, 11: dtheta]

# # create subplots
# fig, axs = plt.subplots(2, 4)

# n_states = state.shape[0]
# x_axes = np.array(range(n_states))

# # plot the first subplot
# axs[0, 0].plot(x_axes, state[:, 3])
# axs[0, 0].set_title('vx')
# axs[0, 0].legend(['vx'])

# # plot the second subplot
# axs[0, 1].plot(x_axes, state[:, 4])
# axs[0, 1].set_title('vy')
# axs[0, 1].legend(['vy'])

# # plot the third subplot
# axs[0, 2].plot(x_axes, state[:, 8])
# axs[0, 2].set_title('Theta')
# axs[0, 2].legend(['Theta'])

# # plot the fourth subplot
# axs[0, 3].plot(x_axes, state[:, 6])
# axs[0, 3].set_title('T')
# axs[0, 3].legend(['T'])

# # # plot the fifth subplot
# # axs[0, 4].plot(exitflags)
# # axs[0, 4].set_title('exitflags')
# # axs[0, 4].legend(['exitflags'])

# # plot the sixth subplot
# axs[1, 0].plot(x_axes, state[:, 2])
# axs[1, 0].set_title('yaw')
# axs[1, 0].legend(['yaw'])

# # plot the seventh subplot
# axs[1, 1].plot(x_axes, state[:, 5])
# axs[1, 1].set_title('dyaw')
# axs[1, 1].legend(['dyaw'])

# # plot the eighth subplot
# axs[1, 2].plot(state[:, 9])
# axs[1, 2].set_title('delta')
# axs[1, 2].legend(['delta'])

# # plot the tenth subplot
# axs[1, 3].plot(solvetimes)
# axs[1, 3].set_title('solvetimes')
# axs[1, 3].legend(['solvetimes'])

# # adjust the spacing between subplots
# fig.tight_layout()
# plt.figure(1)
# plt.plot()

