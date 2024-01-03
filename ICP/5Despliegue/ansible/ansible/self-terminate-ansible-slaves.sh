#! /bin/bash

# Curso Online de Cloud Computing con Amazon Web Services 
# German Molto July 2014
#

USER_NAME="alucloud$ID"
#USER_NAME="gmolto"
INSTANCE_IDS=`aws ec2 describe-instances --output text --filters "Name=instance-state-code,Values=16" "Name=tag:ansible,Values=$USER_NAME" --query "Reservations[*].Instances[*].InstanceId"`
if [ -z "$INSTANCE_IDS" ]; then 
  echo "No instances to be terminated"
  exit 0
fi
echo "Will terminate instances $INSTANCE_IDS"
read -p "Are you sure? [yY] " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    aws ec2 terminate-instances --instance-ids $INSTANCE_IDS
    echo "Instances succesfully terminated"
fi

