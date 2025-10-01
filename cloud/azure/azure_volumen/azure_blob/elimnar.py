from azure.identity import DefaultAzureCredential
from azure.storage.blob import BlobServiceClient

default_credential = DefaultAzureCredential()
# CONFIGURACIÓN
#az storage account show-connection-string --name "<your-storage-account-name>"
account_url = ""
container_name = "mysql-backups"
carpetas_a_eliminar = [
    "advisorsydatabase-mygreatschedule",
    "backup",

    # Agrega aquí todas las carpetas (prefijos) que quieras eliminar
]

# CONEXIÓN AL CONTENEDOR
blob_service_client = BlobServiceClient.from_connection_string(account_url)
container_client = blob_service_client.get_container_client(container_name)

# ELIMINACIÓN DE BLOBS POR PREFIJO
for carpeta in carpetas_a_eliminar:
    print(f"\n⏳ Eliminando blobs en la carpeta: {carpeta}")
    blobs = container_client.list_blobs(name_starts_with=carpeta)
    eliminados = 0
    for blob in blobs:
        print(f"🗑️ Eliminando: {blob.name}")
        container_client.delete_blob(blob.name)
        eliminados += 1
    print(f"✅ {eliminados} blobs eliminados de '{carpeta}'")

print("\n🚀 Proceso completado.")
