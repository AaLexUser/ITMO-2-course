import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.integrate import solve_ivp
from tabulate import tabulate


def runge(yh, yh2, p):
    return abs(yh - yh2) / (2 ** p - 1)


# Define an abstract class for ODE solvers
class ODESolver:
    def __init__(self, f, a, b, h, y0, eps):
        self.f = f  # function defining the ODE dy/dx = f(x, y)
        self.a = a  # lower bound of x
        self.b = b  # upper bound of x
        self.h = h  # step size
        self.y0 = y0  # initial value of y
        self.eps = eps  # maximum error tolerance

    def solve(self):
        # Abstract method to be implemented by subclasses
        raise NotImplementedError

    def plot(self):
        # Method to plot the approximate solution
        dots = self.solve()
        x = [x for x, _ in dots]
        y = [y for _, y in dots]
        plt.plot(x, y)
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Approximate solution to the ODE')
        plt.show()

    @staticmethod
    def print_table(dots):
        # Method to print a beautiful table of results
        headers = ['x', 'y']
        table = tabulate(dots, headers=headers, tablefmt="grid")
        print(table)

