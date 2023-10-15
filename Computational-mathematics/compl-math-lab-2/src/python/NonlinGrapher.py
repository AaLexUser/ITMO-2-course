import matplotlib.pyplot as plt
import numpy as np
import sys
import os


def choose_functions_and_plot(inpt):
    # Define the options for f(x, y) and g(x, y)
    option = str(inpt)
    options = {
        '1': (lambda x, y: x ** 2 + y ** 2 - 4, lambda x, y: -3*x**2 + y),
        '2': (lambda x, y: 0.1*x**2+x+0.2*y**2-0.3, lambda x, y: 0.2*x**2+y+0.1*x*y-0.7),
        '3': (lambda x, y: np.abs(x) + np.abs(y) - 4, lambda x, y: np.abs(x ** 2 - y ** 2) - 1)
    }

    # Get the chosen functions
    if option in options:
        f, g = options[option]
    else:
        print('Invalid option')
        return

    # Call the plot_functions function with the chosen functions
    plot_functions(f, g, f'Plot of f(x, y) and g(x, y) - Option {option}')


def plot_functions(f, g, title):
    # Create values for x and y
    x = np.linspace(-5, 5, 100)
    y = np.linspace(-5, 5, 100)

    # Create a grid of (x, y) values
    X, Y = np.meshgrid(x, y)

    # Calculate the corresponding z values for each (x, y) pair
    Z1 = f(X, Y)
    Z2 = g(X, Y)

    # Plot the functions with both major and minor grid
    plt.contour(X, Y, Z1, levels=[0], colors='blue')
    plt.contour(X, Y, Z2, levels=[0], colors='red')
    plt.grid(True, which='both', color='gray', linestyle='--', linewidth=0.5, alpha=0.5)
    plt.minorticks_on()
    plt.grid(which='minor', color='gray', linestyle=':', linewidth=0.5, alpha=0.2)

    # Add labels and title
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title(title)

    # Set the aspect ratio to equal
    plt.gca().set_aspect('equal')

    # Set the figure size to be square
    fig = plt.gcf()
    fig.set_size_inches(6, 6)

    # Add a legend
    plt.legend(['f(x, y) = 25', 'g(x, y) = 25'])

    plt.savefig('plot.png')
    # Display the plot
    plt.show()


def func1():
    print(sys.path)


if __name__ == '__main__':
    choose_functions_and_plot(1)
