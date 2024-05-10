# Creamos la carpeta en hadoop
hadoop fs -mkdir movies
# copiamos la carpeta
hadoop fs -put MOVIES.csv movies
# Verificamos lo que hay dentro de la carpeta
hadoop fs -ls movies

# test
cat datasets/MOVIES.csv | head -n 30 | script/mapper.py sort 1,1
cat datasets/MOVIES.csv | head -n 30 | script/mapper.py sort 1,1 | script/reducer.py