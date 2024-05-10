#!/usr/bin/python
import sys

budget_max = 0
oldKey = None

for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 2:
    # Something has gone wrong. Skip this line.
        continue
    thisKey, budget = data_mapped

    
