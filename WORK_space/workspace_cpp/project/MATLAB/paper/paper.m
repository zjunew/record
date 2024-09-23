%% 蒙特卡洛求解解析解无法求解的问题
clear; clc; close all; warning off;

% 生成三个不可积的信号
T = 20;
fs = 1 / 1e3;
x0 = -T : fs : T;
y1 = sin(x0.^ 2);
y2 = sin(x0) ./ x0;
y3 = exp(-x0.^2);

figure(1); clf;
subplot(3, 1, 1);
plot(x0, y1, 'linewidth', 1.5); ylabel('y'); title('y=sin(x^2)'); set(gca, 'fontsize', 12);
subplot(3, 1, 2);
plot(x0, y2, 'linewidth', 1.5); ylabel('y'); title('y=sin(x)/x'); set(gca, 'fontsize', 12);
subplot(3, 1, 3);
plot(x0, y3, 'linewidth', 1.5); xlabel('x'); ylabel('y'); title('y=e^{-x^2}'); set(gca, 'fontsize', 12);

% 绘制围成区域
x = 0 : fs : 2;
y11 = sin(x.^ 2);
y21 = sin(x) ./ x;
y31 = exp(-x.^2);

figure(2); clf;
plot(x, y11, 'linewidth', 1.5); hold on;
plot(x, y21, 'linewidth', 1.5); hold on;
plot(x, y31, 'linewidth', 1.5); hold on;
area(x(y11>y31 & y21>y11), y11(y11>y31 & y21>y11), 'facecolor', 'c', 'edgealpha', 0); hold on;
area(x(y11>y31 & y21>y11), y31(y11>y31 & y21>y11), 'facecolor', 'w', 'edgealpha', 0); hold on;
h = legend('y=sin(x^2)', 'y=sin(x)/x', 'y=e^{-x^2}', 'location', 'southwest');
xlabel('x'); ylabel('y'); title('求三条曲线围成的面积'); set(gca, 'fontsize', 12); set(h, 'fontsize', 12);

% 蒙特卡洛法求面积
L = 2; 
H = 3;
S = L * H;
N_Lis = [1e1, 1e2, 1e3, 1e4];
figure(3); clf;
for n = 1 : length(N_Lis)
    N = N_Lis(n);
    x_random = L * rand(1, N);
    y_random = H * rand(1, N) - 1;
    cnt = 0;
    for i = 1 : N
        if (y_random(i) <= sin(x_random(i)^2)) && (y_random(i) <= sin(x_random(i))/x_random(i)) ...
                && (y_random(i) >= exp(-x_random(i)^2))
            cnt = cnt + 1;
        end
    end
    res_appro = cnt / N * S;
    
    subplot(2, 2, n);
    plot(x, y11, 'linewidth', 1.5); hold on;
    plot(x, y21, 'linewidth', 1.5); hold on;
    plot(x, y31, 'linewidth', 1.5); hold on;
    area(x(y11>y31 & y21>y11), y11(y11>y31 & y21>y11), 'facecolor', 'c', 'edgealpha', 0); hold on;
    area(x(y11>y31 & y21>y11), y31(y11>y31 & y21>y11), 'facecolor', 'w', 'edgealpha', 0); hold on;
    scatter(x_random, y_random, 10, 'r', 'filled', 'markerfacealpha', 0.5);
    xlabel('x'); ylabel('y'); title(['样本数=', num2str(N_Lis(n)), '   近似解≈', num2str(res_appro, '%.2f')]); 
    set(gca, 'fontsize', 14); 
end

h = suptitle('蒙特卡洛法求图形面积');
set(h, 'fontsize', 18);
set(gcf, 'position', [12, 60, 1450, 650]);
