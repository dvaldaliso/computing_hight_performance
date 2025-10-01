En el momento de crear todod funciona bien.
pero cuando hay que asignarlo en azure hay que darle permisos a la identidad que se obtiene con el siguiente comando.

az aks show --resource-group panel_advisorsy --name cluster_advisorsy --query identity

se asigna
Roles:
1-Data Operator for Managed Disks 
2-Contributor

az role assignment create \
  --assignee "principal_id" \
  --role "rol" \
  --scope "disco"
  
az role assignment create \
  --assignee "54fce765-3fd8-4d21-ace1-94cd0f09cdb1" \
  --role "Data Operator for Managed Disks" \
  --scope "/subscriptions/c83d31e0-2b22-4dbe-9340-b522a54aed64/resourceGroups/panel_advisorsy/providers/Microsoft.Compute/disks/pv_storage_jenkins"

az role assignment create \
  --assignee "54fce765-3fd8-4d21-ace1-94cd0f09cdb1" \
  --role "Contributor" \
  --scope "/subscriptions/c83d31e0-2b22-4dbe-9340-b522a54aed64/resourceGroups/panel_advisorsy/providers/Microsoft.Compute/disks/pv_storage_jenkins"

