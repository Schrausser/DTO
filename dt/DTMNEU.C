//---------------------------------------------------------------------------| DTMNEU by Dietmar SCHRAUSSER 2oo8          

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void _err_msg (); //---------------------------------------------------------> prozedur fehlermeldung und usage instruktion   
void _head(void); //---------------------------------------------------------> prozedur für kopfzeilen                        
               
main(int argc, char *argv[]) //----------------------------------------------> main übernimmt n argumente im vektor argv      
{   
	FILE *inStream, *outStream; //-------------------------------------------> stream                                      
      
	if (argc != 2) //--------------------------------------------------------> was wenn keine oder zuwenig, zuviel argumente? 
	{
   		printf("ERROR, check arguments!\n");
   		_err_msg(argv[0]);
	}
	
	outStream = fopen( "~tmp01.bat","w" );//---------------------------------> anlegen von ordner DTMNEU kopieren der eingabedatei

	fprintf(outStream, "md ~tmp_DTMNEU\ncopy %s ~tmp_DTMNEU\\\n", argv[1]);
	fclose( outStream );
	
	system("~tmp01.bat");
	system("del ~tmp01.bat");
	
	//-----------------------------------------------------------------------| öffnet input datei, name wird übergeben (erstes argument)        
	inStream = fopen( argv[1],"w" );                                                                              
   
	if (inStream == NULL) //-------------------------------------------------> was wenn keine inputdatei                      
	{
		printf("ERROR, check file %s!\n", argv[1]);
		_err_msg(argv[0]);
	}
  
	_head();

	fclose( inStream );
	
 
	return 0;
}

//--------------------------------------------------------------------------| allgemeine fehlerroutine                       
void _err_msg()
{
	printf("---------------------------------------------------------\n");
	printf("Usage: DTMNEU [input] \n ");
	printf("[input] ... Eingabe Datei\n");
	printf("---------------------------------------------------------\n");
	printf("DTMNEU by Dietmar Schrausser\n");
        printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

//---------------------------------------------------------------------------| titelzeile bildschirmausgabe                   
void _head(void) 
{
	printf("\nDTMNEUby Dietmar Schrausser\n");
	printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	printf("computing DTMNEU:"); 
}

//---------------------------------------------------------------------------| ENDE                                             