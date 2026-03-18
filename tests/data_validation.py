import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

# Read as df
df = pd.read_csv("../data/weather.csv", delimiter=",")
print(df.columns)

# test
print(df[:1])

# Create single colum of date and time as an index
df["datetime"] = pd.to_datetime(df["date"] + " " + df["time"], format="%Y/%m/%d %H:%M:%S")
# drop columns date and time - not important further
df.set_index("datetime", inplace=True)
df = df.drop(["date", "time"], axis=1)

# test
print(df[:1])

df["rain"] = df["rain"].astype(int)

# Create plot of each colum

plt.rcParams.update({
        "figure.facecolor": "black",
        "axes.facecolor": "black",
        "axes.edgecolor": "white",
        "axes.labelcolor": "white",
        "xtick.color": "white",
        "ytick.color": "white",
        "text.color": "white",
        "grid.color": "#202020"
    })

fig, axes = plt.subplots(4, 2, figsize=(12, 4 * 4))
axes = axes.flatten()

for i, col in enumerate(df.columns):
    axes[i].plot(df.index, df[col], color='red')

    axes[i].set_title(col)
    axes[i].set_xlabel("Time")
    axes[i].set_ylabel(col)

    axes[i].grid(True)
    axes[i].tick_params(axis="x", rotation=45)

plt.tight_layout()
plt.show()
