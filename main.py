from math import pi, sin, cos
from matplotlib import pyplot

"""Generating an approximated ECG signal using Fourier series. 60 beats per minute"""
# My base functions
# P-Peak:
# -0.000125*((x-300)**2)+0.2

# R-peak:
# -0.0000156((x-420)**4)+2.5

# T-Peak:
# -0.0001*((x-690)**2)+0.6



def fourier_fR(cnt_R, x):
    ret = 0
    for n in range(1, cnt_R):
        ret += (2 / 1000 * ((2 * ((pi ** 4 * n ** 4 + 4680000 * pi ** 2 * n ** 2 - 5850000000) * sin(
            (22 * pi * n) / 25) - 62400 * pi * n * (pi ** 2 * n ** 2 - 3750) * cos((22 * pi * n) / 25) - (
                                          pi ** 4 * n ** 4 + 4680000 * pi ** 2 * n ** 2 - 5850000000) * sin(
            (4 * pi * n) / 5) - 62400 * pi * n * (pi ** 2 * n ** 2 - 3750) * cos((4 * pi * n) / 5))) / (
                                    pi ** 5 * n ** 5)) * cos((2 * pi * n * x) / 1000) +
                (2 / 1000 * (-(2 * (62400 * pi * n * (pi ** 2 * n ** 2 - 3750) * sin((22 * pi * n) / 25) + (
                        pi ** 4 * n ** 4 + 4680000 * pi ** 2 * n ** 2 - 5850000000) * cos(
                    (22 * pi * n) / 25) + 62400 * pi * n * (pi ** 2 * n ** 2 - 3750) * sin((4 * pi * n) / 5) - (
                                            pi ** 4 * n ** 4 + 4680000 * pi ** 2 * n ** 2 - 5850000000) * cos(
                    (4 * pi * n) / 5))) / (pi ** 5 * n ** 5)) * sin((2 * pi * n * x) / 1000)))
    return (2 / 1000) * 0.16 + ret


def fourier_fP(cnt_P, x):
    ret = 0
    for n in range(1, cnt_P):
        ret += (2 / 1000 * ((1250 * (25 * sin((17 * pi * n) / 25) - 2 * pi * n * (
                cos((17 * pi * n) / 25) + cos((13 * pi * n) / 25)) - 25 * sin((13 * pi * n) / 25))) / (
                                    pi ** 3 * n ** 3)) * cos((2 * pi * n * x) / 1000) +
                (2 / 1000 * (-(1250 * (2 * pi * n * (sin((17 * pi * n) / 25) + sin((13 * pi * n) / 25)) + 25 * cos(
                    (17 * pi * n) / 25) - 25 * cos((13 * pi * n) / 25))) / (pi ** 3 * n ** 3)) * sin(
                    (2 * pi * n * x) / 1000)))
    return (2 / 1000) * (32 / 3) + ret


def fourier_fT(cnt_T, x):
    ret = 0
    for n in range(1, cnt_T):
        ret += (2 / 1000 * (((224 * pi ** 2 * n ** 2 + 500000) * sin((767 * pi * n) / 500) - 76000 * pi * n * cos(
            (767 * pi * n) / 500) + (241 * pi ** 2 * n ** 2 - 500000) * sin(
            (153 * pi * n) / 125) - 79000 * pi * n * cos((153 * pi * n) / 125)) / (20 * pi ** 3 * n ** 3)) * cos(
            (2 * pi * n * x) / 1000) +
                (2 / 1000 * (-(76000 * pi * n * sin((767 * pi * n) / 500) + (224 * pi ** 2 * n ** 2 + 500000) * cos(
                    (767 * pi * n) / 500) + 79000 * pi * n * sin((153 * pi * n) / 125) + (
                                       241 * pi ** 2 * n ** 2 - 500000) * cos((153 * pi * n) / 125)) / (
                                     20 * pi ** 3 * n ** 3)) * sin(
                    (2 * pi * n * x) / 1000)))
    return (2 / 1000) * (61.9328) + ret


fourierfR = []
fourier_n_R = 30
fourier_n_P = 30
fourier_n_T = 30

x = 0
up = 2000
while x <= up:

    fourR = fourier_fR(fourier_n_R, x)
    fourP = fourier_fP(fourier_n_P, x)
    fourT = fourier_fT(fourier_n_T, x)

    four = fourR + fourP + fourT
    # if four < 0:
    #     four = 0
    dot = [x, four]
    fourierfR.append(four)
    x += 1
    if x == up:
        pyplot.plot(fourierfR)
        pyplot.show()
        fourierfR.clear()
        x = 0
