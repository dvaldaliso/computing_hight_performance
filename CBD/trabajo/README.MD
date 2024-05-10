# Creamos la carpeta en hadoop
hadoop fs -mkdir movies
# copiamos la carpeta
hadoop fs -put MOVIES.csv movies
# Verificamos lo que hay dentro de la carpeta
hadoop fs -ls movies
