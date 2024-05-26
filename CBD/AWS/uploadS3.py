import boto3

# https://boto3.amazonaws.com/v1/documentation/api/latest/guide/credentials.html#best-practices-for-configuring-credentials
# Let's use Amazon S3
s3 = boto3.resource('s3')

client = boto3.client(
    's3',
    aws_access_key_id="ACCESS_KEY",
    aws_secret_access_key="SECRET_KEY",
    aws_session_token="SESSION_TOKEN"
)
