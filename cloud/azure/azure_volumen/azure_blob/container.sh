export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export CONTAINER="mysql-backups"

az storage container create  \
  --name $CONTAINER \
  --account-name $STORE_ACOUNT



# kubectl create secret generic mysql-backup-secret \
#   --from-literal=config="{
#   \"azureStorageAccount\":\"storepaneladvisorsy\",
#   \"azureStorageSasToken\":\"$AZURE_STORAGE_SAS_TOKEN\"}"\
#   --namespace=data