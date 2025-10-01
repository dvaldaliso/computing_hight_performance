export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export CONTAINER="mysql-backups"

az storage account management-policy create \
    --account-name $STORE_ACOUNT \
    --resource-group $MY_RESOURCE_GROUP_NAME \
    --policy @"./K8-advisorsy/azure/azure_volumen/azure_blob/rules/policy.json"