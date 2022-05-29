import math
from typing import List


a1 = 0.0134
b1 = 1
c1 = 4.35e-4
m1 = 1
R = 0.5

alpha_0 = 1.94e-2
delta = 1.5e3
gamma = 0.2e-2

l = 10
T_0 = 300
F_0 = 50

relax_factor = 0.125
eps = 1e-6

def alpha(T: float) -> float:
    return alpha_0 * (T / delta - 1) ** 4 + gamma

def k(T: float) -> float:
    return a1 * (b1 + c1 * T ** m1)

def p(T: float) -> float:
    return 2 / R * alpha(T)

def f(T: float) -> float:
    return 2 * T_0 / R * alpha(T)

def alpha_prime(T: float) -> float:
    return 4 * alpha_0 / delta * (T / delta - 1) ** 3

def k_prime(T: float) -> float:
    return a1 * c1 * m1 * T ** (m1 - 1)

def p_prime(T: float) -> float:
    return 2 / R * alpha_prime(T)

def f_prime(T: float) -> float:
    return 2 * T_0 / R * alpha_prime(T)

def solve_schema(A: List, B: List, C: List, D: List):
    N = len(A) - 1
    ksi = [0, C[0] / B[0]]
    eta = [0, D[0] / B[0]]
    for n in range(1, N + 1):
        div = (B[n] - A[n] * ksi[n])
        ksi.append(C[n] / div)
        eta.append((D[n] + A[n] * eta[n]) / div)
    X = [None] * (N + 1)
    X[N] = (D[N] + A[N] * eta[N]) / (B[N] - A[N] * ksi[N])
    for n in range(N-1, -1, -1):
        X[n] = ksi[n+1] * X[n+1] + eta[n+1]
    return X

def get_max_diff(X1: List, X2: List) -> float:
    return max(abs((x1 - x2) / x1) for x1, x2 in zip(X1, X2))

# Релаксация для минимизации скачков, если результат сильно отличается от предыдущей итерации
def relax(X1: List, X2: List, factor: float) -> List:
    return [x1 + factor * (x2 - x1) for x1, x2 in zip(X1, X2)]

def solve(N: int):
    h = l / (N - 1)
    h2 = h * h
    X = [i * h for i in range(N)]
    T = [T_0] * N

    max_diff = math.inf
    iterations = 0
    max_iterations = 500
    while max_diff > eps and iterations < max_iterations:
        k_arr = tuple(map(k, T))
        p_arr = tuple(map(p, T))
        f_arr = tuple(map(f, T))
        k_pr_arr = tuple(map(k_prime, T))
        p_pr_arr = tuple(map(p_prime, T))
        f_pr_arr = tuple(map(f_prime, T))

        C0 = 0.5 * (k_arr[0] + k_arr[1])
        B0 = C0 + p_arr[0] * h2
        D0 = f_arr[0] * h2 + F_0 * h

        AN = 0.5 * (k_arr[-2] + k_arr[-1])
        BN = AN + p_arr[-1] * h2 + alpha(T[-1]) * h
        DN = f_arr[-1] * h2 + alpha(T[-1]) * T_0 * h

        A = [0] + [0.5 * (k_arr[i-1] + k_arr[i]) for i in range(1, N-1)] + [AN]
        C = [C0] + [0.5 * (k_arr[i] + k_arr[i+1]) for i in range(1, N-1)] + [0]
        B = [B0] + [A[i] + C[i] + p_arr[i] * h2 for i in range(1, N-1)] + [BN]
        D = [D0] + [f_arr[i] * h2 for i in range(1, N-1)] + [DN]

        Bp0 = B0 + (0.5 * k_pr_arr[0] + p_pr_arr[0] * h2) * T[0] + 0.5 * k_pr_arr[0] * T[1] + f_pr_arr[0] * h2
        Cp0 = C0 + 0.5 * k_pr_arr[1] * (T[1] - T[0])
        Dp0 = -B0 * T[0] + C0 * T[1] + D0

        ApN = AN + 0.5 * k_pr_arr[-2] * (T[-2] - T[-1])
        BpN = BN + (k_pr_arr[-1] + p_pr_arr[-1] * h2) * T[-1] + 0.5 * k_pr_arr[-1] * T[-2] + f_pr_arr[-1] * h2
        DpN = AN * T[-2] - BN * T[-1] + DN

        A_prime = [0] + [A[i] + 0.5 * k_pr_arr[i-1] * (T[i-1] - T[i]) for i in range(1, N-1)] + [ApN]
        B_prime = [Bp0] + [B[i] + (k_pr_arr[i] + p_pr_arr[i] * h2) * T[i] + 0.5 * k_pr_arr[i] * (T[i-1] + T[i+1]) + f_pr_arr[i] * h2 for i in range(1, N-1)] + [BpN]
        C_prime = [Cp0] + [C[i] + 0.5 * k_pr_arr[i+1] * (T[i+1] - T[i]) for i in range(1, N-1)] + [0]
        D_prime = [Dp0] + [A[i] * T[i-1] - B[i] * T[i] + C[i] * T[i+1] + D[i] for i in range(1, N-1)] + [DpN]

        delta_T = solve_schema(A_prime, B_prime, C_prime, D_prime)
        next_T = [T[i] + delta_T[i] for i in range(N)]
        max_diff = get_max_diff(T, next_T)
        T = relax(T, next_T, relax_factor)
        iterations += 1

    return X, T


if __name__ == "__main__":
    import matplotlib.pyplot as plt

    N = 100
    for F_0 in (50, 0, -10):
        X, T = solve(N)
        plt.plot(X, T, label=f"N={N}, F_0={F_0}")

    alpha_0 *= 3

    F_0 = 50
    X, T = solve(N)
    plt.plot(X, T, label=f"N={N}, F_0={F_0}, alpha_0={alpha_0}")

    plt.title("График зависимости ")
    plt.xlim(0, l)
    plt.ylim(0, 2500)
    plt.grid()
    plt.legend()
    plt.show()
