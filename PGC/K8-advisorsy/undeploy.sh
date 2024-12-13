#!/bin/bash
set -e
set -x

alias kubectl='minikube kubectl --'

minikube kubectl -- delete -f redis-config.yaml
minikube kubectl -- delete -f mysql-secret.yaml
minikube kubectl -- delete  -f mysql-config.yaml

#minikube kubectl -- delete  -f mysql-volumen.yaml
minikube kubectl -- delete  -f memcached-deployment_service.yaml
minikube kubectl -- delete  -f redis-deployment_service.yaml
minikube kubectl -- delete  -f mysql_deployment_service.yaml
minikube kubectl -- delete pvc mysql-pv-claim
minikube kubectl -- delete pv mysql-pv-volume

minikube kubectl -- delete  -f webapp.yaml
minikube kubectl -- delete  -f ingress.yaml







# kubectl apply -f redis-config.yaml
# kubectl apply -f mysql-secret.yaml
# kubectl apply -f mysql-config.yaml

# kubectl apply -f mysql-volumen.yaml

# kubectl apply -f memcached-deployment_service.yaml
# kubectl apply -f redis-deployment_service.yaml
# kubectl apply -f mysql_deployment_service.yaml

# kubectl apply -f webapp.yaml