import numpy as np
import matplotlib.pyplot as plt

print("Starting Speedup Plot...")

threads = np.array([1, 2, 4, 6, 8, 10])

times = np.array([
    [0.000, 0.001, 0.001, 0.000, 0.001, 0.000],  # 250x250
    [0.000, 0.004, 0.000, 0.000, 0.000, 0.003],  # 500x500
    [0.000, 0.002, 0.002, 0.001, 0.000, 0.001],  # 750x750
    [0.002, 0.002, 0.003, 0.001, 0.003, 0.001],  # 1000x1000
    [0.011, 0.009, 0.004, 0.005, 0.008, 0.005],  # 2000x2000
])

matrix_sizes = [250, 500, 750, 1000, 2000]
speedup = np.zeros_like(times)

for i in range(len(matrix_sizes)):
    base_time = times[i][0] if times[i][0] != 0 else 1e-6
    for j in range(len(threads)):
        speedup[i][j] = base_time / (times[i][j] if times[i][j] != 0 else 1e-6)

plt.figure(figsize=(10, 6))
for i, size in enumerate(matrix_sizes):
    plt.plot(threads, speedup[i], marker='o', label=f'{size}x{size}')

plt.title('Speedup vs Number of Threads for Matrix Addition')
plt.xlabel('Number of Threads')
plt.ylabel('Speedup')
plt.grid(True)
plt.legend(title="Matrix Size")
plt.xticks(threads)
plt.tight_layout()

# Save instead of showing
plt.savefig("speedup_plot.png")
print("✅ Plot saved as 'speedup_plot.png'")
