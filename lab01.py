# import scipy.integrate as integrate
import matplotlib
import matplotlib.pyplot as plt


matplotlib.use('Qt5Agg')


if __name__ == '__main__':

    elasticity = 5
    damping = 10
    mass = 200  # kg
    force = 100  # N

    total_time = 260
    step = 0.1
    pos_derivatives = [0, 0, 0]

    series = {"position": [], "velocity": [], "accelerate": []}
    time_series = []

    time = 0
    while time < total_time:
        pos_derivatives[2] = (force - damping * pos_derivatives[1] - elasticity * pos_derivatives[0]) / mass
        for i in (1, 0):
            pos_derivatives[i] += pos_derivatives[i + 1] * step

        for idx, curr_series in enumerate(series.values()):
            curr_series.append(pos_derivatives[idx])
        time_series.append(time)
        time += step

    # time_series = [i for i in range(total_time, 0, step)]
    fig, axis = plt.subplots(3, 1)

    for idx, (series_name, series_values) in enumerate(zip(series.keys(), series.values())):
        axis[idx].plot(time_series, series_values)
        axis[idx].set_ylabel(series_name)
        axis[idx].set_xlabel("time")
        axis[idx].grid(True)

    plt.savefig("plot.pdf", format="pdf")
    # plt.show()
