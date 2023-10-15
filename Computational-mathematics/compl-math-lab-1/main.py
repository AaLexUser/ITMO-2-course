import math

import numpy as np

def read_from_file(file_name):
    with open(file_name, "r") as f:
        tol = float(f.readline())
        n = int(f.readline())
        A = np.zeros((n, n))
        b = np.zeros(n)
        for i in range(n):
            row_values = np.fromstring(f.readline(), sep=' ')
            A[i, :] = row_values[:-1]
            b[i] = row_values[-1]
        return tol, n, A, b

def read_from_console():
    tol = float(input("Enter the convergence tolerance: "))
    n = int(input("Enter the number of equations: "))
    A = np.zeros((n, n))
    b = np.zeros(n)
    for i in range(n):
        row = input("Enter coefficients and constant for equation %d"
                    " separated by spaces: " % (i + 1))
        row_values = np.fromstring(row, sep=' ')
        A[i, :] = row_values[:-1]
        b[i] = row_values[-1]
    return tol, n, A, b

def solve():
    input_method = int(input("""Select the input method:
        0 - from console
        1 - from file\n"""))
    if input_method == 0:
        tol, n, A, b = read_from_console()
    elif input_method == 1:
        file_name = input("Enter the file name: ")
        tol, n, A, b = read_from_file(file_name)
    else:
        print("Error: Unknown input method")
        return 0

    if np.linalg.det(A) == 0:
        print("Matrix is degenerate or indefinite")
        return 0

    # Ensure that the diagonal elements are dominant by permuting rows
    for i in range(n):
        max_index = np.argmax(abs(A[i:, i])) + i
        if abs(A[max_index, i]) < np.sum(abs(np.concatenate((A[max_index, 0:i], A[max_index, i+1:])))):
            print("Cannot achieve diagonal dominance")
            return
        A[[i, max_index], :] = A[[max_index, i], :]
        b[[i, max_index]] = b[[max_index, i]]

    D = np.diag(np.diag(A))
    L = np.tril(A, k=-1)
    U = np.triu(A, k=1)
    C = np.linalg.inv(D).dot(- (L + U))
    d = np.linalg.inv(D).dot(b)
    max_iter = 1000
    x = d
    for i in range(max_iter):
        x_new = C.dot(x) + d
        tol_vec = np.max(abs((x_new - x)))
        if tol_vec < tol:
            x = x_new
            break
        x = x_new
    exponent = -int(math.floor(math.log10(abs(tol))))
    print("Solution: ", np.round(x, exponent + 7))
    print("Number of iterations: ", i + 1)
    print("Tolerance vector: ", np.round(tol_vec, exponent + 2))

if __name__ == '__main__':
    solve()
