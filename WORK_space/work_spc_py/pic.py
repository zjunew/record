import numpy as np
import matplotlib.pyplot as plt

# 定义 x 的范围
x = np.linspace(0, 10, 400)

# 计算对应的 y 值，以满足约束条件
y = 6 - x

# 绘制约束线
plt.plot(x, y, label=r'$x + y \leq 6$')

# 填充约束区域
plt.fill_between(x, y, 0, where=(y>=0), color='gray', alpha=0.3)

# 设置坐标轴标签和标题
plt.xlabel('x')
plt.ylabel('y')
plt.title('线性规划示例')

# 显示图例
plt.legend()

# 显示图形
plt.show()
