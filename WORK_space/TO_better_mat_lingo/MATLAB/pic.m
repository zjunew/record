% 定义 x 的范围
x = linspace(0, 10, 400);

% 计算对应的 y 值，以满足约束条件
y = 6 - x;

% 绘制约束线
plot(x, y, 'LineWidth', 2);
hold on;

% 填充约束区域
fill([x(1), x, x(end)], [0, y, 0], 'gray');

% 设置坐标轴标签和标题
xlabel('x');
ylabel('y');
title('线性规划示例');

% 显示图例
legend('x + y \leq 6', 'Location', 'northwest');

% 显示图形
grid on;
hold off;
