In = 0.51;
Out = 0.32;
D = 0.012;
C0 = 0;


tspan = [0, 500];

[t, C] = ode45(@(t, y) In - Out - D * y, tspan, C0)

plot(t, C);
xlabel('时间 (小时)');
ylabel('污染物浓度 (kg/m³)');
title('青海湖污染物浓度变化');
grid on;
