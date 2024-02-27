#estado
PDU=pdu1-labs.disca.upv.es
USER=practica
PASS=cos

{ printf "$USER\n$PASS\n1\n\e4"; sleep 2; }|telnet $PDU
