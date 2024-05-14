#!/usr/bin/python
import csv
import sys

for line in sys.stdin:
    # Para el caso de leer csv tenemos que usar esta libreria porque pueden existir campos asi (" English, Espanol")
    data = next(csv.reader([line.strip()]))
    if len(data) == 15:
        budget, original_language, original_title,popularity,release_date,revenue,runtime,title,vote_average,vote_count,languages,year,genre,companies,countries = data
        try:
            x=float(popularity)
            y=float(budget)
            print("{0}\t{1}\t{2}\t{3}\t{4} \n".format(x, y, x*y, x**2, y**2))
        except Exception as a:
            pass    