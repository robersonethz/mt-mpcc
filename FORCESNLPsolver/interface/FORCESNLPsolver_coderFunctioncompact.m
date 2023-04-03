% FORCESNLPsolver : A fast customized optimization solver.
% 
% Copyright (C) 2013-2022 EMBOTECH AG [info@embotech.com]. All rights reserved.
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
% - x0 - matrix of size [960x1]
% - all_parameters - matrix of size [1280x1]
% - num_of_threads - scalar
% - receive_floating_license - scalar
% Outputs:
% - outputs - column vector of length 960
function [outputs] = FORCESNLPsolver(xinit, x0, all_parameters, num_of_threads, receive_floating_license)
    
    [output, ~, ~] = FORCESNLPsolverBuildable.forcesCall(xinit, x0, all_parameters, num_of_threads, receive_floating_license);
    outputs = coder.nullcopy(zeros(960,1));
    outputs(1:24) = output.x01;
    outputs(25:48) = output.x02;
    outputs(49:72) = output.x03;
    outputs(73:96) = output.x04;
    outputs(97:120) = output.x05;
    outputs(121:144) = output.x06;
    outputs(145:168) = output.x07;
    outputs(169:192) = output.x08;
    outputs(193:216) = output.x09;
    outputs(217:240) = output.x10;
    outputs(241:264) = output.x11;
    outputs(265:288) = output.x12;
    outputs(289:312) = output.x13;
    outputs(313:336) = output.x14;
    outputs(337:360) = output.x15;
    outputs(361:384) = output.x16;
    outputs(385:408) = output.x17;
    outputs(409:432) = output.x18;
    outputs(433:456) = output.x19;
    outputs(457:480) = output.x20;
    outputs(481:504) = output.x21;
    outputs(505:528) = output.x22;
    outputs(529:552) = output.x23;
    outputs(553:576) = output.x24;
    outputs(577:600) = output.x25;
    outputs(601:624) = output.x26;
    outputs(625:648) = output.x27;
    outputs(649:672) = output.x28;
    outputs(673:696) = output.x29;
    outputs(697:720) = output.x30;
    outputs(721:744) = output.x31;
    outputs(745:768) = output.x32;
    outputs(769:792) = output.x33;
    outputs(793:816) = output.x34;
    outputs(817:840) = output.x35;
    outputs(841:864) = output.x36;
    outputs(865:888) = output.x37;
    outputs(889:912) = output.x38;
    outputs(913:936) = output.x39;
    outputs(937:960) = output.x40;
end
