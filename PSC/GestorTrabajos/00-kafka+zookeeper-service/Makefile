
help:
	@echo "--------------------------------------"
	@echo " lee Makefile "
	@echo 
	@echo "  with docker-compose:"
	@echo 
	@echo " make appup"
	@echo " make appdown"
	@echo 
	@echo " PLEASE: check /etc/hosts. See docker-compose "
	@echo 
	@echo "you can log into a running kafka broker:"
	@echo 
	@echo "          docker-compose exec kafka1 bash"
	@echo 
	@echo " and then run commands to administer the cluster:"
	@echo
	@echo "kafka-topics --bootstrap-server localhost:9091  --list / --describe  --create ..."
	@echo "kafka-console-producer --bootstrap-server localhost:9091  ..."
	@echo "kafka-console-consumer --bootstrap-server localhost:9091  ..."
	@echo "--------------------------------------"

# -------------------------------------------------------
# recordar: docker inspect
# -------------------------------------------------------

# -------------------------------------------------------
#  
#  con docker-compose
#
# -------------------------------------------------------
appup:
	docker-compose up --remove-orphans
	
appdown:
	docker-compose down 
	@echo "---------------------------------"
	docker ps -a
	@echo "---------------------------------"
	docker images
	@echo "---------------------------------"

# -------------------------------------------------------
#
# utilidades
#
# -------------------------------------------------------
#
# ver imagenes
#
ls:
	docker images

#
# ver contenedoroes
#
ps:
	clear
	@echo "---------------------------------"
	@echo "---------------------------------"
	docker ps -a
	@echo "---------------------------------"
	@echo "---------------------------------"

#
# borrar todos los contenedores
#
rmcont:
	docker rm `docker ps -aq` || true
#wc -l `ls`

#
# borrar todas las imagenes
#
rmimg:
	docker rmi `docker images -aq` || true

#
# borrar contenedores e imagenes
#
clean: rmcont rmimg
	docker rmi servidordatos_servidordatos zmqlogica_img || true
	@echo
	docker ps -a
	@echo
	docker images

