% 定义收益矩阵
A_payoff = [-3000, 10000; -inf, 3000];
B_payoff = [-3000, -inf; 10000, 3000];

% 定义变量
syms p q;

% 定义 A 的期望收益
A_expected = p * (q * -3000 + (1 - q) * 10000) + (1 - p) * (q * -inf + (1 - q) * 3000);

% 定义 B 的期望收益
B_expected = q * (p * -3000 + (1 - p) * -inf) + (1 - q) * (p * 10000 + (1 - p) * 3000);

% 数值求解纳什均衡
p0 = 0.5; % 初始猜测值
q0 = 0.5;
[p_sol, q_sol] = fsolve(@(x) [subs(diff(A_expected, p), p, x(1)); subs(diff(B_expected, q), q, x(2))], [p0; q0]);

% 展示解
disp('Nash Equilibrium:');
disp(['p: ', num2str(p_sol)]);
disp(['q: ', num2str(q_sol)]);
