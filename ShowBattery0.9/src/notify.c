/*
	questo file contiene l'implementazione dei metodi per gestire
	il lancio delle notifiche
*/
#include <libnotify/notify.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "restvalore.h"
#include "costanti.h"
#include "structLB.h"
#include "utistring.h"



/*
	funzione che crea la struttura che contiene il testo della
	notifica
*/

struct livelloBatteria setstruct( char* titolo, char* messaggio,char* path,int livelloBatteria){
	//nuova struttura da inizializzare
	struct livelloBatteria  livello;
	//stringa che contiene l'intero messaggio
	char* interoMessaggio = (char*)malloc(sizeof(char) * 70); 
	//strnga che contiene il messaggio da passare come parametro alla struttura
	char* msg = (char*)malloc(sizeof(char) * 70);
	//stringa che contiene il path reale
	char* pth = (char*)malloc(sizeof(char) * 120);
	
	//creo il messaggio
	msg = itoa(livelloBatteria,interoMessaggio,10,messaggio);
	//creo il path
	pth = realPath(path);

	//modifico la struttura da ritornare
	livello.titolo = titolo;
	livello.messaggio = msg;
	livello.pathToIcon = pth;
	return livello;
}

/*
	funzione che lancia la notifica, costruisce la struttura e lancia quella
	adeguata
*/
void getNotifyC(int livelloBat){	
	//nuova struttura
	struct livelloBatteria livello ;
	//nuova notifica
	NotifyNotification *notifica;  

	//in base al livello della batteria costruisce la struttura
	if(livelloBat == FULL){
		livello=setstruct(TITOLO_FULL,MESSAGGIO_FULL,PATH_FULL, livelloBat);
	}else if(livelloBat <= SOME && livelloBat >= DANGER){
		livello=setstruct(TITOLO_SOME,MESSAGGIO_SOME,PATH_SOME,livelloBat);
	}else if(livelloBat <= DANGER && livelloBat >= EMPTY){
		livello=setstruct( TITOLO_DANGER,MESSAGGIO_DANGER,PATH_DANGER,livelloBat);
	}else{
		livello=setstruct(TITOLO_EMPTY,MESSAGGIO_EMPTY,PATH_EMPTY,livelloBat);
	}

	//manda la notifica
	    //Messaggio con titolo testo e icona
    notifica = notify_notification_new (livello.titolo,
					livello.messaggio, livello.pathToIcon);
	 //Mostra la notifica se possibile altrimenti termina con errore
    if (!notify_notification_show (notifica, NULL)) 
    {
		fprintf(stderr, "Problemi nel mostrare la notifica\n");
    }
    g_object_unref(G_OBJECT(notifica));


}


/*
	funzione che genera un processo figlio per costruire il file
	da cui prendere il livello della batteria
*/
void getNotify(){
	int livelloBatteria;
	int pid,stato;	
	pid = fork();
	if(pid == 0){
		//processo figlio
		execl("/etc/showbattery/src/genlivbat","/etc/showbattery/src/genlivbat",(char*)0);
	}else{
		//processo padre
		wait(&stato);
		livelloBatteria = getIntero();
		getNotifyC(livelloBatteria);
	}
}
