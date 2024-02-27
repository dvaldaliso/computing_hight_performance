PDU=pdu5-labs.disca.upv.es
USER=practica
PASS=cos

{ printf "$USER\n$PASS\n1\n9\n1\nyes\n\n\e\e4"; sleep 2; }|telnet $PDU