#!/usr/bin/python
import sys

currentResource = None
currentCount = 0
maxResource = None
maxCount = 0

for line in sys.stdin:
    resource, _ = line.strip().split('\t')
    
    if currentResource == resource:
        currentCount += 1
    else:
        if currentResource and currentCount > maxCount:
            maxResource = currentResource
            maxCount = currentCount
        currentResource = resource
        currentCount = 1

if currentResource and currentCount > maxCount:
    maxResource = currentResource
    maxCount = currentCount

print("Recurso web más popular:", maxResource, "con", maxCount, "accesos")
