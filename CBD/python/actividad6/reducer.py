#!/usr/bin/python
import sys
requestTotal = 0
oldKey = None

for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 2:
    # Something has gone wrong. Skip this line.
        continue
    thisKey, _ = data_mapped
    
    if oldKey and oldKey == thisKey:
        requestTotal += 1  
    else:
        if oldKey:
            print('%s\t%s' % (oldKey, requestTotal))
        oldKey = thisKey
        requestTotal = 0
    
    
if oldKey:
    print(oldKey, "\t", requestTotal)