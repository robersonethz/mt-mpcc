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
% - x0 - matrix of size [520x1]
% - all_parameters - matrix of size [1040x1]
% - num_of_threads - scalar
% - receive_floating_license - scalar
% Outputs:
% - outputs - column vector of length 520
function [outputs] = FORCESNLPsolver(xinit, x0, all_parameters, num_of_threads, receive_floating_license)
    
    [output, ~, ~] = FORCESNLPsolverBuildable.forcesCall(xinit, x0, all_parameters, num_of_threads, receive_floating_license);
    outputs = coder.nullcopy(zeros(520,1));
    outputs(1:13) = output.x01;
    outputs(14:26) = output.x02;
    outputs(27:39) = output.x03;
    outputs(40:52) = output.x04;
    outputs(53:65) = output.x05;
    outputs(66:78) = output.x06;
    outputs(79:91) = output.x07;
    outputs(92:104) = output.x08;
    outputs(105:117) = output.x09;
    outputs(118:130) = output.x10;
    outputs(131:143) = output.x11;
    outputs(144:156) = output.x12;
    outputs(157:169) = output.x13;
    outputs(170:182) = output.x14;
    outputs(183:195) = output.x15;
    outputs(196:208) = output.x16;
    outputs(209:221) = output.x17;
    outputs(222:234) = output.x18;
    outputs(235:247) = output.x19;
    outputs(248:260) = output.x20;
    outputs(261:273) = output.x21;
    outputs(274:286) = output.x22;
    outputs(287:299) = output.x23;
    outputs(300:312) = output.x24;
    outputs(313:325) = output.x25;
    outputs(326:338) = output.x26;
    outputs(339:351) = output.x27;
    outputs(352:364) = output.x28;
    outputs(365:377) = output.x29;
    outputs(378:390) = output.x30;
    outputs(391:403) = output.x31;
    outputs(404:416) = output.x32;
    outputs(417:429) = output.x33;
    outputs(430:442) = output.x34;
    outputs(443:455) = output.x35;
    outputs(456:468) = output.x36;
    outputs(469:481) = output.x37;
    outputs(482:494) = output.x38;
    outputs(495:507) = output.x39;
    outputs(508:520) = output.x40;
end
