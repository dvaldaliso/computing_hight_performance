#!/usr/bin/python
import csv
import sys

for line in sys.stdin:
    # Para el caso de leer csv tenemos que usar esta libreria porque pueden existir campos asi (" English, Espanol")
    data = next(csv.reader([line.strip()]))
    if len(data) == 15:
        budget, original_language, original_title,popularity,release_date,revenue,runtime,title,vote_average,vote_count,languages,year,genre,companies,countries = data
        try:
            if int(year)!=0: 
                print("{0}\t{1}".format(float(year), genre))
                
        except Exception as a:
            pass    