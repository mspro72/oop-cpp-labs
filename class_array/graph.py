import numpy as np
import matplotlib.pyplot as plt

# Загрузка данных
data = np.genfromtxt('results.csv', delimiter=',', skip_header=1)
n = data[:, 0]
t = data[:, 1]

fig, ax = plt.subplots(figsize=(12, 6))

# Измеренные данные
ax.plot(n, t, color='steelblue', linewidth=1.5, alpha=0.7, label='Измеренное время')
ax.scatter(n, t, color='steelblue', s=10, alpha=0.5)

# Аппроксимация O(n²)
coeffs = np.polyfit(n**2, t, 1)
t_fit = coeffs[0] * n**2 + coeffs[1]
ax.plot(n, t_fit, color='tomato', linewidth=2, linestyle='--', label='O(n²) аппроксимация')

ax.set_xlabel('n (размер входных данных)', fontsize=13)
ax.set_ylabel('Время (сек)', fontsize=13)
ax.set_title('Зависимость времени выполнения от размера входных данных', fontsize=14)
ax.legend(fontsize=12)
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('results_plot.png', dpi=150)
plt.show()