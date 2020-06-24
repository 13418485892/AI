import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# 数据准备
a = np.random.rand(100)
s = pd.Series(a)

# 使用matplotlib
plt.hist(s, 20)
plt.show()
