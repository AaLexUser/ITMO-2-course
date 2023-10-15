from odesolver import ODESolver, runge
import bisect

# Define a subclass for Runge-Kutta method
class RungeKuttaMethod(ODESolver):
    def __init__(self, f, a, b, h, y0, eps):
        super().__init__(f, a, b, h, y0, eps)

    def __rk4(self, x, y, h):
        # Method to perform one step of Runge-Kutta method of order 4
        k1 = h * self.f(x, y)
        k2 = h * self.f(x + h / 2, y + k1 / 2)
        k3 = h * self.f(x + h / 2, y + k2 / 2)
        k4 = h * self.f(x + h, y + k3)
        return y + (k1 + 2 * k2 + 2 * k3 + k4) / 6

    def __loop(self, y0):
        # Method to loop over the interval and update the solution
        x = self.a
        dots = [(self.a, y0)]
        while x < self.b:
            y_next = self.__rk4(x, y0, self.h)
            dots.append((x + self.h, y_next))
            x += self.h
            y0 = y_next
        return dots

    def solve(self):
        # Method to solve the ODE using Runge-Kutta method and adjust the step size if needed
        dots = self.__loop(self.y0)
        yh = dots
        self.h /= 2
        dots = self.__loop(self.y0)
        yh2 = dots
        err = runge(yh[-1][-1], yh2[-1][-1], 4)
        if err > self.eps:
            return RungeKuttaMethod(self.f, self.a, self.b, h = self.h / 2, y0 = self.y0, eps = self.eps).solve()
        # index = bisect.bisect_right([x for x,_ in yh], self.b + self.h)
        # del yh[index:]
        return yh
