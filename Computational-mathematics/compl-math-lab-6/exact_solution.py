from odesolver import ODESolver
from scipy.integrate import solve_ivp
import numpy as np


class ExactSolution(ODESolver):
    def __init__(self, f, a, b, h, y0, eps):
        super().__init__(f, a, b, h, y0, eps)

    def __ode_function(self, t, y):
        return self.f(t, y)

    def solve(self):
        res = solve_ivp(self.__ode_function, (self.a, self.b+self.h), [self.y0], t_eval=np.arange(self.a, self.b, self.h), method='DOP853')
        dots = [(res.t[i], res.y[0][i]) for i in range(len(res.t))]
        return dots
