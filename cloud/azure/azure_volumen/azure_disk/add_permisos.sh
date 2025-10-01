export CLUSTER_NAME="cluster-advisorsy"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"
AKS_SP_ID=$(az aks show --name ${CLUSTER_NAME} --resource-group $MY_RESOURCE_GROUP_NAME --query identity.principalId --output tsv)
AKS_SP_APP_ID=$(az ad sp show --id ${AKS_SP_ID} --query appId --output tsv)
echo $AKS_SP_ID
echo $AKS_SP_APP_ID

az role assignment create \
--assignee $AKS_SP_ID \
--role "Contributor" \
--scope  "/subscriptions/c83d31e0-2b22-4dbe-9340-b522a54aed64/resourceGroups/panel_advisorsy/providers/Microsoft.Compute/disks/pv_storage_jenkins"
