import math

data = open("data.txt", "r")
data_x, data_y, data_y1 = [], [], []
while True:
    line = list(data.read().split())
    if line == []:
        break
    print(line)

data.close()