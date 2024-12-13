-- K8 demo run

-- First run de config map
kubectl apply -f K8-advisorsy/memcached-config.yaml
kubectl apply -f K8-advisorsy/redis-config.yaml
kubectl apply -f K8-advisorsy/mysql-secret.yaml
kubectl apply -f K8-advisorsy/mysql-config.yaml

kubectl apply -f K8-advisorsy/mysql-volumen.yaml

kubectl apply -f K8-advisorsy/memcached-deployment_service.yaml
kubectl apply -f K8-advisorsy/redis-deployment_service.yaml
kubectl apply -f K8-advisorsy/mysql_deployment_service.yaml

kubectl apply -f K8-advisorsy/webapp.yaml



para webapp utilice la imagen de la aplicacion que tengo en /application tengo que crear su imagen y meterla dentro de kubernete
me install la aplicacion "kind"
dentro del entorno de kubectl contrui la imagen y luego
luego la cargue
kind load docker-image my-app:1.0
minikube image load my-app:1.0

--- Comprobaciones
kubectl get all
kubectl logs name-pod-web

-- acceder desde el navegador
-- Listar todos los servicios
kubectl get svc
webapp-service   NodePort    10.100.231.139   <none>        3000:30100/TCP   4m10s
vemos el puerto que tiene salida

-- vemos la ip de minikube
minikube ip
-- kubectl get node -o wide
cojemos la ip
minikube   Ready    control-plane   6d7h   v1.31.0   192.168.58.2   <none>        Ubuntu 22.04.4 LTS   
para acceder seria con estos datos
192.168.58.2:30100

kubectl port-forward svc/webapp-service 3000:3000


