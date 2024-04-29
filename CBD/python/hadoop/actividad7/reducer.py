#!/usr/bin/env python

import sys

total_accesses = 0

# Suma todos los valores asociados con la IP objetivo
for line in sys.stdin:
    _, count = line.strip().split('\t')
    total_accesses += int(count)

print('Total de accesos desde la IP 10.223.157.186:', total_accesses)
