#!/usr/bin/python
import sys

sum_xy = 0
sum_x = 0
sum_y = 0
sum_x_squared = 0
sum_y_squared = 0
n = 0
data = []
for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 5:
    # Something has gone wrong. Skip this line.
        continue
    x, y, xy, xx, yy = data_mapped
    sum_x += float(x)
    sum_y += float(y)
    sum_xy += float(xy)
    sum_x_squared += float(xx)
    sum_y_squared += float(yy)
    n += 1


correlation = (n * sum_xy - sum_x * sum_y) / ((n * sum_x_squared - sum_x ** 2) * (n * sum_y_squared - sum_y ** 2)) ** 0.5

print(f"correalcion {correlation}" )