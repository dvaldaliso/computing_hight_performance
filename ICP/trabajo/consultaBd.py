import boto3
import json

s3_client = boto3.client('s3')
sbd_client = boto3.client('sdb')
     
def handler(event, context):
    request = json.loads(event["body"]) 
    print("request: " + json.dumps(request));
    
    response = sbd_client.select(SelectExpression="select * from Imagenes where topic like '%"+request["searchString"]+"%'")
    return response
        
if __name__ == '__main__':
  consultaDB(sys.argv[1])