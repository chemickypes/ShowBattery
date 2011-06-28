
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utistring.h"



/*
 Funzione che prende una stringa del tipo "100%" e restituisce il valore numerico
 compiendo opportune modifiche
*/
int rest_valore(char* stringa){
	int i;	
	for(i = 0; i < strlen(stringa); i++){
		if(stringa[i] == '%'){
			stringa[i] = '\0';
		}
	}
	
	sscanf(stringa,"%d",&i);
	return i;
}

/*
 Funzione che preso il file restituisce un intero,
 ovvero, il livello corrente della batteria
*/
int getIntero(){
	FILE* file;
	char batteria[20];
	char numero_batteria[20];
	char livello_carica[20];
	char numero_livello_carica[20];

	char* pathtofile = (char*)malloc(sizeof(char)*120);		
	pathtofile = realPath("/.showbattery/livello_batteria");
	//acquisisco gli elementi che mi servono
	//questo metodo è spartano ma efficace	
	if((file = fopen(pathtofile,"r")) != NULL){
		fscanf(file,"%s %s %s %s", batteria, numero_batteria, livello_carica, numero_livello_carica);
	}
	//chiudo il file che non mi serve più
	fclose(file);
	
	//restituisco il valore del livello della batteria
	//chiamando la funzione rest_valore() che prende come
	//parametro una stringa e restituisce il valore all'interno
	return rest_valore(numero_livello_carica);
}




