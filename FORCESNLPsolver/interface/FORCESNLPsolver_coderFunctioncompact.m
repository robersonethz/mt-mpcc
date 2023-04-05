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
% - x0 - matrix of size [1000x1]
% - all_parameters - matrix of size [1360x1]
% - num_of_threads - scalar
% - receive_floating_license - scalar
% Outputs:
% - outputs - column vector of length 1000
function [outputs] = FORCESNLPsolver(xinit, x0, all_parameters, num_of_threads, receive_floating_license)
    
    [output, ~, ~] = FORCESNLPsolverBuildable.forcesCall(xinit, x0, all_parameters, num_of_threads, receive_floating_license);
    outputs = coder.nullcopy(zeros(1000,1));
    outputs(1:25) = output.x01;
    outputs(26:50) = output.x02;
    outputs(51:75) = output.x03;
    outputs(76:100) = output.x04;
    outputs(101:125) = output.x05;
    outputs(126:150) = output.x06;
    outputs(151:175) = output.x07;
    outputs(176:200) = output.x08;
    outputs(201:225) = output.x09;
    outputs(226:250) = output.x10;
    outputs(251:275) = output.x11;
    outputs(276:300) = output.x12;
    outputs(301:325) = output.x13;
    outputs(326:350) = output.x14;
    outputs(351:375) = output.x15;
    outputs(376:400) = output.x16;
    outputs(401:425) = output.x17;
    outputs(426:450) = output.x18;
    outputs(451:475) = output.x19;
    outputs(476:500) = output.x20;
    outputs(501:525) = output.x21;
    outputs(526:550) = output.x22;
    outputs(551:575) = output.x23;
    outputs(576:600) = output.x24;
    outputs(601:625) = output.x25;
    outputs(626:650) = output.x26;
    outputs(651:675) = output.x27;
    outputs(676:700) = output.x28;
    outputs(701:725) = output.x29;
    outputs(726:750) = output.x30;
    outputs(751:775) = output.x31;
    outputs(776:800) = output.x32;
    outputs(801:825) = output.x33;
    outputs(826:850) = output.x34;
    outputs(851:875) = output.x35;
    outputs(876:900) = output.x36;
    outputs(901:925) = output.x37;
    outputs(926:950) = output.x38;
    outputs(951:975) = output.x39;
    outputs(976:1000) = output.x40;
end
