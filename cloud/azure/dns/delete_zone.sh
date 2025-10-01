export DNS_ZONE="contoso.com"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"

az network dns zone delete --resource-group $MY_RESOURCE_GROUP_NAME --name contoso.com

az network dns zone list --resource-group $MY_RESOURCE_GROUP_NAME