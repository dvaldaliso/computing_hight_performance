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
def remove_instance(instance_id):
    ec2 = boto3.client('ec2')
    try:
        response = ec2.terminate_instances(InstanceIds=[instance_id])
        print(f"Instance {instance_id} terminated successfully.")
    except Exception as e:
        print(f"Error terminating instance {instance_id}: {e}")
def get_ima_user():
    iam = boto3.client('iam')
    response = iam.get_user()
    return response['User']['UserName']
if __name__ == "__main__":
    list_ec2_instance()
    #remove_instance('i-0af1af45ac94bfe0e')  # Replace with your instance