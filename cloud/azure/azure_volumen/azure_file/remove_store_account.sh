

export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export SHARE_ACOUNT="sharepaneladvisorsy"



az storage account delete --name $STORE_ACOUNT --resource-group $MY_RESOURCE_GROUP_NAME
az storage account list --output table

