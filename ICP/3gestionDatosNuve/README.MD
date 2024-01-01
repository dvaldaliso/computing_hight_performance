# Dynamobd
## python3 
## Usar la query dentro de queries
## aws dynamodb query --table-name alucloud50-Movies --key-condition-expression "#y = :theYear and begins_with(title,:theTitle)" --expression-attribute-values file:///opt/cursoaws/dynamodb/movies/queries/movies-by-year-that-start-with.json --projection-expression "#y,title" --expression-attribute-names '{"#y":"year"}' --output json

## leer informacion de una tabla
### aws dynamodb describe-table --table-name alucloud50-ctt --output json