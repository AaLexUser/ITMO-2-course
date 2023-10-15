from odesolver import ODESolver, runge
from scipy.integrate import quad


class EulerMethod(ODESolver):
    def __init__(self, f, a, b, h, y0, eps):
        super().__init__(f, a, b, h, y0, eps)

    def euler_step(self, x, y):
        # Method to perform one step of Euler's method
        return y + self.h * self.f(x, y)

    def loop(self, y0):
        # Method to loop over the interval and update the solution
        x = self.a
        dots = [(self.a, y0)]
        while (x+self.h <= self.b):
            y_next = self.euler_step(x, y0)
            dots.append((x + self.h, y_next))
            x += self.h
            y0 = y_next
        return dots

    def solve(self):
        # Method to solve the ODE using Euler's method and adjust the step size if needed
        dots = self.loop(self.y0)
        yh = dots
        dots = self.loop(self.y0)
        self.h /= 2
        yh2 = dots
        err = runge(yh[-1][-1], yh2[-1][-1], 1)
        if err > self.eps:
            return EulerMethod(self.f, self.a, self.b, self.h / 2, self.y0, self.eps).solve()
        return yh
