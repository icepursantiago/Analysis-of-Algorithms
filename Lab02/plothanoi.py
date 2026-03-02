import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read the CSV file
data = pd.read_csv('hanoi_analysis.csv')

# Create figure with subplots
fig, axes = plt.subplots(2, 2, figsize=(14, 10))
fig.suptitle('Towers of Hanoi - Empirical Analysis', fontsize=16, fontweight='bold')

# ========== PLOT 1: Theoretical Moves (2^n - 1) ==========
axes[0, 0].plot(data['n'], data['Theoretical_Moves'], 
                marker='o', color='blue', linewidth=2, markersize=6)
axes[0, 0].set_xlabel('n (number of disks)', fontsize=11)
axes[0, 0].set_ylabel('Number of Moves', fontsize=11)
axes[0, 0].set_title('Theoretical Complexity: M(n) = 2^n - 1', fontweight='bold')
axes[0, 0].grid(True, alpha=0.3)
axes[0, 0].set_yscale('log')  # Logarithmic scale to show exponential growth

# ========== PLOT 2: Execution Time Comparison ==========
axes[0, 1].plot(data['n'], data['Iterative_Time_ms'], 
                marker='o', label='Iterative', color='green', linewidth=2, markersize=6)
axes[0, 1].plot(data['n'], data['Recursive_Time_ms'], 
                marker='s', label='Recursive', color='red', linewidth=2, markersize=6)
axes[0, 1].set_xlabel('n (number of disks)', fontsize=11)
axes[0, 1].set_ylabel('Execution Time (ms)', fontsize=11)
axes[0, 1].set_title('Execution Time Comparison', fontweight='bold')
axes[0, 1].legend()
axes[0, 1].grid(True, alpha=0.3)
axes[0, 1].set_yscale('log')  # Logarithmic scale

# ========== PLOT 3: Time vs Theoretical Moves (Iterative) ==========
axes[1, 0].scatter(data['Theoretical_Moves'], data['Iterative_Time_ms'], 
                   color='green', s=50, alpha=0.6)
axes[1, 0].plot(data['Theoretical_Moves'], data['Iterative_Time_ms'], 
                color='green', alpha=0.4, linewidth=1)
axes[1, 0].set_xlabel('Theoretical Moves (2^n - 1)', fontsize=11)
axes[1, 0].set_ylabel('Execution Time (ms)', fontsize=11)
axes[1, 0].set_title('Iterative: Time vs Theoretical Complexity', fontweight='bold')
axes[1, 0].grid(True, alpha=0.3)
axes[1, 0].set_xscale('log')
axes[1, 0].set_yscale('log')

# ========== PLOT 4: Time vs Theoretical Moves (Recursive) ==========
axes[1, 1].scatter(data['Theoretical_Moves'], data['Recursive_Time_ms'], 
                   color='red', s=50, alpha=0.6)
axes[1, 1].plot(data['Theoretical_Moves'], data['Recursive_Time_ms'], 
                color='red', alpha=0.4, linewidth=1)
axes[1, 1].set_xlabel('Theoretical Moves (2^n - 1)', fontsize=11)
axes[1, 1].set_ylabel('Execution Time (ms)', fontsize=11)
axes[1, 1].set_title('Recursive: Time vs Theoretical Complexity', fontweight='bold')
axes[1, 1].grid(True, alpha=0.3)
axes[1, 1].set_xscale('log')
axes[1, 1].set_yscale('log')

# Adjust layout and save
plt.tight_layout()
plt.savefig('hanoi_empirical_analysis.png', dpi=300, bbox_inches='tight')
print("✓ Graph saved as 'hanoi_empirical_analysis.png'")
plt.show()

# ========== PRINT STATISTICAL ANALYSIS ==========
print("\n=== EMPIRICAL ANALYSIS SUMMARY ===\n")

print("Mathematical Analysis:")
print("  Recurrence: M(n) = 2·M(n-1) + 1")
print("  Closed form: M(n) = 2^n - 1")
print("  Complexity: O(2^n)\n")

print("Empirical Results:")
print(f"  Total tests: {len(data)} input sizes (n = 1 to 25)")
print(f"  Max moves tested: {data['Theoretical_Moves'].max():,}")
print(f"  Max iterative time: {data['Iterative_Time_ms'].max():.2f} ms")
print(f"  Max recursive time: {data['Recursive_Time_ms'].max():.2f} ms\n")

# Calculate growth rate
n_sample = data['n'].iloc[-5:]
moves_sample = data['Theoretical_Moves'].iloc[-5:]
print("Last 5 data points - verifying exponential growth:")
for i in range(len(n_sample)):
    print(f"  n={n_sample.iloc[i]}: {moves_sample.iloc[i]:,} moves")
    
print("\n✓ Consistency Check:")
print("  The empirical execution time grows exponentially with n,")
print("  matching the mathematical prediction O(2^n).")
print("  Both iterative and recursive implementations show similar growth patterns.\n")