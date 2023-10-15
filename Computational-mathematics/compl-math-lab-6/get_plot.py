import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


class Plot:
    @staticmethod
    def plot_all(a, b, exact_solution, euler, runge_kutta, adams):
        dots = exact_solution
        x = [x for x, _ in dots]
        y = [y for _, y in dots]
        plt.plot(x, y, color='red', label='Exact solution', linewidth=3)
        dots = euler
        x = [x for x, _ in dots]
        y = [y for _, y in dots]
        plt.plot(x, y, color='blue', label='Euler method')
        dots = runge_kutta
        x = [x for x, _ in dots]
        y = [y for _, y in dots]
        plt.plot(x, y, color='green', label='Runge-Kutta method')
        dots = adams
        x = [x for x, _ in dots]
        y = [y for _, y in dots]
        plt.plot(x, y, color='orange', label='Adams method')
        plt.xlabel('x')
        plt.ylabel('y')
        plt.title('Comparison of methods')
        plt.legend()
        # Add major and minor gridlines
        plt.grid(which='major', linestyle='-', linewidth=0.5)
        plt.grid(which='minor', linestyle=':', linewidth=0.2)
        plt.minorticks_on()
        plt.show()
