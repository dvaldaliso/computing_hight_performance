-- K8 demo run

-- First run de config map
kubectl apply -f mongo-config.yaml
-- Mongo secret
kubectl apply -f mongo-secret.yaml
-- Creamos database
kubectl apply -f mongo_deployment_service.yaml 
--- Creamos la web
kubectl apply -f webapp.yaml 

para webapp utilice la imagen de la aplicacion que tengo en application
me install la aplicacion "kind"
dentro del entorno de kubectl contrui la imagen y luego
luego la cargue
kind load docker-image my-app:1.0


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




