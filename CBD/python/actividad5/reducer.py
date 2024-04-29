#!/usr/bin/python
import sys
paymentMax = 0
oldKey = None
# Loop around the data
#Obtener el valor de la venta de mayor importe para cada tienda.

for line in sys.stdin:
    data_mapped = line.strip().split("\t")
    if len(data_mapped) != 2:
    # Something has gone wrong. Skip this line.
        continue
    thisKey, thisPayment = data_mapped

    #number = float(thisPayment)
        
    if thisKey == oldKey:
        paymentMax = max(paymentMax, float(thisPayment))
    else:
        if oldKey:
            print('%s\t%s' % (oldKey, paymentMax))
        oldKey = thisKey
        paymentMax = float(thisPayment)

if oldKey:
    print('%s\t%s' % (oldKey, paymentMax))