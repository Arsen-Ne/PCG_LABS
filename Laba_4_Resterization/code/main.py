import matplotlib.pyplot as plt
import math
from matplotlib.widgets import Button
from matplotlib.widgets import Slider


def draw_dda_line(x1, y1, x2, y2, color="r."):
    ax = plt.subplot(2, 4, 1)
    plt.title("ЦДА", fontsize=10)
    ax.plot(x1, y1, color)
    ax.grid()
    ax.set_xlabel("x (point)")
    ax.set_ylabel("y (point)")
    plt.plot(x1, y1, ':')

    dx = x2 - x1
    dy = y2 - y1

    # calculate steps required for generating pixels
    steps = abs(dx) if abs(dx) > abs(dy) else abs(dy)

    # calculate increment in x & y for each step
    if steps != 0:
        x_inc = float(dx / steps)
        y_inc = float(dy / steps)
    else:
        x_inc, y_inc = 0,1

    for i in range(0, int(steps + 1)):
        # draw pixels
        plt.plot(x1, y1, color)
        x1 += x_inc
        y1 += y_inc
    plt.axis('square')


def draw_steps_line(x, k, b, steps, color="r."):
    ax = plt.subplot(2, 4, 2)
    ax.grid()
    plt.title("Пошаговый", fontsize=10)
    ax.set_xlabel("x (point)")
    ax.set_ylabel("y (point)")

    y = float()
    for i in range(0, int(steps + 1)):
        # draw pixels
        y = x * k + b
        y = round(y)
        plt.plot(int(x), y, color)
        x += 1
    plt.axis('square')


def draw_b_circle(x1, y1, x2, y2, color="r."):
    ax = plt.subplot(2, 4, 3)
    ax.grid()
    plt.title("Брезенхем окружность", fontsize=10)
    ax.set_xlabel("x (point)")
    ax.set_ylabel("y (point)")

    px = []
    py = []
    r = math.sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))
    disp_x = x1
    disp_y = y1
    x = 0
    y = r
    delta = (2 - 2 * r)
    while y >= 0:
        px.append(disp_x + x)
        py.append(disp_y + y)
        px.append(disp_x + x)
        py.append(disp_y - y)
        px.append(disp_x - x)
        py.append(disp_y + y)
        px.append(disp_x - x)
        py.append(disp_y - y)

        error = 2 * (delta + y) - 1
        if (delta < 0) and (error <= 0):
            x += 1
            delta = delta + (2 * x + 1)
            continue
        if (delta > 0) and (error > 0):
            y -= 1
            delta = delta - (1 + 2 * y)
            continue
        x += 1
        delta = delta + (2 * (x - y))
        y -= 1
    plt.plot(px, py, color)
    plt.axis('square')


def draw_b_line(x1, y1, x2, y2, color="r."):
    ax = plt.subplot(2, 4, 4)
    plt.title("Брезенхем линия", fontsize=10)
    ax.set_xlabel("x (point)")
    ax.set_ylabel("y (point)")
    plt.plot(x2, y2, color)
    ax.grid()

    # start algor Brezenhem line
    dx = x2 - x1
    dy = y2 - y1

    sign_x = 1 if dx > 0 else -1 if dx < 0 else 0
    sign_y = 1 if dy > 0 else -1 if dy < 0 else 0

    if dx < 0:
        dx = -dx
    if dy < 0:
        dy = -dy

    if dx > dy:
        pdx, pdy = sign_x, 0
        es, el = dy, dx
    else:
        pdx, pdy = 0, sign_y
        es, el = dx, dy

    x, y = x1, y1

    error, t = el / 2, 0

    plt.plot(x, y, color)

    while t < el:
        error -= es
        if error < 0:
            error += el
            x += sign_x
            y += sign_y
        else:
            x += pdx
            y += pdy
        t += 1
        plt.plot(x, y, color)
    plt.axis('square')


def submit_dda_line(x, y, x_end, y_end):
    def clicked(event):
        ax2 = plt.subplot(2, 4, 1)
        ax2.cla()
        draw_dda_line(int(x.val), int(y.val), int(x_end.val), int(y_end.val))
        plt.draw()

    return clicked


def submit_steps_line(x, k, b, steps):
    def clicked(event):
        ax2 = plt.subplot(2, 4, 2)
        ax2.cla()
        draw_steps_line(int(x.val), float(k.val), int(b.val), int(steps.val))
        plt.axis('square')
        plt.draw()

    return clicked


def submit_b_circle(x, y, x_end, y_end):
    def clicked(event):
        ax2 = plt.subplot(2, 4, 3)
        ax2.cla()
        draw_b_circle(int(x.val), int(y.val), int(x_end.val), int(y_end.val))
        plt.draw()

    return clicked


