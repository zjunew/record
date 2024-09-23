C0 = 0; 
In = 0.51; 
Out = 0.32; 
D = 0.012; 

dt = 1;

T = 500; 

C = C0; % 当前污染物浓度
t = 0; % 当前时间

% 使用欧拉法进行数值求解
while t <= T

    C_next = C + dt * (In - Out - D * C);

    C = C_next;
    t = t + dt;
end
fprintf('在稳态时，C(t) = %.4f\n',  C);
