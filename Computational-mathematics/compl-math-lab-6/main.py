from data_getter import DataGetter
from euler import EulerMethod
from runge_kutta import RungeKuttaMethod
from adams import AdamsMethod
from odesolver import ODESolver
from exact_solution import ExactSolution
from get_plot import Plot
import numpy as np

if __name__ == '__main__':
    data_getter = DataGetter()
    y0, a, b, h, eps, f = data_getter.get_data()
    euler = EulerMethod(f=f, a=a, b=b, h=h, y0=y0, eps=eps).solve()
    rk4 = RungeKuttaMethod(f=f, a=a, b=b, h=h, y0=y0, eps=eps).solve()
    exact_solution = ExactSolution(f=f, a=a, b=b+h, h=h, y0=y0, eps=eps).solve()
    adams = AdamsMethod(f=f, a=a, b=b, h=h, y0=y0, eps=eps).solve()
    print("########## Euler's method ##########")
    ODESolver.print_table(euler)
    print("########## Runge-Kutta method ##########")
    ODESolver.print_table(rk4)
    print("########## Adams method ##########")
    ODESolver.print_table(adams)
    print("########## Exact solution ##########")
    ODESolver.print_table(exact_solution)
    Plot.plot_all(a, b, exact_solution, euler, rk4, adams)