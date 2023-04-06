% FORCESNLPsolver : A fast customized optimization solver.
% 
% Copyright (C) 2013-2023 EMBOTECH AG [info@embotech.com]. All rights reserved.
% 
% 
% This software is intended for simulation and testing purposes only. 
% Use of this software for any commercial purpose is prohibited.
% 
% This program is distributed in the hope that it will be useful.
% EMBOTECH makes NO WARRANTIES with respect to the use of the software 
% without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
% PARTICULAR PURPOSE. 
% 
% EMBOTECH shall not have any liability for any damage arising from the use
% of the software.
% 
% This Agreement shall exclusively be governed by and interpreted in 
% accordance with the laws of Switzerland, excluding its principles
% of conflict of laws. The Courts of Zurich-City shall have exclusive 
% jurisdiction in case of any dispute.
% 
% [OUTPUTS] = FORCESNLPsolver(INPUTS) solves an optimization problem where:
% Inputs:
% - xinit - matrix of size [9x1]
% - x0 - matrix of size [640x1]
% - all_parameters - matrix of size [1040x1]
% - num_of_threads - scalar
% - receive_floating_license - scalar
% Outputs:
% - x01 - column vector of length 16
% - x02 - column vector of length 16
% - x03 - column vector of length 16
% - x04 - column vector of length 16
% - x05 - column vector of length 16
% - x06 - column vector of length 16
% - x07 - column vector of length 16
% - x08 - column vector of length 16
% - x09 - column vector of length 16
% - x10 - column vector of length 16
% - x11 - column vector of length 16
% - x12 - column vector of length 16
% - x13 - column vector of length 16
% - x14 - column vector of length 16
% - x15 - column vector of length 16
% - x16 - column vector of length 16
% - x17 - column vector of length 16
% - x18 - column vector of length 16
% - x19 - column vector of length 16
% - x20 - column vector of length 16
% - x21 - column vector of length 16
% - x22 - column vector of length 16
% - x23 - column vector of length 16
% - x24 - column vector of length 16
% - x25 - column vector of length 16
% - x26 - column vector of length 16
% - x27 - column vector of length 16
% - x28 - column vector of length 16
% - x29 - column vector of length 16
% - x30 - column vector of length 16
% - x31 - column vector of length 16
% - x32 - column vector of length 16
% - x33 - column vector of length 16
% - x34 - column vector of length 16
% - x35 - column vector of length 16
% - x36 - column vector of length 16
% - x37 - column vector of length 16
% - x38 - column vector of length 16
% - x39 - column vector of length 16
% - x40 - column vector of length 16
function [x01, x02, x03, x04, x05, x06, x07, x08, x09, x10, x11, x12, x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28, x29, x30, x31, x32, x33, x34, x35, x36, x37, x38, x39, x40] = FORCESNLPsolver(xinit, x0, all_parameters, num_of_threads, receive_floating_license)
    
    [output, ~, ~] = FORCESNLPsolverBuildable.forcesCall(xinit, x0, all_parameters, num_of_threads, receive_floating_license);
    x01 = output.x01;
    x02 = output.x02;
    x03 = output.x03;
    x04 = output.x04;
    x05 = output.x05;
    x06 = output.x06;
    x07 = output.x07;
    x08 = output.x08;
    x09 = output.x09;
    x10 = output.x10;
    x11 = output.x11;
    x12 = output.x12;
    x13 = output.x13;
    x14 = output.x14;
    x15 = output.x15;
    x16 = output.x16;
    x17 = output.x17;
    x18 = output.x18;
    x19 = output.x19;
    x20 = output.x20;
    x21 = output.x21;
    x22 = output.x22;
    x23 = output.x23;
    x24 = output.x24;
    x25 = output.x25;
    x26 = output.x26;
    x27 = output.x27;
    x28 = output.x28;
    x29 = output.x29;
    x30 = output.x30;
    x31 = output.x31;
    x32 = output.x32;
    x33 = output.x33;
    x34 = output.x34;
    x35 = output.x35;
    x36 = output.x36;
    x37 = output.x37;
    x38 = output.x38;
    x39 = output.x39;
    x40 = output.x40;
end
