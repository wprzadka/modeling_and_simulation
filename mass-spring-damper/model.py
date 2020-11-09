from sympy import inverse_laplace_transform, diff
from sympy.abc import s, t
import matplotlib
import matplotlib.pyplot as plt

matplotlib.use('Qt5Agg')


def euler_method(derivatives: list, step: float):
    for idx in reversed(range(len(derivatives) - 1)):
        derivatives[idx] += derivatives[idx + 1] * step


def transfer_function(mass: float, damping: float, elasticity: float):
    position_func = inverse_laplace_transform(1/(mass * s**2 + damping * s + elasticity), s, t)
    velocity_func = diff(position_func)
    accelerate_func = diff(velocity_func)
    return position_func, velocity_func, accelerate_func


# if __name__ == '__main__':
#     print(transfer_function(1, 0.3, 1))

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

    func = transfer_function(mass, damping, elasticity)
    for f in func:
        print(f)

    time = 0
    while time < total_time:
        # pos_derivatives[2] = (force_func(time) - damping * pos_derivatives[1] - elasticity * pos_derivatives[0]) / mass
        # euler_method(pos_derivatives, step)
        #
        force_series.append(force_func(time))
        for idx, curr_series in enumerate(series.values()):
            curr_series.append(func[idx].subs([(t, time)]))
        #     curr_series.append(pos_derivatives[idx])

        time_series.append(time)
        time += step

    for curr_series in series.values():
        curr_series[0] = 0

    fig, axis = plt.subplots(4, 1)

    for idx, (series_name, series_values) in enumerate(
            zip([*series.keys(), "force"], [*series.values(), force_series])):
        axis[idx].plot(time_series, series_values)
        axis[idx].set_ylabel(series_name)
        axis[idx].set_xlabel("time")
        axis[idx].grid(True)

    # plt.savefig("plot.png", format="png")
    plt.show()
