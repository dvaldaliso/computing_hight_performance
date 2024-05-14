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
    x_mean, y_mean, x, y = data_mapped
    print(x_mean, y_mean, x, y)
