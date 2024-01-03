#!/bin/bash
# 
# Curso Online de Cloud Computing con Amazon Web Services 
# German Molto - @gmolto - October 2020

TOTAL_NODES=2
KEYPAIR="alucloud$ID-keypair"
#SECURITY_GROUP="gs-aws-$ID"
SECURITY_GROUP=sg-aa1f0fd8
USER_NAME="alucloud$ID"
#USER_NAME="gmolto"
PRIVATE_KEY_FILE="$HOME/alucloud$ID-priv.pem"
#PRIVATE_KEY_FILE="/Users/gmolto/.ec2/alucloud00-priv.pem"
PUBLIC_KEY_FILE="$HOME/.ssh/id_rsa.pub"

ANSIBLE_LOCAL_INVENTORY_FILE="$HOME/.ansible_hosts_local"

rm -f $ANSIBLE_LOCAL_INVENTORY_FILE
echo "[local]" >> $ANSIBLE_LOCAL_INVENTORY_FILE
echo "localhost ansible_python_interpreter=/usr/bin/python3" >> $ANSIBLE_LOCAL_INVENTORY_FILE
export ANSIBLE_HOST_KEY_CHECKING=False
ansible-playbook /opt/cursoaws/ansible/self-submit-ansible-slaves.yml -i $ANSIBLE_LOCAL_INVENTORY_FILE --extra-vars "total=$TOTAL_NODES keypair=$KEYPAIR security_group=$SECURITY_GROUP user_name=$USER_NAME"
ansible-playbook -i /opt/cursoaws/ansible/inventory_aws_ec2.yml --private-key $PRIVATE_KEY_FILE /opt/cursoaws/ansible/self-configure-ansible-slaves.yml --extra-vars="target=tag_ansible_$USER_NAME user_name=$USER_NAME pub_key_file=$PUBLIC_KEY_FILE" 

