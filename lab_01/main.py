import math

data_file = open("data.txt", "r")
data_x, data_y, data_y1 = [], [], []
data = data_file.read().split()
data_file.close()
if len(data) == 0:
    print("Пустый файл")
    exit(0)
if len(data) % 3:
    print("Некорректный ввод")
    exit(0)
total_point = len(data) // 3
for i in range(total_point):
    data_x.append(data[i * 3])
    data_y.append(data[i * 3 + 1])
    data_y1.append(data[i * 3 + 2])


