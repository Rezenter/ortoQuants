function out = syst(x)
global n
r = zeros(1,n)';
r(n) = 1;
global matr
a = [matr; x'];
out = a*x - r;
end

