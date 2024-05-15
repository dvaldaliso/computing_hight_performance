#!/usr/bin/python
import sys

import numpy as np
import scipy.stats as stats

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
t = correlation * np.sqrt((n - 2) / (1 - correlation**2))
# Calcular el valor p 
p_value = 2 * (1 - stats.t.cdf(abs(t), df=n-2))



print(f"correalcion {correlation}" )

print(f'Estadístico t: {t}')
print(f'Valor p: {p_value}')