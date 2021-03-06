#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
	funzione per trasformare un intero in una stringa
*/
char* itoa(int intToCopy, char* str, int base, char*messaggio){
	char spazio = ':';
	if(base == 10){
		sprintf(str,"%d %c %s",intToCopy,spazio,messaggio);
	}else if(base == 16){
		sprintf(str,"%x %c %s",intToCopy,spazio,messaggio);
	}else if(base == 8){
		sprintf(str,"%o %c %s",intToCopy,spazio,messaggio);
	}else{
		fprintf(stderr,"Base = 10,16,8\n");
	}
	return str;
}

/*
	funzione che ritorna il reale path di un file
*/
char* realPath(char* logicPath){
	FILE* file;
	char* realPath = (char*)malloc(sizeof(char)*120);
	
	//acquisisco la stringa che è la cartella principale
	if((file = fopen("/etc/showbattery/impostazioni/info","r")) != NULL){
		fscanf(file,"%s",realPath);
	}
	fclose(file);

	//concateno le due stringhe
	realPath = strcat(realPath,logicPath);
	return realPath;
}
	
