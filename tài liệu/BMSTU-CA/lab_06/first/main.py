from matplotlib import pyplot as plt
from numpy import linspace, arange

from function import function

fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

major_ticks = linspace(0, 31, 6)
minor_ticks = linspace(0, 31, 21)

ax.set_xticks(major_ticks)
ax.set_xticks(minor_ticks, minor=True)
# ax.set_yticks(linspace(0, 1, 6))
# ax.set_yticks(linspace(0, 1, 11), minor=True)

# And a corresponding grid
ax.grid(which='both')

# Or if you want different settings for the grids:
ax.grid(which='minor', alpha=0.4)
ax.grid(which='major', alpha=0.8)

n = [1, 10, 15, 20, 25]
m = 10
z = [function(ni, m) for ni in n]
ax.plot(n, z, label=f"z(n, {m})")
print(z[-1])

n = 10
m = [1, 10, 15, 20, 25]
z = [function(n, mi) for mi in m]
ax.plot(m, z, label=f"z({n}, m)")
print(3.553)

plt.legend()
plt.xlabel("n, m")
plt.ylabel("z").set_rotation(0)
#plt.grid()
plt.show()
