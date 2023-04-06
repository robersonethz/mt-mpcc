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
% - outputs - column vector of length 640
function [outputs] = FORCESNLPsolver(xinit, x0, all_parameters, num_of_threads, receive_floating_license)
    
    [output, ~, ~] = FORCESNLPsolverBuildable.forcesCall(xinit, x0, all_parameters, num_of_threads, receive_floating_license);
    outputs = coder.nullcopy(zeros(640,1));
    outputs(1:16) = output.x01;
    outputs(17:32) = output.x02;
    outputs(33:48) = output.x03;
    outputs(49:64) = output.x04;
    outputs(65:80) = output.x05;
    outputs(81:96) = output.x06;
    outputs(97:112) = output.x07;
    outputs(113:128) = output.x08;
    outputs(129:144) = output.x09;
    outputs(145:160) = output.x10;
    outputs(161:176) = output.x11;
    outputs(177:192) = output.x12;
    outputs(193:208) = output.x13;
    outputs(209:224) = output.x14;
    outputs(225:240) = output.x15;
    outputs(241:256) = output.x16;
    outputs(257:272) = output.x17;
    outputs(273:288) = output.x18;
    outputs(289:304) = output.x19;
    outputs(305:320) = output.x20;
    outputs(321:336) = output.x21;
    outputs(337:352) = output.x22;
    outputs(353:368) = output.x23;
    outputs(369:384) = output.x24;
    outputs(385:400) = output.x25;
    outputs(401:416) = output.x26;
    outputs(417:432) = output.x27;
    outputs(433:448) = output.x28;
    outputs(449:464) = output.x29;
    outputs(465:480) = output.x30;
    outputs(481:496) = output.x31;
    outputs(497:512) = output.x32;
    outputs(513:528) = output.x33;
    outputs(529:544) = output.x34;
    outputs(545:560) = output.x35;
    outputs(561:576) = output.x36;
    outputs(577:592) = output.x37;
    outputs(593:608) = output.x38;
    outputs(609:624) = output.x39;
    outputs(625:640) = output.x40;
end
