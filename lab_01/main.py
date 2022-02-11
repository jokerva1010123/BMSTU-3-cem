import math

data = open("data.txt", "r")
data_x, data_y, data_y1 = [], [], []
line = [(data.read().split())]
if len(line) == 0:
    print("Пустый файл")
    data.close()
    exit(0)
if len(line) % 3:
    print("Не ")