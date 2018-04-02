import matplotlib.pyplot as plt

file_path = "../build/brownian_bridge.values"

ifile = open(file_path)

x, y = ifile.readlines()
x = [float(i) for i in x.split()]
y = [float(i) for i in y.split()]

print(x)
print(y)

plt.plot([x[0], x[1]], [x[0], x[1]])
plt.plot(x, y)
plt.show()

ifile.close()