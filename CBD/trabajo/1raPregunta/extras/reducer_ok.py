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
x_mean_square = x_mean**2
y_mean_square = y_mean**2
covarianza = 0
desviacionx = 0
desviaciony = 0

for line in data:
    x, y = map(float, line)
    x_xmean = (x - x_mean)
    y_ymean = (y - y_mean)
    covarianza += x_xmean * (y_ymean)
    desviacionx += (x_xmean)**2
    desviaciony += (y_ymean)**2
    
desviacionxy= (desviacionx**0.5) * (desviaciony**0.5)
correlation = covarianza / desviacionxy

print(f"correalcion {correlation}" )