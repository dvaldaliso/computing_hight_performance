import base64
import json
import os

import requests

_API_='https://pre-vidsignercloud.validatedid.com/api/v2.1'
_HEADER_ = {
        "Content-Type": "application/json",
        "Authorization": "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhdWQiOiJ2aWRjbG91ZCIsImFkbWluIjoiRmFsc2UiLCJzdWIiOiIyZmUyZTBiOC01OWM0LTQxMmItYjFjYS1hNjRkYjczOTUyZDMiLCJyb2xlIjoic3Vic2NyaXB0aW9uIiwiY2xpZW50IjoiQWR2aXNvcnN5Q2xpZW50RGVtbyIsIm5ld19lbnRpdHkiOiJUcnVlIiwiZW52IjoiUFJFUFJPRFVDVElPTiIsIm5iZiI6MTcxOTc2MDQ2NSwiZXhwIjoxNzE5NzY0MDY1LCJpYXQiOjE3MTk3NjA0NjV9.2ler1dL-uG2bk_cSkdLpdm9hOAKSWOI7_9X7Q1bRuRU",
    }

def convertFileToBase64(file_path):
    with open(file_path, 'rb') as file:
        return base64.b64encode(file.read()).decode('utf-8')
    
path_user = os.path.join(os.environ['HOME'])
print(path_user)
file_Path = os.path.join(path_user, 'Documents',"mucnap_icp_listado_trabajos.pdf")


def delete_document_by_gui(gui):
    url = f'{_API_}/documents/{gui}'
   
   
    r = requests.delete(url, headers=_HEADER_)
    if not r.ok:
        print(f"Error delete document {gui}")
        return
    return  json.loads(r.text)
def get_list_document(id):
    url = f'{_API_}/documentlist/{id}'
   
    
    r = requests.get(url, headers=_HEADER_)
    if not r.ok:
        print("Error get document list")
        return
    return  json.loads(r.text)
def send_pdf(base64PDF, name_file):
    url = f'{_API_}/documents/'

    data = {
            "FileName":name_file,
            "DocContent":base64PDF,
            "IssuerName": "David Valdaliso Lopez",
            "OrderedSignatures":True,
            "Signers":
            [
                {            
                    "SignatureType": "emailandsms",
                    "SignerName":"SignerName",
                    "TypeOfID":"Z1196381H",
                    "NumberID":"A00000000",
                    "Language":"es",
                    "PhoneNumber": "+34624179807",
                    "Email":"d.valdaliso@advisorsy.es",
                    "Visible":{"Page":1,"PosX":100,"PosY":100,"SizeX":60,"SizeY":30,"SignatureField":None,"Anchor":""},
                    "NotificationEmailMessage": {
                        "eMailBody": "debe firmar este document",
                        "eMailSubject": "Firmar documento"
                    }
                }
            ]
        }
    

    r = requests.post(url, data=json.dumps(data), headers=_HEADER_)

    if r.ok:
        print('Operación realizada con éxito de envio de pdf')
    else:
        print(f'Error en el robot procesando el elemento {name_file}, enviando PDF')  

#resp = send_pdf(convertFileToBase64(file_Path), "mucnap_icp_listado_trabajos.pdf")        
resp = get_list_document("all")
#resp=delete_document_by_gui('cfad6faf-c6fd-421a-b734-098790aca6f5')
print(resp)