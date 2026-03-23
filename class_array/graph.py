import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage import uniform_filter1d

data = np.genfromtxt('results.csv', delimiter=',', skip_header=1)
n = data[:, 0]
t = data[:, 1]

coeffs = np.polyfit(n**2 + n, t, 1)
t_fit = coeffs[0] * (n**2 + n) + coeffs[1] 

SMOOTH = 10
t_smooth = uniform_filter1d(t, size=SMOOTH)

fig, ax = plt.subplots(figsize=(12, 6))

ax.plot(n, t, color='steelblue', linewidth=1, label='Оригинал')
ax.scatter(n, t, color='steelblue', s=15)

ax.plot(n, t_smooth, color='green', linewidth=2, label=f'Сглаженный (Сглаживание={SMOOTH})')
ax.scatter(n, t_smooth, color='green', s=15)

ax.plot(n, t_fit, color='tomato', linewidth=2, linestyle='--', label='O(n²) аппроксимация')

ax.set_xlabel('n', fontsize=13)
ax.set_ylabel('Время (сек)', fontsize=13)
ax.set_title('Зависимость времени выполнения от размера входных данных', fontsize=14)
ax.legend(fontsize=12)
ax.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('results_plot.png', dpi=150)
plt.show()