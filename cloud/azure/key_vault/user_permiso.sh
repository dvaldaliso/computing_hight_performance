#!/bin/bash
# Script to assign Key Vault Secrets User role to a user for a specific Key Vault

export KEYVAULT_NAME="certificateclient"
export USER_PRINCIPAL_NAME="ariel.martinez@amartinezadvisorsy.onmicrosoft.com"
#Listar usuarios
az ad user list  -o table
#Obtener el objectId del usuario
az ad user show --id $USER_PRINCIPAL_NAME --query objectId -o tsv
#Asignar el rol de Key Vault Secrets User al usuario para el Key Vault especificado
az role assignment create --role "Key Vault Secrets User" --assignee $USER_PRINCIPAL_NAME --scope $(az keyvault show --name $KEYVAULT_NAME --query id -o tsv)
