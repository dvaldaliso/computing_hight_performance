import json
import os
import shutil
import subprocess
import sys

from azure.storage.blob import BlobServiceClient

# Configuración de conexión (mejor si esta cadena no se expone así en producción)
account_url = ""
container_name = "mysql-backups"

LOCAL_BASE_DIR = "./backups"

MYSQL_USER = ""
MYSQL_PASSWORD = ""
MYSQL_HOST = ""
MYSQL_DATABASE = ""


def download_backup_folder(backup_folder_blob):
    print(f"\n⏳ Descargando backup: {backup_folder_blob}") 
    blob_service_client = BlobServiceClient.from_connection_string(account_url)
    container_client = blob_service_client.get_container_client(container_name)
    
    # Aseguramos que el prefijo termina en '/'
    if not backup_folder_blob.endswith('/'):
        backup_folder_blob += '/'

    blobs_list = container_client.list_blobs(name_starts_with=backup_folder_blob)

    # Para que el nombre local no cree subcarpetas inesperadas, 
    # reemplazamos / por _ en el nombre de carpeta local
    safe_folder_name = backup_folder_blob.rstrip('/').replace('/', '_')
    local_backup_dir = os.path.join(LOCAL_BASE_DIR, safe_folder_name)

    if not os.path.exists(local_backup_dir):
        os.makedirs(local_backup_dir)

    for blob in blobs_list:
        if blob.size == 0:
            # Saltar blobs vacíos que pueden ser marcadores de carpeta
            continue

        blob_name = blob.name
        relative_path = blob_name[len(backup_folder_blob):].lstrip('/')
        if not relative_path:
            continue  # en caso raro que sea el prefijo solo

        local_path = os.path.join(local_backup_dir, relative_path)
        local_dir = os.path.dirname(local_path)
        if not os.path.exists(local_dir):
            os.makedirs(local_dir)

        print(f"Descargando blob {blob_name} a {local_path}")
        with open(local_path, "wb") as f:
            download_stream = container_client.download_blob(blob_name)
            f.write(download_stream.readall())
    print(f"Backup descargado exitosamente en {local_backup_dir}")
    return local_backup_dir

def filtrar_dump_esquema(origen_dir, esquema, destino_dir):
    if not os.path.exists(destino_dir):
        os.makedirs(destino_dir)
    # Copiar solo archivos que contengan "produccion@" en su nombre (archivos .tsv.zst y DDL)
    for root, dirs, files in os.walk(origen_dir):
        # Para preservar estructura relativa:
        rel_path = os.path.relpath(root, origen_dir)
        destino_subdir = os.path.join(destino_dir, rel_path)
        if not os.path.exists(destino_subdir):
            os.makedirs(destino_subdir)

        for f in files:
            # Filtramos archivos de dump del esquema producido
            if esquema + "@" in f or f.endswith(".sql") or f.endswith(".ddl") or f.endswith(".txt") or f.endswith(".json"):
                # Esto incluye los archivos con datos del esquema y posibles archivos DDL o configuraciones
                origen_file = os.path.join(root, f)
                destino_file = os.path.join(destino_subdir, f)
                shutil.copy2(origen_file, destino_file)
                print(f"Copiado: {origen_file} -> {destino_file}")
def restore_mysqlsh(local_backup_dir):
    print("Iniciando restauración con mysqlsh...")
    path_js_escaped = json.dumps(local_backup_dir)

    cmd = [
    "mysqlsh",
    f"--user={MYSQL_USER}",
    f"--password={MYSQL_PASSWORD}",
    f"--host={MYSQL_HOST}",
    "--port=3306",
    "--js",
    "-e",
    f"util.loadDump({json.dumps(destino)}, {{threads: 4}});"
    ]

    result = subprocess.run(cmd, capture_output=True, text=True)
    if result.returncode == 0:
        print("Restauración completada exitosamente.")
    else:
        print("Error en la restauración:")
        print(result.stderr)

    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Uso: python restore_backup.py <nombre_carpeta_backup_en_blob>")
        sys.exit(1)

    backup_folder_blob = sys.argv[1]

    #local_dir = download_backup_folder(backup_folder_blob)
    origen=r"./backups/advisorsydatabase-mygreatschedule250627004204"
    esquema = "produccion"
    destino = "./backups/solo_produccion"
    filtrar_dump_esquema(origen, esquema, destino)
    restore_mysqlsh(destino)

    print("\n🚀 Proceso completado.")