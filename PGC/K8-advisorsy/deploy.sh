#!/bin/bash
set -e
set -x

alias kubectl='minikube kubectl --'
minikube addons enable ingress
minikube kubectl -- apply -f redis-config.yaml
minikube kubectl -- apply -f mysql-secret.yaml
minikube kubectl -- apply  -f mysql-config.yaml
minikube kubectl -- apply  -f memcached-config.yaml

minikube kubectl -- apply  -f mysql-volumen.yaml
minikube kubectl -- apply  -f memcached-deployment_service.yaml
minikube kubectl -- apply  -f redis-deployment_service.yaml
minikube kubectl -- apply  -f mysql_deployment_service.yaml

minikube kubectl -- apply  -f webapp.yaml
minikube kubectl -- apply  -f ingress.yaml






# kubectl apply -f redis-config.yaml
# kubectl apply -f mysql-secret.yaml
# kubectl apply -f mysql-config.yaml

# kubectl apply -f mysql-volumen.yaml

# kubectl apply -f memcached-deployment_service.yaml
# kubectl apply -f redis-deployment_service.yaml
# kubectl apply -f mysql_deployment_service.yaml

# kubectl apply -f webapp.yaml