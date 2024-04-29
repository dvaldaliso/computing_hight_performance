#!/usr/bin/python

import sys
for line in sys.stdin:
    data = line.strip().split(" ")
    if len(data) == 10:
        addrIp, identidadCliente, identifyUser, time, utc, methodRequest, nameRequest, typeRequest, codigoEstado, byteSize = data
        print("{0}\t{1}".format(nameRequest,time))