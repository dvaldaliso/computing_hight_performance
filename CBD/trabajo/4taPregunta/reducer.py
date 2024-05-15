#!/usr/bin/python
import sys

requestTotal = 1
oldKey = None

for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 2:
    # Something has gone wrong. Skip this line.
        continue
    thisKey, _ = data_mapped
    
    if oldKey == thisKey:
        requestTotal += 1  
    else:
        if oldKey:
            print('%s,%s' % (oldKey, requestTotal))
        oldKey = thisKey
        requestTotal = 1

if oldKey:
    print('%s,%s' % (oldKey, requestTotal))