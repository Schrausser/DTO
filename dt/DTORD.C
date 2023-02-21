//---------------------------------------------------------------------------| DTORD by Dietmar SCHRAUSSER 2oo8               

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void _err_msg (); //---------------------------------------------------------> prozedur _err_msg fehlermeldung und usage instruktion   
void _head(void); //---------------------------------------------------------> prozedur _head für kopfzeilen  

  
FILE *inStream, *outStream; //-----------------------------------------------> streams

char dbuffer [9],tbuffer [9]; //---------------------------------------------> buffer fuer time und date                     
char datei_name[30], *index_null="0"; //-------------------------------------> index_null: vorangestellte nullen

int iLauf = 0, index = 1; //-------------------------------------------------> laufindexnummer

//---------------------------------------------------------------------------| prozedur _batch für dateiausgabe, erstellung der rename batch 
void _batch	(char bt_a1[5],
			 char bt_a2[2],
			 char bt_a3[2],
			 char *bt_index_null, int bt_index)  
{
	fprintf	(	outStream,
				"\nren %s %s_%s_%s_%s%i_%s", 
						
				datei_name,
				bt_a1,			// -Jahr-
				bt_a2,			// -Monat-
				bt_a3,			// -Tag-
				bt_index_null,	// -00-
				bt_index,		// -n-
				datei_name
			); 
}                 

//---------------------------------------------------------------------------| main übernimmt n argumente im vektor argv     
main(int argc, char *argv[]) 
{   
	if (argc != 7) //--------------------------------------------------------> was wenn keine oder zuwenig, zuviel argumente? 
	{
		printf("ERROR, check arguments!\n");
		_err_msg(argv[0]);
	}
   
	//-----------------------------------------------------------------------> def von input und outputdatei:                
	inStream  = fopen( argv[1], "r" ); //------------------------------------> input: datei mit dateinamensliste (bspsw. via "dir *.jpg \b\n\o:d > input.txt")
	outStream = fopen( argv[2], "w" ); //------------------------------------> output: batch datei (rename)
     
	if (inStream == NULL) //-------------------------------------------------> was wenn keine inputdatei                     
	{
		printf("ERROR, check file %s!\n", argv[1]);
		_err_msg(argv[0]);
    	}
   
	_head(); //--------------------------------------------------------------> DOS Ausgabe der Kopfzeilen                              
   

	//-----------------------------------------------------------------------> Zeilenweises Einlesen der Dateinamen            
	if ( atoi(argv[6]) == 0) //----------------------------------------------> eingabe n=0 -> automatische dateilängenbestimmung
	{
		do 
		{
			fscanf (inStream,"%s", datei_name); //---------------------------> Einlesen aus input

			//---------------------------------------------------------------> def der laufindex nullen Anzahl (über index)    		
			if (index < 10                 ) 	index_null = "00"; 
			if (index >  9 && index < 100  ) 	index_null = "0" ; 
			if (index >  99                ) 	index_null = ""  ;  

			_batch (argv[3], argv[4], argv[5], index_null, index); //--------> funktionsaufruf _batch() zeilenausgabe in datei
			//		-Jahr-	-Monat-		-tag-	-00-		-n-
			
			index ++;
	
		}while (feof (inStream) == 0); //------------------------------------> bis EOF		

		fclose( inStream ); 
		fclose( outStream );
	
	}
	else	//---------------------------------------------------------------> eingabe n>0, explizite dateilängen angabe 
	{
		for (iLauf = 1; iLauf < atoi(argv[6])+1; iLauf++)
		{
			fscanf (inStream,"%s", datei_name);

		//-------------------------------------------------------------------> def der laufindex nullen Anzahl (über iLauf)                                           		
		if (iLauf < 10                 ) 	index_null = "00"; 
		if (iLauf >  9 && iLauf < 100  ) 	index_null = "0" ; 
		if (iLauf >  99                ) 	index_null = ""  ;  

		_batch (argv[3], argv[4], argv[5], index_null, iLauf); //------------> funktionsaufruf _batch() zeilenausgabe in datei
		//		-Jahr-	-Monat-		-tag-	-00-		-n-
		}		

		fclose( inStream ); 
		fclose( outStream );
	}

	return 0;
}

//---------------------------------------------------------------------------| programmuebersicht, allgemeine fehlerroutine,                       
void _err_msg()
{
	printf("------------------------------------------------------\n");
	printf("Usage: DTORD [input] [output] [jjjj] [mm] [tt] [n]\n ");
	printf("[input] ... Eingabe Datei (ASCII File der Dateinamen)\n");
	printf(" [output] .. Ausgabe Datei (DOS Batch)\n");
	printf(" [jjjj] .... Jahr der Dateierstellung (4-stellig)\n");
	printf(" [mm] ...... Monat der Dateierstellung (2-stellig) \n");
	printf(" [tt] ...... Tag der Dateierstellung (2-stellig) \n");
	printf(" [n] ....... Anzahl der Dateinamen (0:auto) \n");
	printf("------------------------------------------------------\n");
	printf("DTORD by Dietmar Schrausser\n");
        printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

//---------------------------------------------------------------------------| titelzeile zu DOS Ausgabe                  
void _head(void)
{
	printf("\nDTORD by Dietmar Schrausser\n");
	printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	printf("computing DTORD:"); 
}

//---------------------------------------------------------------------------| ENDE                                                          
