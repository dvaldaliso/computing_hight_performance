

export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export SHARE_ACOUNT="sharepaneladvisorsy"
export AKS_VNET="AKSVnet"
export AKS_SUBVNET="aks-subnet"



az storage account create \
  --name $STORE_ACOUNT \
  --resource-group $MY_RESOURCE_GROUP_NAME \
  --location $REGION \
  --sku Standard_LRS

export AZURE_STORAGE_SAS_TOKEN=$(az storage account generate-sas \
  --permissions acdlrw \
  --account-name $STORE_ACOUNT \
  --services b \
  --resource-types sco \
  --expiry 2025-12-31T23:59:59Z)

export STORAGE_KEY=$(az storage account keys list \
  --account-name $STORE_ACOUNT \
  --resource-group $MY_RESOURCE_GROUP_NAME \
  --query "[0].value" -o tsv)
echo Storage account key: $STORAGE_KEY


# kubectl create secret generic azure-secret \
#   --from-literal=azurestorageaccountname=$STORE_ACOUNT \
#   --from-literal=azurestorageaccountkey=$STORAGE_KEY \
#   --from-literal=azurestorageaccountsastoken=$AZURE_STORAGE_SAS_TOKEN \
#   --namespace=data

#Asociacion con vnet del cluster
# export STORAGE_ACCOUNT_ID=$(az storage account show \
#   --name $STORE_ACOUNT \
#   --resource-group $MY_RESOURCE_GROUP_NAME \
#   --query id \
#   --output tsv)
# export AKS_SUBVNET_ID=$(az network vnet subnet show \
#   --resource-group $MY_RESOURCE_GROUP_NAME \
#   --vnet-name $AKS_VNET \
#   --name $AKS_SUBVNET \
#   --query "id" --output tsv)

# az storage account network-rule add \
#   --resource-group $MY_RESOURCE_GROUP_NAME \
#   --account-name $STORE_ACOUNT \
#   --subnet $AKS_SUBVNET_ID  
#Asociacion con vnet del cluster

# az storage share create \
#   --name $SHARE_ACOUNT \
#   --account-name $STORE_ACOUNT 

# STORAGE_KEY=$(az storage account keys list \
#   --account-name $STORE_ACOUNT \
#   --resource-group $MY_RESOURCE_GROUP_NAME \
#   --query "[0].value" -o tsv)


# echo Storage account key: $STORAGE_KEY

# az storage account list --output table


kubectl create secret generic azure-secret \
  --from-literal=azurestorageaccountname=$STORE_ACOUNT \
  --from-literal=azurestorageaccountkey=$STORAGE_KEY

