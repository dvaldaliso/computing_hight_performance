
export STORAGE_NFS="pv_storage_nfs"
export STORAGE_JENKINS="pv_storage_jenkins"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"


az disk create \
    --resource-group $MY_RESOURCE_GROUP_NAME \
    --name $STORAGE_JENKINS \
    --zone 3 \
    --size-gb 20 --query id --output tsv