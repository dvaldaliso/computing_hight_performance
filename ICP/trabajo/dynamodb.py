import boto3
import json
import asyncio
from boto3.dynamodb.conditions import Key, Attr
# define the DynamoDB table that Lambda will connect to
tableName = "alucloud50-project"

# create the DynamoDB resource
dynamo = boto3.resource('dynamodb').Table(tableName)

print('Loading function')

def handler(event, context):
        
    # define the functions used to perform the CRUD operations
    def ddb_create(x):
        try:
            dynamo.put_item(**x)
            return "creado"
        except ClientError as e:
            return "error al insertar"

    def ddb_read(x):
        print(x)
        return dynamo.get_item(**x)
     
    def ddb_query(x):
        return dynamo.query(
        KeyConditionExpression='years = :value',
        ExpressionAttributeValues={
            ':value': {'S': '245'}
        }
        )
    def ddb_scan(x):
        return dynamo.scan()    
     
    def ddb_update(x):
        try:
            dynamo.update_item(**x)
            return  "actualizado"
        except ClientError as e:
            return "error al actualizar"
        
        
    def ddb_delete(x):
        try:
            dynamo.delete_item(**x)
            return "eliminado"
        except ClientError as e:
            return "error al eliminar"

    def echo(x):
        return x

    operation = event['operation']

    operations = {
        'create': ddb_create,
        'read': ddb_read,
        'query': ddb_query,
        'scan': ddb_scan,
        'update': ddb_update,
        'delete': ddb_delete,
        'echo': echo,
    }

    if operation in operations:
        return operations[operation](event.get('payload'))
    else:
        raise ValueError('Unrecognized operation "{}"'.format(operation))
