export DNS_ZONE="advisorsy.com"
export MY_RESOURCE_GROUP_NAME="panel_advisorsy"


az network dns zone create --resource-group $MY_RESOURCE_GROUP_NAME --name $DNS_ZONE --tags "project=advisorsy" "env=test"

az network dns zone list --resource-group $MY_RESOURCE_GROUP_NAME 