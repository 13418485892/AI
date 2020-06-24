import pandas as pd
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt


# 数据准备
N = 5000
x = np.random.rand(N)
y = np.random.rand(N)

# 用matplotlib画图
plt.scatter(x, y, marker='.')
plt.show()
