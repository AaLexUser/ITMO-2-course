import numpy as np
import matplotlib.pyplot as plt


def variation_series(arr):
    return sorted(set(arr))


def frequency(arr):
    freq = {i: arr.count(i) for i in arr}
    return freq


def get_statistical_series(arr):
    freq = frequency(sorted(arr))
    freq_arr = [[key, value] for key, value in freq.items()]
    return freq_arr


def mean(arr):
    ss = get_statistical_series(arr)
    return sum(x * n for x, n in ss) / sum(n for _, n in ss)


def get_standard_deviation(arr):
    freq_arr = get_statistical_series(arr)
    m = mean(arr)
    variance = sum([((x - m) ** 2) * n for x, n in freq_arr]) / len(arr)
    std_dev = (variance)**(0.5)
    return std_dev


def empirical_distribution_function(arr, x):
    freq_arr = get_statistical_series(arr)
    freq = 0
    for i in range(len(freq_arr)):
        if freq_arr[i][0] >= x:
            break
        freq += freq_arr[i][1]
    return freq / len(arr)


def print_empirical_distribution(arr):
    freq_arr = get_statistical_series(arr)
    freq = 0
    print(f"x < {freq_arr[0][0]}:\tF(x) = {freq / len(arr)}")
    for i in range(len(freq_arr) - 1):
        freq += freq_arr[i][1]
        print(
            f"{freq_arr[i][0]} <= x < {freq_arr[i+1][0]}:\tF(x) = {freq / len(arr)}")
    freq += freq_arr[-1][1]
    print(f"{freq_arr[-1][0]} <= x:\tF(x) = {freq / len(arr)}")


def plot_empirical_distribution_function(arr):
    x_values = np.linspace(min(arr) - 1, max(arr) + 1, 10000)
    ecdf_values = [empirical_distribution_function(arr, x)
                   for x in x_values]
    plt.grid(which='both')
    plt.minorticks_on()
    plt.scatter(x_values, ecdf_values, marker='_', s=1)
    plt.xlabel('x', ha='right', x=1.0)
    plt.ylabel('F(x)', va='top', y=1.0)
    plt.gca().yaxis.set_label_coords(-0.03, 1.02)
    plt.gca().yaxis.get_label().set_rotation(0)
    plt.gca().xaxis.set_label_coords(1.02, 0)
    plt.title('Empirical Distribution Function')

    plt.show()


def plot_histogram(arr):
    stat_arr = get_statistical_series(arr)
    x_values = [x for x, _ in stat_arr]
    bin_widths = [x_values[i+1] - x_values[i]
                  for i in range(len(x_values) - 1)]
    bin_heights = [n/h for n, h in zip([n for _, n in stat_arr], bin_widths)]
    x_values.pop()
    plt.bar(x_values, height=bin_heights,
            width=bin_widths, edgecolor='black', align='edge', linewidth=2)
    plt.grid(which='both')
    plt.minorticks_on()
    plt.title('Histogram of Frequencies')
    plt.xlabel('x', ha='right', x=1.0)
    plt.ylabel('n/h', va='top', y=1.0)
    plt.gca().yaxis.get_label().set_rotation(0)
    plt.show()


def plot_frequency_polygon(arr):
    stat_array = get_statistical_series(arr)
    x, n = zip(*stat_array)
    plt.grid(which='both')
    plt.minorticks_on()
    plt.plot(x, n, marker='o', linestyle='-')
    plt.title('Frequency Polygon')
    plt.xlabel('x', ha='right', x=1.0)
    plt.ylabel('n', va='top', y=1.0)
    plt.gca().yaxis.get_label().set_rotation(0)
    plt.show()


data = [1.07, -1.18, 1.69, 0.48, 0.92, 1.42, -0.08, 0.65, 0.66, 0.46,
        -1.02, 1.34, 0.31, 0.11, 0.04, -1.59, -0.21, 0.55, 1.22, 0.82]
if __name__ == '__main__':
    vs = variation_series(data)
    print("========[Variation series]========================")
    print(vs)
    max_val, min_val = vs[-1], vs[0]
    print("========[Characteristics of the variation series]========")
    print('maximum value: ', round(max_val, 5))
    print('minimum value: ', round(min_val, 5))
    print('range: ', round(max_val - min_val, 5))
    print(f'expected value: {round(mean(data), 5)}')
    print(f'standard deviation: {round(get_standard_deviation(data), 5)}')
    print('========[Empirical distribution function]========')
    print_empirical_distribution(data)
    plot_empirical_distribution_function(data)
    plot_histogram(data)
    plot_frequency_polygon(data)
