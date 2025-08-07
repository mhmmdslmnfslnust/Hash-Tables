import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv(r"C:\~ Data\~ BESE\Summer\2025\Start here\Data Structures and Algorithms\Labs\Week 07\Lab 12\Code\To Inifinity\hash_performance.csv")

plt.plot(df["N"], df["Direct Addressing"], label="Direct Addressing")
plt.plot(df["N"], df["Linear Probing"], label="Linear Probing")
plt.plot(df["N"], df["Quadratic Probing"], label="Quadratic Probing")
plt.plot(df["N"], df["Double Hashing"], label="Double Hashing")

plt.xlabel("Number of Keys (N)")
plt.ylabel("Average Lookup Time (ns)")
plt.title("Hashing Technique Performance")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
