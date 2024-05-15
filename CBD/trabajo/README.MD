# Creamos la carpeta en hadoop
hadoop fs -mkdir movies
# copiamos la carpeta
hadoop fs -put MOVIES.csv movies
# Verificamos lo que hay dentro de la carpeta
hadoop fs -ls movies

# test
cat datasets/MOVIES.csv | head -n 30 | script/mapper.py | sort 1,1
cat datasets/MOVIES.csv | head -n 30 | script/mapper.py | sort 1,1 | script/reducer.py

David
¿Existe alguna correlación entre el presupuesto de una película y su popularidad?
¿Cuál es la película con el mayor presupuesto en el dataset?
¿Cuál es la película más popular según la medida de popularidad?
¿Cuántas películas se lanzaron cada año?


Gary
¿Cuál es el año con mayor cantidad de películas en el dataset?
¿Cuál es el género más frecuente en las películas del dataset?
¿Cuál es la distribución de géneros más común en las películas producidas por diferentes compañías?

Encinas
¿Cuáles son las compañías productoras que más películas han lanzado en un año determinado y cuál es su distribución de género?
¿Cuál es el idioma original más común en las películas del dataset?
¿Cuál es la película mejor calificada (voto promedio) en el dataset?

# test con Cat
cat datasets/MOVIES.csv | head -n 100 | script/mapper_cuarta.py | sort -k 1,1 | script/reducer_cuarta.py | head -n 100
cat datasets/MOVIES.csv | head -n 10 | script/mapper.py sort -k 1,1 | script/reducer.py | head -n 20
# Ejecucion con hadoop
hs ./mapper.py ./reducer.py movies purchases/output
hadoop fs -text purchases/output/part-00000