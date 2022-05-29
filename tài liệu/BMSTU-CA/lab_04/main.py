from d2 import d2
from d3 import d3


def menu():
    print("1. Двумерная апроксимация")
    print("2. Трёхмерная апроксимация")
    print("0. Выход")
    print("Выбор: ", end="")
    res = int(input())
    return res


def main():
    choice = menu()
    while choice != 0:
        if choice == 1:
            d2()
        elif choice == 2:
            d3()
        else:
            print("Неверный ввод")
        choice = menu()

main()
