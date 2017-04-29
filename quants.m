clc;
clear all;
global n;
load state.txt
n = length(state);
global matr
matr = state;
fileID = fopen('coeffs.txt','w');
fprintf(fileID,'%2.10f\n', fsolve(@syst, ones(1,n)'));
fclose(fileID);