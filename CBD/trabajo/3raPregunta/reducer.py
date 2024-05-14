#!/usr/bin/python
import sys

popular_max = 0
oldKey = None
maxKey = None

for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 2:
    # Something has gone wrong. Skip this line.
        continue
    thisKey, popular = data_mapped
    
    if oldKey and oldKey != thisKey and float(popular) > float(popular_max):
        popular_max = popular
        maxKey = thisKey
    oldKey = thisKey
if oldKey != None:
    print(f"The title of movie with greater budge is{maxKey} value {popular_max}")    
else:
    print("No movie with greater popular")