def F(x):
    '''
        Функция, которую исслудуем по таблице.
    '''
    return (math.cos(x) - x)



def find_x0_xn(data, power, arg):
    '''
        Нахождение начального и конечного индекса в таблице (x0 и xn).
    '''
    index_x = 0
    
    while arg > data[index_x][0]:
        index_x += 1
    index_x0 = index_x - power // 2 - 1
    index_xn = index_x + (power // 2) + (power % 2) - 1
    if index_xn > len(data) - 1:
        index_x0 -= index_xn - len(data) + 1
        index_xn = len(data) - 1
    elif index_x0 < 0:
        index_xn += -index_x0
        index_x0 = 0
    return index_x0, index_xn

def div_diff(x, y, node):
    '''
        Расчет разделенных разниц для полинома Ньютона
    '''
    pol = []
    for i in range(node):
        pol.append([0] * (node + 1))
    for i in range(node):
        pol[i][0], pol[i][1] = x[i], y[i]
    i = 2
    new_node = node - 1
    while i < (node + 1):
        j = 0
        while j < new_node:
            pol[j][i] = round((pol[j + 1][i - 1] - pol[j][i - 1]) \
                 / (pol[i - 1][0] - pol[0][0]), 5)
            j += 1
        i += 1
        new_node -= 1
    return pol

def polinom_n(x, y, node, arg):
    '''
        Расчет значение функции от заданного аргумента.
        Полином Ньютона.
    '''
    pol = div_diff(x, y, node)
    y = pol[0][1]
    i = 2
    while i < node + 1:
        j, p = 0, 1
        while j < i - 1:
            p *= (arg - pol[j][0])
            j += 1
        y += pol[0][i] * p
        i += 1
    return y 


def hermite_interpolate(data, node, arg, coords_x):
    '''
        Расчет таблицы для полинома Эрмита.
    '''
    # Поиск нужных начала и конца отрезка х
    x0, xn = find_x0_xn(data, node // 2, arg)
    data = data[x0 : xn + 1]
    pol = []
    for i in range(2 * len(data)):
        pol.append([0] * (2 * node + 1))
    i = 0
    for j in range(len(data)):
        pol[i][0], pol[i][1], pol[i][2] = data[j][0], data[j][1], data[j][2]
        i += 1
        pol[i][0], pol[i][1] = data[j][0], data[j][1]
        i += 1
    i = 2
    # Заполнения таблицы, как для полнома Ньютона
    for j in range(len(pol) - 1):
        if j % 2 == 1:
            pol[j][i] = (pol[j][1] - pol[j + 1][1]) \
                 / (pol[j][0] - pol[j + 1][0])
    i = 3
    new_node = node - 2
    while i < len(pol):
        j = 0
        while j < new_node:
            pol[j][i] = round((pol[j + 1][i - 1] - pol[j][i - 1]) \
                 / (pol[i - 1][0] - pol[0][0]), 5)
            j += 1
        i += 1
        new_node -= 1
    return pol


def polynom_h(pol, node, arg):
    '''
        Расчет значение функции от заданного аргумента.
        Полином Эрмита.
    '''
    y = pol[0][1]
    i = 2
    while i < node + 2:
        j = 0
        p = 1
        while j < i - 1:
            p *= (arg - pol[j][0])
            j += 1
        y += pol[0][i] * p
        i += 1
    return y 
