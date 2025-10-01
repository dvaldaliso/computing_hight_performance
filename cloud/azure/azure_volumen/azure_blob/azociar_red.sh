export REGION="westeurope"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
export STORE_ACOUNT="storepaneladvisorsy"
export MY_AKS_CLUSTER_NAME="cluster-advisorsy"
export ID_STORAGE=""
export ID_CLUSTER=""
export AKS_VNET="/subscriptions/c83d31e0-2b22-4dbe-9340-b522a54aed64/resourceGroups/panel_advisorsy/providers/Microsoft.Network/virtualNetworks/AKSVnet/subnets/aks-subnet"
az network vnet create \
  --name AKSVnet \
  --resource-group $MY_RESOURCE_GROUP_NAME \
  --location westeurope \
  --address-prefix 10.0.0.0/16 \
  --subnet-name aks-subnet \
  --subnet-prefix 10.0.0.0/24
AKS_VNET_ID=$(az network vnet show \
  --name AKSVnet \
  --resource-group $MY_RESOURCE_GROUP_NAME \
  --query id \
  --output tsv)
ID_STORAGE=$(az storage account show --name $STORE_ACOUNT --resource-group $MY_RESOURCE_GROUP_NAME --query id --output tsv)

ID_CLUSTER=$(az aks show --resource-group  $MY_RESOURCE_GROUP_NAME --name $MY_AKS_CLUSTER_NAME --query "networkProfile.loadBalancerProfile" )

echo $ID_STORAGE
echo $ID_CLUSTER
echo $AKS_VNET