import sys
import numpy as np
import matplotlib.pyplot as plt

# Check if output path is provided
if len(sys.argv) < 2:
    print("Usage: python3 plot.py <output_file>")
    sys.exit(1)

# Path to save the plot
output_path = sys.argv[1]

# Load data from CSV
data = np.genfromtxt('output.csv', delimiter=',', skip_header=1)

# Separate into x and y
x, y = data[:, 0], data[:, 1]

# Plot the data
plt.plot(x, y, marker='.', linestyle='-', color='k')
plt.xlabel('x')
plt.ylabel('y')
plt.title('C++ Interpolation Data')
plt.grid(True)

# Save the plot
plt.savefig(output_path)
print(f"Plot saved to {output_path}")

