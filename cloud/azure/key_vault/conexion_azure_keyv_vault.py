from azure.identity import ClientSecretCredential
from azure.keyvault.certificates import CertificateClient
from azure.keyvault.secrets import SecretClient

# pip install azure-identity azure-keyvault-secrets azure-keyvault-certificates
# Datos de tu App Registration
tenant_id = ""
client_id = ""
client_secret = ""

# Nombre de tu Key Vault
key_vault_name = "certificateclient"
vault_url = f"https://{key_vault_name}.vault.azure.net/"

# Autenticación usando App Registration
credential = ClientSecretCredential(tenant_id, client_id, client_secret)

# Cliente para secretos
secret_client = SecretClient(vault_url=vault_url, credential=credential)

# Cliente para certificados
certificate_client = CertificateClient(vault_url=vault_url, credential=credential)



# Crear cliente para secretos
secret_client = SecretClient(vault_url=vault_url, credential=credential)

# === Crear un secreto nuevo ===
new_secret_name = "minuevosecreto"
new_secret_value = "valorsupersecreto"

secret = secret_client.set_secret(new_secret_name, new_secret_value)

print(f"Secreto '{secret.name}' creado con versión {secret.properties.version}")