# Crear una CA
sudo grid-ca-create -force
esto te genera un globus_simple_ca_XXXXXXXX.tar.gz
[ccgc@XXX~]$ tar -zxvf globus_simple_ca_XXXXXXXX.tar.gz
[ccgc@XXX~]$ mv globus_simple_ca_XXXXXXXX/* /etc/grid-security/certificates
# Crea una petición de Certificado de usuario
grid-cert-request -ca -int -dir .
# Crea una petición de Certificado de Host
grid-cert-request -host <host> -ca -int -dir .

# firmar vuestro propio certificado con vuestra propia CA.
sudo grid-ca-sign -in usercert_request.pem -out usercert.pem
sudo grid-ca-sign -in hostcert_request.pem -out hostcert.pem


hostcert.pem - Clave pública del certificado de host
hostcert_request.pem - Fichero de petición de certificado de host
hostkey.pem - Clave privada del certificado de host
usercert.pem - Clave pública del certificado de usuario
usercert_request.pem - Fichero de petición de certificado de usuario 
userkey.pem - Clave privada del certificado de usuario

Los comandos OpenSSL que implementan estas operaciones son las
siguientes:
• Cifrado de un Fichero (Con Clave Pública) - usercert.pem
openssl smime -encrypt -in <fichero_mensaje> -out <fichero_mensaje_cifado> <fichero_clave_publica>
• Firmado (Con Clave Privada)
openssl smime -sign -text -in <fichero_mensaje> -out <fichero_mensaje_firmado> -inkey <fichero_clave_privada> -signer 
<fichero_clave_publica>
• Verificación firma (Con Clave Pública)
openssl smime -verify -in <fichero_mensaje_firmado> -out <fichero_mensaje_sin_firma> -CApath /etc/grid-
security/certificates/
• Descifrado de un Fichero (Con Clave Privada)
openssl smime -decrypt -inkey <fichero_clave_privada> -in <fichero_mensaje_cifrado> -out <fichero_mensaje_descifrado>


OJO
•Paso . Verificar con Clave Publica del Emisor. A partir del mensaje recibido de vuestro
compañero, genera el fichero “mensaje_verificado_por_mi_
y_cifrado_por_<<nombre_comp>>.txt”. A este fichero debes quitarle la primera línea antes de
descifrar.



Proxy:
grid-proxy-init -cert usercert.pem -key userkey.pem -valid 12:00