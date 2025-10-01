# Crear la app en Azure AD o Azure AD, ahora llamado Microsoft Entra ID,
export NameApp="DevKeyVaultApp"
az ad app create --display-name $NameApp --query appId -o tsv

export NameAppid="576b274a-58f4-4066-b65d-053f0eef9f7a"
# Crear un service principal
az ad sp create --id $NameAppid

# Crear un secreto para autenticación
az ad app credential reset --id $NameAppid --display-name "DevSecret" --query password -o tsv



az role assignment create --role "Key Vault Administrator" --assignee $NameAppid --scope $(az keyvault show --name certificateclient --resource-group panel_advisorsy --query id -o tsv)


export NOMBRE_KEYVAULT="certificateclient"
az keyvault set-policy --name $NOMBRE_KEYVAULT  --spn $NameAppid --secret-permissions get list set delete  --key-permissions get list create delete --certificate-permissions get list create delete