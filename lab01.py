# import scipy.integrate as integrate
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('Qt5Agg')


if __name__ == '__main__':

    elasticity = 1
    damping = 0.3
    mass = 1  # kg
    # force_func = lambda t: 1 if t % 7 > 2.5 else 0  # N
    # force_func = lambda t: t % 7  # N
    force_func = lambda t: 1  # N

    total_time = 40
    step = 0.1
    pos_derivatives = [0, 0, 0]

    series = {"position": [], "velocity": [], "accelerate": []}
    time_series = []
    force_series = []

    time = 0
    while time < total_time:
        pos_derivatives[2] = (force_func(time) - damping * pos_derivatives[1] - elasticity * pos_derivatives[0]) / mass
        for i in (1, 0):
            pos_derivatives[i] += pos_derivatives[i + 1] * step

        """
        pos_derivatives[1] = (force_func(time) * time
                              - damping * pos_derivatives[0]
                              - elasticity * pos_derivatives[0] * time
                              ) / mass
                              
        pos_derivatives[0] = (force_func(time) * (time ** 2) / 2
                              - damping * pos_derivatives[0] * time
                              - elasticity * pos_derivatives[0] * (time ** 2) / 2
                              ) / mass
        """
        print(time % 7)
        force_series.append(force_func(time))

        for idx, curr_series in enumerate(series.values()):
            curr_series.append(pos_derivatives[idx])
        time_series.append(time)
        time += step

    # time_series = [i for i in range(total_time, 0, step)]
    fig, axis = plt.subplots(4, 1)

    for idx, (series_name, series_values) in enumerate(zip([*series.keys(), "force"], [*series.values(), force_series])):
        axis[idx].plot(time_series, series_values)
        axis[idx].set_ylabel(series_name)
        axis[idx].set_xlabel("time")
        axis[idx].grid(True)

    # plt.savefig("plot.pdf", format="pdf")
    for name, tab in series.items():
        print(name, tab)
    print("time", time_series)
    plt.show()
