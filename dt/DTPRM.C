//---------------------------------------------------------------------------| DTPRM by Dietmar SCHRAUSSER 2oo8               

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void _err_msg (); //---------------------------------------------------------> prozedur _err_msg fehlermeldung und usage instruktion   
void _head(void); //---------------------------------------------------------> prozedur _head für kopfzeilen  

  
FILE *inStream, *outStream; //-----------------------------------------------> streams

char           
	_tmp_,	
	__tmp[5], 
	datei_name[30], 
	datei_name_num[50], 
	dt_pur_teil[50],
	dt_ext[4];

int zeichen_bis_punktjpg, zeichen_bis_punkt;
            
//---------------------------------------------------------------------------| main übernimmt n argumente im vektor argv     
main(int argc, char *argv[]) 
{   
	if (argc != 4) //--------------------------------------------------------> was wenn keine oder zuwenig, zuviel argumente? 
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
   
	//-----------------------------------------------------------------------> Zeilenweises Einlesen und Ausgeben             
	do
	{
		_tmp_ = fgetc(inStream);//-------------------------> einlesen eines zeichens von der inputdatei 
		if (feof (inStream) != 0 ) break;//---------------------------> ende wenn eof

		fscanf (inStream,"%s%s%s", __tmp, datei_name, datei_name_num);

		zeichen_bis_punktjpg = strcspn(datei_name_num,".jpg"); //------------> Bestimmt die Anzahl der Zeichen bis zu ".jpg".
				
		strncpy (dt_pur_teil, datei_name_num, zeichen_bis_punktjpg); //------> Kopiert die Zeichen bis zu ".jpg" in dt_pur_teil.

		strrev (datei_name_num);//-------------------------------------------> Inversion von datei_name_num.
		
		zeichen_bis_punkt = strcspn(datei_name_num,"."); //------------------> Bestimmt die Anzahl der Zeichen bis zu "." (i.A. n=3). 

		strncpy (dt_ext, datei_name_num, zeichen_bis_punkt); //--------------> Kopiert die Zeichen bis zu "." in dt_ext, das ist die invertierte Erweiterung (pgj, fit etc).

		strrev (dt_ext); //--------------------------------------------------> Inversion von datei_ext.
		
		fprintf (	outStream, //--------------------------------------------> Ausgabe in argv[2], Einfügung des Parameterteils
					
					"ren %s %s%s.%s\n", 
						
					datei_name, dt_pur_teil, argv[3], dt_ext
				);
	

	}while (feof (inStream) == 0);

	fclose( inStream ); 
	fclose( outStream );

	return 0;
}

//---------------------------------------------------------------------------| programmuebersicht, allgemeine fehlerroutine,                       
void _err_msg()
{
	printf("------------------------------------------------------\n");
	printf("Usage: DTPRM [input] [output] [p] \n ");
	printf("[input] ... Eingabe Datei (DOS Batch aus DTORD)\n");
	printf(" [output] .. Ausgabe Datei (DOS Batch)\n");
	printf(" [p] ....... RAW Verarbeitungsparameter\n");
	printf("------------------------------------------------------\n");
	printf("DTPRM by Dietmar Schrausser\n");
        printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	exit(EXIT_FAILURE);
}	

//---------------------------------------------------------------------------| titelzeile zu DOS Ausgabe                  
void _head(void)
{
	printf("\nDTPRM by Dietmar Schrausser\n");
	printf("compiled on %s @ %s\n", __DATE__, __TIME__);
	printf("computing DTPRM:"); 
}

//---------------------------------------------------------------------------| ENDE                                                          
