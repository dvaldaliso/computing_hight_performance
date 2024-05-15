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
    data.append((x, y))
    sum_x += float(x)
    sum_y += float(y)
    n += 1

x_mean = sum_x/n
y_mean = sum_y/n
print("{0}\t{1}\t{2}\t{3} \n".format(x_mean, y_mean, x, y))