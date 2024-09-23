syms x ;
F = 90 * tand(x) - 9 * 9.81 / 2 / cosd(x)^2 + 0.8;

x1_vals = 35:0.1:55;
y1_vals = subs(F, x, x1_vals);
plot(x1_vals, y1_vals)
xlabel('x');
ylabel('F(x)');
title('Plot of 90*tand(x) - 9* 9.81/2/cosd(x)^2 + 0.8');