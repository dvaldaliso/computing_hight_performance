aws lambda create-function \
--region us-east-1 \
--function-name lambda-grayify-$ID \
--zip-file fileb://$HOME/function.zip \
--role arn:aws:iam::974349055189:role/cursocloudaws-lambda-serverless-role \
--handler index.handler --runtime python3.9 \
--timeout 10 \
--memory-size 128 \
--layers "arn:aws:lambda:us-east-1:770693421928:layer:Klayers-p39-pillow:1"
