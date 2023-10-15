from odesolver import ODESolver
from runge_kutta import RungeKuttaMethod
from exact_solution import ExactSolution
import math


class AdamsMethod(ODESolver):
    def __init__(self, f, a, b, h, y0, eps):
        super().__init__(f, a, b, h, y0, eps)

    def solve(self):
        # Method to solve the ODE using Adams method and adjust the step size if needed
        n = int((self.b - self.a) / self.h)
        x = self.a + 4 * self.h
        dots = RungeKuttaMethod(self.f, self.a, min(x, self.b), self.h, self.y0, self.eps).solve()
        del dots[4:]
        x = dots[-1][0]
        while not (round(x + self.h, math.ceil(abs(math.log10(self.eps)) + 1)) > round(self.b, math.ceil(abs(math.log10(self.eps)) + 1))):
            y1 = dots[-1][1] + self.h / 24 * (55 * self.f(dots[-1][0], dots[-1][1]) -
                                              59 * self.f(dots[-2][0], dots[-2][1]) +
                                              37 * self.f(dots[-3][0], dots[-3][1]) -
                                              9 * self.f(dots[-4][0], dots[-4][1]))
            y2 = dots[-1][1] + self.h / 24 * (9 * self.f(x + self.h, y1) +
                                              19 * self.f(dots[-1][0], dots[-1][1]) -
                                              5 * self.f(dots[-2][0], dots[-2][1]) +
                                              self.f(dots[-3][0], dots[-3][1]))
            x += self.h
            dots.append((x, y2))
            if x >= self.b:
                break
        exact_solution = ExactSolution(self.f, self.a, self.b + 5*self.h, self.h, self.y0, self.eps).solve()
        err = max(abs(exact_solution[i][1] - y) for i, (_, y) in enumerate(dots))
        if err > self.eps:
            self.h /= 2
            AdamsMethod(self.f, self.a, self.b, y0= self.y0, h = self.h, eps = self.eps).solve()
        return dots
