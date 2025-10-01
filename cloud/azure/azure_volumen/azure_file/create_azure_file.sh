

export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export SHARE_ACOUNT="backups"



az storage share create \
  --name $SHARE_ACOUNT \
  --account-name $STORE_ACOUNT 



