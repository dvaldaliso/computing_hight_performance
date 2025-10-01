export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export CONTAINER="mysql-backups"

#az storage container create --name $CONTAINER --account-name $STORE_ACOUNT
# az storage blob delete \
#   --account-name $STORE_ACOUNT \
#   --container-name $CONTAINER \
#   --name <blob-name> \
#   --sas-token <sas-token>
az storage container delete \
  --account-name $STORE_ACOUNT \
  --name $CONTAINER


# kubectl create secret generic azure-storage-secret \
#   --from-literal=AZURE_STORAGE_ACCOUNT=$STORE_ACOUNT \
#   --from-literal=AZURE_SAS_TOKEN=$STORAGE_KEY