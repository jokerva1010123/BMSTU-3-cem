from matplotlib.pyplot import *
import random as rd 

# Кол-во точек в таблице
LEN_T = 6

# Аппроксимирующая функция 
def F(x, k):
    return x ** k

# Функция для заполнения таблицы рандомными значениями
def table_():
    x_arr = []
    y_arr = []
    w_arr = []
    x = rd.random() * 5
    for i in range(LEN_T):
        y = rd.random() * 5
        x_arr.append(x)
        y_arr.append(y)
        w_arr.append(1)
        x += 1
    print(x_arr)
    return x_arr, y_arr, w_arr

# Печать таблицы
def print_table(x, y, ro):
    length = len(x)
    print("|  №  |   x   |    y   |    W   |")
    for i in range(length):
        print("|  %d  | %.4f| %7.4f| %.4f |" % (i + 1, x[i], y[i], ro[i]))
    print()

# Матрица СЛАУ
def makeSLAEmatrix(matrix, n):
    N = len(matrix)
    res = [[0 for i in range(0, n + 1)] for j in range(0, n + 1)]
    col = [0 for i in range(0, n + 1)]
    for i in range(0, n + 1):
        for j in range(N):
            coef = matrix[j][2] * F(matrix[j][0], i)
            for k in range(0, n + 1):
                res[i][k] += coef * F(matrix[j][0], k)
            col[i] += coef * matrix[j][1]
    for i in range(len(col)):
        res[i].append(col[i])
    return res

# Функция метод Гаусс
def method_gauss(mat, degree):
    matrix = makeSLAEmatrix(mat, degree)

    n = len(matrix)
    print(matrix)
    for k in range(n):
        for i in range(k + 1, n):
            coeff = -(matrix[i][k] / matrix[k][k])
            for j in range(k, n + 1):
                matrix[i][j] += coeff * matrix[k][j]
    a = [0 for i in range(n)]
    for i in range(n - 1, -1, -1):
        for j in range(n - 1, i, -1):
            matrix[i][n] -= a[j] * matrix[i][j]
        print(matrix[i][i])
        a[i] = matrix[i][n] / matrix[i][i]
    return a
    
# Функция, если был сделан выбор изменения веса
def chahge_weight(matrix, n):
    print(matrix)
    plot([a[0] for a in matrix], [a[1] for a in matrix], 'o', label='Date')
    dx = (matrix[-1][0] - matrix[0][0]) / 10
    answer = method_gauss(matrix, 1)
    print("Коэффициенты А полинома: ", answer)
    y = []
    x = []
    j = matrix[0][0] - dx
    while j <= matrix[-1][0] + dx:
        buff = 0
        for k in range(0, 1 + 1):
            buff += F(j, k) * answer[k]
        y.append(buff)
        x.append(j)
        j += 0.01
        
    plot(x, y, label='ro = 1 и n = 1')
    answer = method_gauss(matrix, n)
    print("Коэффициенты А полинома: ", answer)
    y = []
    x = []
    j = matrix[0][0] - dx
    while j <= matrix[-1][0] + dx:
        buff = 0
        for k in range(0, n + 1):
            buff += F(j, k) * answer[k]
        y.append(buff)
        x.append(j)
        j += 0.01
        
    plot(x, y, label='ro = 1 и n = ' + str(n))

    number = 0
    while number != 'x':
        number = input("Введите номер точки и её новый вес(чтобы закончить ввод - введите 'x'):")
        if number == 'x':
            print_table([a[0] for a in matrix], [a[1] for a in matrix],  [a[2] for a in matrix])
            dx = (matrix[-1][0] - matrix[0][0]) / 10
            answer = method_gauss(matrix, 1)
            print("Коэффициенты А полинома: ", answer)
            y = []
            x = []
            j = matrix[0][0] - dx
            while j <= matrix[-1][0] + dx:
                buff = 0
                for k in range(0, 1 + 1):
                    buff += F(j, k) * answer[k]
                y.append(buff)
                x.append(j)
                j += 0.01
                
            plot(x, y, label='Веса разные, n = 1')
            answer = method_gauss(matrix, n)
            print("Коэффициенты А полинома: ", answer)
            y = []
            x = []
            j = matrix[0][0] - dx
            while j <= matrix[-1][0] + dx:
                buff = 0
                for k in range(0, n + 1):
                    buff += F(j, k) * answer[k]
                y.append(buff)
                x.append(j)
                j += 0.01
                
            plot(x, y, label='Веса разные и n = ' + str(n))

            legend()
            title("Наилучшее среднеквадратичное приближние.")
            grid()
            xlabel('x')
            ylabel('y')
            show()
            return 
        try:
            number = number.split()
            number[0] = int(number[0])
            number[1] = float(number[1])
        except Exception:
            print("Значение невозможно считать")
        else:
            if number[0] > 0 and number[0] < len(matrix):
                try:
                    matrix[number[0]][2] = number[1]
                except Exception:
                    print("Значение невозможно считать.")


# Главная функция
def main():
    # x_coor = [1.5,2.1,3.6,4.2,5.8,6.3]
    # y_coor = [3.2,5.6,3.2,-0.51,1.1,2.54]
    # w = [1,1,1,1,1,1]
    # # w = [0.1, 0.1, 0.1, 5.1, 3.9, 9.1]
    # # x_coor, y_coor, w = table()
    x_coor = []
    y_coor = []
    w = []
    table = []
    x_coor, y_coor, w = table_()
    for i in range(len(w)):
        table.append([x_coor[i], y_coor[i], w[i]])

    print("Принятая таблица:\n")
    print_table(x_coor, y_coor, w)

    degree = -1
    while degree < 0:
        try:
            degree = int(input("Введите степень аппроксимирующего полинома: "))
        except Exception:
            print("Неверная степень. Степень должна быть больше 0.\n")

    print("Выберите\n1. Изменить веса в таблице по номеру точки\n2. Получить результат работы программы")
    choice = 0
    while choice <= 0 or choice >= 3:
        try:
            choice = int(input("Ваш выбор: "))
        except Exception:
            print("Невозможно считать значение. Повторите попытку.\n")

    if choice == 1:
        chahge_weight(table, degree)

    else:
        plot(x_coor, y_coor, 'o', label='Date')
        dx = (table[-1][0] - table[0][0]) / 10
        for i in range(1, degree + 1):
            answer = method_gauss(table, i)
            print("Коэффициенты А полинома: ", answer)
            y = []
            x = []
            j = table[0][0] - dx
            while j <= table[-1][0] + dx:
                buff = 0
                for k in range(0, i + 1):
                    buff += F(j, k) * answer[k]
                y.append(buff)
                x.append(j)
                j += 0.01
            plot(x, y, label='n = ' + str(i))
        legend()
        title("Наилучшее среднеквадратичное приближние.")
        grid()
        xlabel('x')
        ylabel('y')
        show()

if __name__ == '__main__':
    main()