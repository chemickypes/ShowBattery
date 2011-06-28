#!/bin/bash

#creo la cartella nel quale saranno salvati i file utili
mkdir ~/.showbattery/
# creo il file delle info
echo ~ > info
mv info ~/.showbattery/

pwd

#copio il file delle icone
cp -R src/icone/ ~/.showbattery/
#compilo il programma
gcc -Wall src/*.c -o showbattery `pkg-config --cflags gtk+-2.0`  `pkg-config --cflags glib-2.0` -lnotify

#avanzo con l'installazione
echo inserisci password
sudo -s

exit

#creo la cartella che conterrà il programma in etc
sudo mkdir /etc/showbattery/
sudo cp -R . /etc/showbattery/

#creo la cartella delle inpostazioni
sudo mkdir /etc/showbattery/impostazioni/
sudo cp -R ~/.showbattery/* /etc/showbattery/impostazioni/

#rendo eseguibile il file showbattery
sudo cp /etc/showbattery/showbattery /usr/bin/

#elimino il file di installazione dalla cartella /etc/showbattery
sudo rm /etc/showbattery/installshowbattery



