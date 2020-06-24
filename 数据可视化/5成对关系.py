import seaborn as sns
import matplotlib.pyplot as plt

# 数据准备
iris = sns.load_dataset('iris')

# 用seaborn画成对关系
sns.pairplot(iris)
plt.show()
