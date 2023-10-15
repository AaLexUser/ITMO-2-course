import math
class DataGetter:
    def __init__(self):
        # Initialize the attributes of the class
        self.y0 = None  # initial value of y
        self.a = None  # lower bound of x
        self.b = None  # upper bound of x
        self.h = None  # step size
        self.eps = None  # error tolerance
        self.f = None  # function defining the ODE

    def get_initial_value(self):
        # Method to get the initial value of y from the user
        print('Enter y0:')
        self.y0 = float(input())

    def get_interval(self):
        # Method to get the interval of x from the user
        print('Enter a, b:')
        while True:
            self.a, self.b = map(float, input().split())
            if self.a >= self.b:
                print('Wrong input. Try again:')
            else:
                break

    def get_step_size(self):
        # Method to get the step size from the user
        print('Enter h:')
        while True:
            self.h = float(input())
            if self.h <= 0 or self.h > self.b - self.a:
                print('Wrong input. Try again:')
            else:
                break

    def get_error_tolerance(self):
        # Method to get the error tolerance from the user
        print('Enter eps:')
        while True:
            self.eps = float(input())
            if self.eps <= 0:
                print('Wrong input. Try again:')
            else:
                break

    def get_function(self):
        # Method to get the function defining the ODE from the user
        print('Choose function:')
        print('1. y\' = x^2 - 2y')
        print('2. y\' = 1 + (y - x)^2')
        print('3. y\' = y / x + x / y')
        print('4. y\' = y + (1 + x) * y^2')
        functions = [lambda x, y: (x ** 2) - 2 * y,
                     lambda x, y: 1 + (y - x) ** 2,
                     lambda x, y: y / x + x / y,
                     lambda x, y: y + (1 + x) * y ** 2]
        n = int(input()) - 1
        self.f = functions[n]

    def get_data(self):
        # Method to get all the data from the user by calling other methods
        self.get_function()
        self.get_initial_value()
        self.get_interval()
        self.get_step_size()
        self.get_error_tolerance()
        return self.y0, self.a, self.b, self.h, self.eps, self.f
