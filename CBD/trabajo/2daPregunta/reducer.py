#!/usr/bin/python
import sys

budget_max = 0
oldKey = None
maxKey = None

for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 2:
    # Something has gone wrong. Skip this line.
        continue
    thisKey, budget = data_mapped
    
    if oldKey and oldKey != thisKey and float(budget) > float(budget_max):
        budget_max = budget
        maxKey = thisKey
    print(f"The title of movie  is{thisKey} value {budget}")
    oldKey = thisKey

if oldKey != None:
    print(f"------------------------------------------------------------------")    
    print(f"The title of movie with greater budge is{maxKey} value {budget_max}")    
else:
    print("No movie with greater budget")