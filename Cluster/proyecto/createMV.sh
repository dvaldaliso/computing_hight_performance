export NAME=Base
export MEM=1000
export DISK=10000

VBoxManage createvm --name $NAME --ostype "Debian_64" --register
VBoxManage modifyvm $NAME --memory=$MEM --nic1=natnetwork
VBoxManage modifyvm $NAME --boot1 dvd --boot2 disk --boot3 none --boot4 none
VBoxManage modifyvm $NAME --graphicscontroller vmsvga --vram 33
VBoxManage storagectl $NAME --name "SATA" --add sata --portcount 10
VBoxManage storagectl $NAME --name "IDE" --add ide
VBoxManage createmedium disk --filename "$VBOX"/$NAME.vdi --size $DISK
VBoxManage storageattach $NAME --storagectl "SATA" --port 0 --type hdd --medium "$VBOX"/$NAME.vdi
VBoxManage storageattach $NAME --storagectl "IDE" --port 0 --device 0 --type dvddrive --medium "emptydrive"