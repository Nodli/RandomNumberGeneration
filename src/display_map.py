import matplotlib.pyplot as plt

file_path = "../build/perlin_noise.values"

ifile = open(file_path)

size = ifile.readline().split()[1:]
size = [int(i) for i in size]

values = ifile.readline()
values = [float(i) for i in values.split()]

matrixed_values = [[val for val in values[line * size[0]: (line + 1) * size[0]]] for line in range(size[1])]

plt.imshow(matrixed_values, cmap='viridis', interpolation='None')
plt.show()

ifile.close()