
# Obtener el ARN del balanceador de carga
LOAD_BALANCER_ARN=$(aws elbv2 describe-load-balancers --names wp-50-lb | jq -r ".LoadBalancers[].LoadBalancerArn")

TARGET_GROUP_ARN=$(aws elbv2 describe-target-groups --name wp-$ID-lb-tg --output json | jq -r ".TargetGroups[].TargetGroupArn")

# Crear un escucha utilizando el ARN del balanceador de carga
#aws elbv2 create-listener \
#  --load-balancer-arn $LOAD_BALANCER_ARN \
#  --protocol HTTP \
#  --port 80 \
#  --default-actions Type=forward,TargetGroupArn=$TARGET_GROUP_ARN


#WP_IMAGE_ID=$(aws ec2 describe-images --owners self --filters Name=name,Values=AMIWordPress$ID --output json | jq -r ".Images[].ImageId")
#SG_ID=$(aws ec2 describe-security-groups --filters Name=group-name,Values=gs-aws-$ID --output json | jq -r ".SecurityGroups[].GroupId")

#aws ec2 create-launch-template --launch-template-name wp-launch-template-$ID --version-description version1  --launch-template-data '{"ImageId":"'$WP_IMAGE_ID'","InstanceType":"t3.micro", "KeyName":"'alucloud$ID-keypair'", "NetworkInterfaces":[{"DeviceIndex":0,"AssociatePublicIpAddress":true, "Groups":["'$SG_ID'"],"DeleteOnTermination":true}]}'


#aws ec2 describe-launch-templates --launch-template-names wp-launch-template-$ID

#aws autoscaling create-auto-scaling-group --auto-scaling-group-name as-wp-group-$ID --launch-template "LaunchTemplateName=wp-launch-template-$ID" --min-size 1 --max-size 2 --default-cooldown 120 --target-group-arns $TARGET_GROUP_ARN --vpc-zone-identifier "subnet-c0c33fef,subnet-432a9408"

#SO_POLICY_ARN=$(aws autoscaling put-scaling-policy --policy-name pol-wp-50-scale-OUT-on-CPU --auto-scaling-group-name as-wp-group-50 --adjustment-type PercentChangeInCapacity --scaling-adjustment 25 --cooldown 120)

#aws cloudwatch put-metric-alarm --alarm-name alucloud-alarm-wp-50-scale-OUT-on-CPU --alarm-actions $SO_POLICY_ARN --metric-name CPUUtilization  --unit Percent --namespace AWS/EC2 --statistic Average --dimensions="Name=AutoScalingGroupName,Value=as-wp-group-50"  --period 60 --evaluation-periods 2 --threshold 80 --comparison-operator GreaterThanThreshold 

#SI_POLICY_ARN=$(aws autoscaling put-scaling-policy --policy-name pol-wp-$ID-scale-IN-on-CPU --auto-scaling-group-name as-wp-group-$ID --adjustment-type PercentChangeInCapacity --scaling-adjustment -25 --cooldown 120)

#aws cloudwatch put-metric-alarm --alarm-name alucloud-alarm-wp-$ID-scale-IN-on-CPU --alarm-actions $SI_POLICY_ARN --metric-name CPUUtilization --unit Percent --namespace AWS/EC2 --statistic Average --dimensions="Name=AutoScalingGroupName,Value=as-wp-group-$ID" --period 60 --evaluation-periods 2 --threshold 20 --comparison-operator LessThanThreshold

aws autoscaling update-auto-scaling-group --auto-scaling-group-name as-wp-group-$ID --min-size 0 --max-size 0
#aws autoscaling delete-auto-scaling-group --auto-scaling-group-name as-wp-group-$ID
#aws ec2 delete-launch-template --launch-template-name wp-launch-template-$ID
#aws elbv2 delete-load-balancer --load-balancer-arn $LOAD_BALANCER_ARN
