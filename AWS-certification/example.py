import boto3


#CONFIGURAR ZONA 
#nano ~/.aws/config
#nano ~/.aws/credentials
def list_ec2_instance():
    ec2 = boto3.client('ec2')

    response = ec2.describe_instances()

    for reservation in response['Reservations']:
        for instance in reservation['Instances']:
            print(f"Instance ID: {instance['InstanceId']}, ")
            print(f"Instance type: {instance['InstanceType']}")
            print(f"State: {instance['State']['Name']}")
            print("---------------------------")

def get_ima_user():
    iam = boto3.client('iam')
    response = iam.get_user()
    return response['User']['UserName']
if __name__ == "__main__":
    list_ec2_instance()