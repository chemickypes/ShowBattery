/*
	ShowBattery è un'applicazione leggere che permette di gestire
	semplicemente la batteria, gestisce automaticamente le notifiche e 
	inoltre, può far vedere lo stato a comando.
	Non ha l'icona per questione di scelte grafiche
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <libnotify/notify.h>
#include "notify.h"
#define TR 1
#define CINQUE_MIN 300
#define MEZZO_MIN 30

void putHelp(){
	fprintf(stderr, "Errore: showbattery [-n]\n");
}

/*
	metodo main che genera la stuttura dell'esecuzione del programma
*/
int main(int argc , char*argv[]){
	    notify_init("ShowBattery");
	//controllo se ci sono argomenti
	if(argc > 1){
		// se il secondo argomento è uguale a "-n"
		//stampo la situazione attuale
		if(strcmp(argv[1],"-n")==0){
			getNotify();
		// mando un messaggio di errore
		}else{
			putHelp();
		}
	return 0;
	//se gli argomenti non sono più di uno allora eseguo il programma normalmente
	}else{
		//ciclo infinito
		while(TR){
			//mando la notifica
			getNotify();
			//aspetto 15 minuti
			sleep(CINQUE_MIN);
		}
	}
	//esco dall'esecuzione
	return 0;
}
