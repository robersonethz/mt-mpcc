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
% - xinit - matrix of size [18x1]
% - x0 - matrix of size [1120x1]
% - all_parameters - matrix of size [1360x1]
% - num_of_threads - scalar
% - receive_floating_license - scalar
% Outputs:
% - outputs - column vector of length 1120
function [outputs] = FORCESNLPsolver(xinit, x0, all_parameters, num_of_threads, receive_floating_license)
    
    [output, ~, ~] = FORCESNLPsolverBuildable.forcesCall(xinit, x0, all_parameters, num_of_threads, receive_floating_license);
    outputs = coder.nullcopy(zeros(1120,1));
    outputs(1:28) = output.x01;
    outputs(29:56) = output.x02;
    outputs(57:84) = output.x03;
    outputs(85:112) = output.x04;
    outputs(113:140) = output.x05;
    outputs(141:168) = output.x06;
    outputs(169:196) = output.x07;
    outputs(197:224) = output.x08;
    outputs(225:252) = output.x09;
    outputs(253:280) = output.x10;
    outputs(281:308) = output.x11;
    outputs(309:336) = output.x12;
    outputs(337:364) = output.x13;
    outputs(365:392) = output.x14;
    outputs(393:420) = output.x15;
    outputs(421:448) = output.x16;
    outputs(449:476) = output.x17;
    outputs(477:504) = output.x18;
    outputs(505:532) = output.x19;
    outputs(533:560) = output.x20;
    outputs(561:588) = output.x21;
    outputs(589:616) = output.x22;
    outputs(617:644) = output.x23;
    outputs(645:672) = output.x24;
    outputs(673:700) = output.x25;
    outputs(701:728) = output.x26;
    outputs(729:756) = output.x27;
    outputs(757:784) = output.x28;
    outputs(785:812) = output.x29;
    outputs(813:840) = output.x30;
    outputs(841:868) = output.x31;
    outputs(869:896) = output.x32;
    outputs(897:924) = output.x33;
    outputs(925:952) = output.x34;
    outputs(953:980) = output.x35;
    outputs(981:1008) = output.x36;
    outputs(1009:1036) = output.x37;
    outputs(1037:1064) = output.x38;
    outputs(1065:1092) = output.x39;
    outputs(1093:1120) = output.x40;
end
