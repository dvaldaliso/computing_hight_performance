# Ejecucion conteo de palabra
## Compilación
# javac -classpath `hadoop classpath` -d wordcount/classes wordcount/src/WordCount.java

## empaquetar en un jar
# jar -cvf wordcount/wordcount.jar -C wordcount/classes .

## ejecucion con haaadop
# hdoop jar wordcount/wordcount.jar cursocloudaws.WordCount /datasets/gutenberg/gutenberg.txt gutenberg/output1