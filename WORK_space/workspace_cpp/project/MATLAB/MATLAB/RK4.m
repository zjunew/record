In = 0.51;
Out = 0.32;
D = 0.012;
C0 = 0;
tspan = [0, 500];
dt = 1;
C = C0;
t = 0;

while t < tspan(2)
    k1 = (In - Out - D * C) * dt;
    k2 = (In - Out - D * (C + k1 / 2)) * dt;
    k3 = (In - Out - D * (C + k2 / 2)) * dt;
    k4 = (In - Out - D * (C + k3)) * dt;
    C = C + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    t = t + dt;
    
end
fprintf('当稳态时，C(t) = %.4f\n', C);