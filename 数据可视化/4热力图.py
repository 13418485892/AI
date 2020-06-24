# 热力图，英文叫heat map，是一种矩阵表示方法，其中矩阵中的元素值用颜色来代表，不同的颜色代表不同大小的值。通过颜色就能直观地知道某个位置上数值的大小。
# 另外你也可以将这个位置上的颜色，与数据集中的其他位置颜色进行比较。
# 我们使用Seaborn中自带的数据集flights，该数据集记录了1949年到1960年期间，每个月的航班乘客的数量。

import seaborn as sns
import matplotlib.pyplot as plt

# 数据准备
flights = sns.load_dataset('flights')
# 取出这三个属性画热力图，坐标点的位置是passengers
data = flights.pivot('month', 'year', 'passengers')
sns.heatmap(data)
plt.show()


'''
import seaborn as sns
import matplotlib.pyplot as plt
import numpy as np
np.random.seed(0)
# 初始化参数
sns.set()
uniform_data = np.random.randn(100, 100)
heatmap = sns.heatmap(uniform_data)
plt.show()
'''