def submit_b_line(x, y, x_end, y_end):
    def clicked(event):
        ax2 = plt.subplot(2, 4, 4)
        ax2.cla()
        draw_b_line(int(x.val), int(y.val), int(x_end.val), int(y_end.val))
        plt.draw()

    return clicked


def main():
    plt.figure("Базовые растровые алгоритмы", figsize=(16, 8), layout="constrained")
    plt.subplots_adjust(left=0.1, right=0.9)

    # input to DDA
    ax = plt.axes([0.05, 0.35, 0.15, 0.04])
    dda_box_x1 = Slider(ax, label='x1', valinit=100, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.05, 0.3, 0.15, 0.04])
    dda_box_y1 = Slider(ax, label='y1', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.05, 0.25, 0.15, 0.04])
    dda_box_x2 = Slider(ax, label='x2', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.05, 0.2, 0.15, 0.04])
    dda_box_y2 = Slider(ax, label='y2', valinit=100, valmin=0, valmax=500, valstep=1)

    ax = plt.axes([0.1, 0.1, 0.1, 0.04])
    button_dda_line = Button(ax, 'Submit')
    button_dda_line.on_clicked(submit_dda_line(dda_box_x1, dda_box_y1, dda_box_x2, dda_box_y2))

    # input to Steps
    ax = plt.axes([0.3, 0.35, 0.15, 0.04])
    steps_box_x = Slider(ax, label='x', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.3, 0.30, 0.15, 0.04])
    steps_box_k = Slider(ax, label='k', valinit=-1, valmin=-10, valmax=10, valstep=0.1)
    ax = plt.axes([0.3, 0.25, 0.15, 0.04])
    steps_box_b = Slider(ax, label='b', valinit=100, valmin=-250, valmax=250, valstep=1)
    ax = plt.axes([0.3, 0.2, 0.15, 0.04])
    steps_box_steps = Slider(ax, label='Steps', valinit=100, valmin=0, valmax=500, valstep=1)

    ax = plt.axes([0.35, 0.1, 0.1, 0.04])
    button_steps_line = Button(ax, 'Submit')
    button_steps_line.on_clicked(submit_steps_line(steps_box_x, steps_box_k, steps_box_b, steps_box_steps))

    # input to Brezenhem circle
    ax = plt.axes([0.55, 0.35, 0.15, 0.04])
    circle_box_x = Slider(ax, label='x1', valinit=100, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.55, 0.30, 0.15, 0.04])
    circle_box_y = Slider(ax, label='y1', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.55, 0.25, 0.15, 0.04])
    circle_box_x_end = Slider(ax, label='x2', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.55, 0.2, 0.15, 0.04])
    circle_box_y_end = Slider(ax, label='y2', valinit=100, valmin=0, valmax=500, valstep=1)

    ax = plt.axes([0.6, 0.1, 0.1, 0.04])
    button_b_circle = Button(ax, 'Submit')
    button_b_circle.on_clicked(submit_b_circle(circle_box_x, circle_box_y, circle_box_x_end, circle_box_y_end))

    # input to Brezenhem line
    ax = plt.axes([0.8, 0.35, 0.15, 0.04])
    line_box_x1 = Slider(ax, label='x1', valinit=100, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.8, 0.30, 0.15, 0.04])
    line_box_y1 = Slider(ax, label='y1', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.8, 0.25, 0.15, 0.04])
    line_box_x2 = Slider(ax, label='x2', valinit=0, valmin=0, valmax=500, valstep=1)
    ax = plt.axes([0.8, 0.2, 0.15, 0.04])
    line_box_y2 = Slider(ax, label='y2', valinit=100, valmin=0, valmax=500, valstep=1)

    ax = plt.axes([0.85, 0.1, 0.1, 0.04])
    button_b_line = Button(ax, 'Submit')
    button_b_line.on_clicked(submit_b_line(line_box_x1, line_box_y1, line_box_x2, line_box_y2))

    # DDA line
    draw_dda_line(int(dda_box_x1.val), int(dda_box_y1.val), int(dda_box_x2.val), int(dda_box_y2.val))
    # Steps line
    draw_steps_line(int(steps_box_x.val), int(steps_box_k.val), int(steps_box_b.val), int(steps_box_steps.val))
    # Brezenhem circle
    draw_b_circle(int(circle_box_x.val), int(circle_box_y.val), int(circle_box_x_end.val),
                  int(circle_box_y_end.val))
    # Brezenhem line
    draw_b_line(int(line_box_x1.val), int(line_box_y1.val), int(line_box_x2.val), int(line_box_y2.val))

    plt.show()


if __name__ == '__main__':
    main()
