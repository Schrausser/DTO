//---------------------------------------------------------------------------| DTNUM Dietmar SCHRAUSSER 2oo8  		      

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void _err_msg (); //---------------------------------------------------------> prozedur fehlermeldung und usage instruktion   
void _head(void); //---------------------------------------------------------> prozedur für kopfzeilen                       
                   
char datei_name[30], datei_name_num[30], dt_num_teil[30], *dt_nam_teil;

int iLauf = 0, jLauf = 0;

//---------------------------------------------------------------------------| main übernimmt n argumente im vektor argv      
main(int argc, char *argv[]) 
{   
	FILE *inStream1, *inStream2, *outStream; //------------------------------> streams                                       

	if (argc != 8) //--------------------------------------------------------> was wenn keine oder zuwenig, zuviel argumente?
	{
		printf("ERROR, check arguments!\n");
		_err_msg(argv[0]);
	}
   
	//-----------------------------------------------------------------------> def von input und outputdatei:                 
	inStream1  = fopen( argv[1], "r" );
	outStream = fopen( argv[3], "w" );

	     
	if (inStream1 == NULL) //------------------------------------------------> was wenn keine inputdatei                     
	{
		printf("ERROR, check file %s!\n", argv[1]);
		_err_msg(argv[0]);
    	}
   
	_head(); //--------------------------------------------------------------> Ausgabe Kopfzeile                              

	//-----------------------------------------------------------------------> schleife(i) zum zeilenweises Einlesen der      
	//		                                                                   Dateinamen (file1)                
	if (atoi(argv[4]) == 0 && atoi(argv[5]) == 0) //-------------------------> Automatische Dateilängenbestimmung
	{
		do
		{
			fscanf (inStream1,"%s", datei_name);

			//---------------------------------------------------------------> schleife(j) zur durchsuchung von file1 nach    
			//							                                       übereinstimmenden num. dateinamen (file2)      
			inStream2  = fopen( argv[2], "r" );

			//for (jLauf = 1; jLauf < atoi(argv[5])+1; jLauf++) 
			do
			{
				fscanf (inStream2,"%s", datei_name_num);
			
				//-----------------------------------------------------------> kopieren des datums und nummernteils           
				//                                                                 (ersten 15 zeichen) in dt_num_teil             
				strncpy (dt_num_teil, datei_name_num, 15); 
		
				dt_nam_teil = &datei_name_num[atoi(argv[6])];	//-----------> pointer dt_nam_teil auf das 15 ([i] argv[6]) zeichen des    
																//	           nummerierten dateinamens = urspr dateiname     
			
				//-----------------------------------------------------------> vergleichen nummerierter dateiname (file2)     
				//                                                             mit dateiname (file1)                          
				//                                                             erste k (argv[7]) Zeichen ab(!) dem iten Zeichen (16, 17, 18 ....)				      
				if(strncmp(dt_nam_teil, datei_name, atoi(argv[7])) == 0) 			

				fprintf	(	outStream,
							"ren %s %s%s\n", 
						
							datei_name,
							dt_num_teil,
							datei_name
						);
			
			}while (feof (inStream2) == 0);
		
			fclose( inStream2 );
	
		}while (feof (inStream1) == 0);
	}
	else
	{
		for (iLauf = 1; iLauf < atoi(argv[4])+1; iLauf++) 
		{
			fscanf (inStream1,"%s", datei_name);
			                                               
			inStream2  = fopen( argv[2], "r" );

			for (jLauf = 1; jLauf < atoi(argv[5])+1; jLauf++) 
			{
				fscanf (inStream2,"%s", datei_name_num);
				
				strncpy (dt_num_teil, datei_name_num, 15); 
		
				dt_nam_teil = &datei_name_num[atoi(argv[6])];				      
		
				if(strncmp(dt_nam_teil, datei_name, atoi(argv[7])) == 0) 			

				fprintf	(	outStream,
							"ren %s %s%s\n", 
						
							datei_name,
							dt_num_teil,
							datei_name
						
						);
		
			}
		
			fclose( inStream2 );
	
		}
	}
 
	fclose( inStream1 );
	fclose( outStream );

	return 0;
}

//---------------------------------------------------------------------------| allgemeine fehlerroutine                       
void _err_msg()
{
	printf("--------------------------------------------------------------------\n");
	printf("Usage: DTNUM [input1] [input2] [output] [n1] [n2] [i] [k]\n ");
	printf("[input1] .. Eingabe Datei 1 (ASCII File der Dateinamen)\n");
	printf(" [input2] .. Eingabe Datei 2 (ASCII File nummerierter Dateinamen)\n");
	printf(" [output] .. Ausgabe Datei (DOS Batch)\n");
	printf(" [n1] ...... Anzahl der Dateinamen (0:auto) \n");
	printf(" [n2] ...... Anzahl der nummerierten Dateinamen (0:auto) \n");
	printf(" [i] ....... Anfangszeichen des Vergleichs (crw default i=15)  \n");
	printf(" [k] ....... Anzahl der zu vergleichenden Zeichen (crw default k=8) \n");
	printf("--------------------------------------------------------------------\n");
	printf("DTNUM by Dietmar Schrausser\n");
        printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

//---------------------------------------------------------------------------| titelzeile bildschirmausgabe                   
void _head(void)
{
	printf("\nDTNUM by Dietmar Schrausser\n");
	printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	printf("computing DTNUM:"); 	
}

//---------------------------------------------------------------------------| ENDE                                                           
