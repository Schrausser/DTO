//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO - Dateiordnungs Werkzeug - Copyright (c) 2oo8 by Dietmar Schrausser
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTODlg.cpp : implementation file
//
#include "stdafx.h"
#include "time.h"
#include <process.h>
#include "DTO.h"
#include "DTODlg.h"
#include "DTO_info.h"
#include "DTO_einstellungen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
// Notiz: Programm-Icon exportieren und sperat mit dem Programm verknüpfen.
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Globale Variablen
///////////////////////////////////////////////////////////////////////////////////////////////////////////// 
char //Variablen für Einstellungen aus dto.ini:
	_DTO_lw[3],
	_DTO_ini_bildtyp[5],
	_DTO_ini_rawtyp[5],
	_DTO_ini_param[50],
	_DTO_ini_num_i[3],
	_DTO_ini_num_k[3],
	_DTO_ini_pfad_dtmneu[100],
	_DTO_ini_pfad_dtord[100],
	_DTO_ini_pfad_dtnum[100],
	_DTO_ini_pfad_dtprm[100],
	_DTO_ini_check_ini[2],
	_DTO_ini_check_auto[2],
	_DTO_ini_check_view[2],
	_DTO_ini_check_log[2],
	//Variablen zur Schalteraktivierung:
	_DTO_Phase[] = "erstellen",
	_DTO_subPhase[] = "off",
	//Variablen für Systemzeit
	dbuffer [9],
	tbuffer [9];

FILE *inStream1, *inStream2, *outStream1, *memStream;

////////////////////////////////////////////////////////////////////////////////////////
// CDTODlg dialog
//System
CDTODlg::CDTODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDTODlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDTODlg)
	m_DTO_Pfad = _T("");
	m_DTO_Jahr = _T("");
	m_DTO_Monat = _T("");
	m_DTO_Tag = _T("");
	m_DTO_Name = _T("");
	m_DTO_Rest_n = 0;
	m_DTO_Typ = _T("");
	m_crw_schalter = 0;
	m_mark_1 = _T("O");
	m_mark_2 = _T("-");
	m_mark_3 = _T("-");
	m_mark_4 = _T("-");
	m_mark_5 = _T("-");
	m_mark_6 = _T("-");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
//System
void CDTODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDTODlg)
	DDX_Text(pDX, IDC_EDIT_Pfad, m_DTO_Pfad);
	DDX_Text(pDX, IDC_EDIT_Jahr, m_DTO_Jahr);
	DDX_Text(pDX, IDC_EDIT_Monat, m_DTO_Monat);
	DDX_Text(pDX, IDC_EDIT_Tag, m_DTO_Tag);
	DDX_Text(pDX, IDC_EDIT_Name, m_DTO_Name);
	DDX_Text(pDX, IDC_EDIT_Typ, m_DTO_Typ);
	DDX_Check(pDX, IDC_CHECK_CRW, m_crw_schalter);
	DDX_Text(pDX, IDC_EDIT_mark1, m_mark_1);
	DDX_Text(pDX, IDC_EDIT_mark2, m_mark_2);
	DDX_Text(pDX, IDC_EDIT_mark3, m_mark_3);
	DDX_Text(pDX, IDC_EDIT_mark4, m_mark_4);
	DDX_Text(pDX, IDC_EDIT_mark5, m_mark_5);
	DDX_Text(pDX, IDC_EDIT_mark6, m_mark_6);
	//}}AFX_DATA_MAP
}
//System
BEGIN_MESSAGE_MAP(CDTODlg, CDialog)
	//{{AFX_MSG_MAP(CDTODlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_info, Oninfo)
	ON_BN_CLICKED(IDC_Ordner_erstellen, OnOrdnererstellen)
	ON_BN_CLICKED(IDC_dDateien_ordnen, OndDateienordnen)
	ON_BN_CLICKED(IDC_CHECK_CRW, OnCheckCrw)
	ON_BN_CLICKED(IDC_Dateien_umbenennen, OnDateienumbenennen)
	ON_BN_CLICKED(IDC_neu_ordnen, Onneuordnen)
	ON_BN_CLICKED(IDC_reinigen, Onreinigen)
	ON_BN_CLICKED(IDC_hilfe, Onhilfe)
	ON_BN_CLICKED(IDC_raw_parameter, Onrawparameter)
	ON_BN_CLICKED(IDC_neu_erstellen, Onneuerstellen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////

BOOL CDTODlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Voreinstellungen bei Programmstart aus dto.ini abfragen.
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Ausführen wenn dto.ini vorhanden... 
	if (fopen ("dto.ini", "r") == ERROR) //...fehlt dto.ini wird eine Vorlage erstellt.
	{
		memStream = fopen ("dto.ini", "w");
		
		fprintf( memStream, 
				"c:\\---\\\n200-\n0-\n0-\ndb\n0\njpg\nCRW\n_srp+-\n15\n8\nc:\\---\\\nc:\\---\\\nc:\\---\\\nc:\\---\\\n1\n1\n0\n0\n"); 
		
		fclose( memStream );
	}
	
	UpdateData(TRUE);	
	
	//Einlesen der Einstellungen aus dto.ini.		
	memStream = fopen ("dto.ini", "r");
	
	char	_pfad[50], 
			_jahr[5], 
			_monat[2], 
			_tag[2], 
			_typ[2], 
			_crw_schalter[2];
	
	fscanf(	memStream, 
			"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
				
			_pfad, 
			_jahr, 
			_monat, 
			_tag, 
			_typ, 
			_crw_schalter,
			_DTO_ini_bildtyp,
			_DTO_ini_rawtyp,
			_DTO_ini_param,
			_DTO_ini_num_i,
			_DTO_ini_num_k,
			_DTO_ini_pfad_dtmneu,
			_DTO_ini_pfad_dtord,
			_DTO_ini_pfad_dtnum,
			_DTO_ini_pfad_dtprm,
			_DTO_ini_check_ini,
			_DTO_ini_check_auto,
			_DTO_ini_check_view,
			_DTO_ini_check_log
		  );
		
	//Variablenintialisierung aus dto.ini, Dialogausgabe. 
	m_DTO_Pfad = _pfad;
	m_DTO_Jahr = _jahr;
	m_DTO_Monat = _monat;
	m_DTO_Tag = _tag;
	m_DTO_Typ = _typ;
	m_crw_schalter = atoi(_crw_schalter);
		
	fclose( memStream );
		
	UpdateData(FALSE);
	
	return TRUE;  
}

//System
void CDTODlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//System
HCURSOR CDTODlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schritt 1 - Ordner erstellen
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::OnOrdnererstellen() 
{
	if ( strcmp(_DTO_Phase, "erstellen") == 0 ) //Phasen Überprüfung.
	{
		UpdateData(TRUE);
		
		//Schaltermarkierungen festlegen
		m_mark_1 = _T("b");
		m_mark_2 = _T("O");
		m_mark_3 = _T("-");
		m_mark_4 = _T("-");
		m_mark_5 = _T("-");
		m_mark_6 = _T("-");

	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 1 - Ordner erstellen / Temporäre DOS Batch schreiben:
		
		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );
	
		//Schreibt DOS Batch Befehlszeile: md erstellt den Ordner für Tag bzw. Inhalt.
		fprintf (	outStream1, 
					
					"@echo off\necho -\necho DTO-Batch 1: Ordner_erstellen\necho %s %s\nmd %s%s_%s_%s_%s_%s\\\n",	
				
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name
			    );
	
		//Schreibt DOS Batch Befehlszeile: md erstellt den Ordner für die Bilder (jpg).
		fprintf (	outStream1, 
					
					"md %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\\n", 
				
					m_DTO_Pfad,	m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);

		if (m_crw_schalter == 1) //Wenn Schalter für RAW ein:
		{
			//Schreibt DOS Batch Befehlszeile: md erstellt den Ordner für die RAW Daeien.
			fprintf (	outStream1, 
						
						"md %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\", 
					
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
						m_DTO_Jahr,	m_DTO_Monat,m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp
					);
		}

		fclose( outStream1 );
	  
	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 1 - Ordner erstellen / Temporäre DOS Batch ausführen:
		
		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log");
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 
	
		UpdateData(FALSE);
	
		strcpy (_DTO_Phase, "ordnen"); //Phasen Variable aktualisieren.
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schritt 2 - Dateien ordnen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::OndDateienordnen() 
{	
	if ( strcmp(_DTO_Phase, "ordnen") == 0) //Phasen Überprüfung.
	{
		UpdateData(TRUE);
	
		//Schaltermarkierungen festlegen
		m_mark_1 = _T("v");
		m_mark_2 = _T("b");
		m_mark_3 = _T("O");
		m_mark_4 = _T("-");
		m_mark_5 = _T("O");
		m_mark_6 = _T("-");
	
	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 2 - Dateien ordnen / Temporäre DOS Batch schreiben:

		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );
	
		//Schreibt DOS Batch Befehlszeile: md erstellt den temporären Ordnungsordner ~O_ORDNEN.
		fprintf (	outStream1, 
					
					"@echo off\necho -\necho DTO-Batch 2: Bild_Dateien_ordnen\necho %s %s\nmd %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n", 
				
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
		    	);
	   
		//Schreibt DOS Batch Befehlszeile: md erstellt den temporären Sicherungsordner ~tmp_URKOPIE für JPG.
		fprintf (	outStream1, 
				
					"md %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_bild\\\n", 
				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,	
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
		    	);
	
		//Schreibt DOS Batch Befehlszeile: move verschiebt DTMNEU.lnk in den temporären Ordnungsordner ~O_ORDNEN.
		fprintf (	outStream1, 
				
					"move %sDTMNEU.lnk %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n",
								
					_DTO_ini_pfad_dtmneu, 
					m_DTO_Pfad,	m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
		    	);
	
		//Schreibt DOS Batch Befehlszeile: move verschiebt DTMNEU.exe in den Hauptordner.
		fprintf (	outStream1, 
					
					"move %sDTMNEU.exe %s%s_%s_%s_%s_%s\\\n",
								
					_DTO_ini_pfad_dtmneu, 
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name
				);
	
		//Schreibt DOS Batch Befehlszeile: xcopy kopiert JPGs in den temporären Ordnungsordner ~O_ORDNEN.
		fprintf (	outStream1, 
				
					"xcopy %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.%s %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad, m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,	
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ									
		    	);

		//Schreibt DOS Batch Befehlszeile: xcopy kopiert JPGs in den temporären C
		fprintf (	outStream1, 
				
					"xcopy %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.%s %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_bild\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad,	m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
				);
	
		if (m_crw_schalter == 1) //Wenn Schalter für RAW ein:
		{
			//Schreibt DOS Batch Befehlszeile: md erstellt den temporären Sicherungsordner ~tmp_URKOPIE für RAW
			fprintf (	outStream1, 
						
						"md %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_%s\\\n", 
					
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_rawtyp
			    	);

			//Schreibt DOS Batch Befehlszeileszeile: xcopy kopiert RAWs in den temporären Sicherungsordner ~tmp_URKOPIE
			fprintf (	outStream1, 
					
						"xcopy %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\*.%s %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_%s\\\n",
								
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ,	_DTO_ini_rawtyp, _DTO_ini_rawtyp,
						m_DTO_Pfad,	m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ,	_DTO_ini_rawtyp									
			    	);
		}

		fclose( outStream1 );

	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 2 - Dateien ordnen / Temporäre DOS Batch ausführen:
	
		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen.  
	
		UpdateData(FALSE);
	
		strcpy (_DTO_Phase, "umbenennen"); //Phasen Variable aktualisieren.
		strcpy (_DTO_subPhase, "neuerstellen"); //Subphasen Variable aktualisieren.
	}	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schritt 2.1 - neu erstellen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::Onneuerstellen() 
{
	if ( strcmp(_DTO_subPhase, "neuerstellen") == 0) //Subphasen Überprüfung.
	{
		UpdateData(TRUE);

		//Schaltermarkierungen festlegen
		m_mark_1 = _T("O");
		m_mark_2 = _T("-");
		m_mark_3 = _T("-");
		m_mark_4 = _T("-");
		m_mark_5 = _T("-");
		m_mark_6 = _T("-");
	
	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 2.1 - neu erstellen / Temporäre DOS Batch schreiben:

		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );

	  //Schreibt DOS Batch Befehlszeile: move verschiebt DTMNEU.lnk zurück.
		fprintf (	outStream1, 
				
					"@echo off\necho -\necho DTO-Batch 2.1: neu_erstellen\necho %s %s\nmove %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\DTMNEU.lnk %s\n",
					
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag, m_DTO_Typ,
					_DTO_ini_pfad_dtmneu	
			    );	
	
		//Schreibt DOS Batch Befehlszeile: move schiebt DTMNEU.exe zurück.
		fprintf (	outStream1, 
					
					"move %s%s_%s_%s_%s_%s\\DTMNEU.exe %s\n",
 
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
					_DTO_ini_pfad_dtmneu 
			    );

		//Schreibt DOS Batch Befehlszeile: rd löscht alle erstellten Ordner und Dateien.
		fprintf (	outStream1, 
					
					"rd /s /q %s%s_%s_%s_%s_%s\\\n",	
				
					m_DTO_Pfad,	m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name
			    );

		fclose( outStream1 );

	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 2.1 - Dateien neu erstellen / Temporäre DOS Batch ausführen:
	
		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 

		UpdateData(FALSE); 

		strcpy (_DTO_Phase, "erstellen"); //Phasen Variable aktualisieren.	
		strcpy (_DTO_subPhase, "off"); //Subphasen Variable aktualisieren.
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schritt 3 - Dateien umbenennen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::OnDateienumbenennen() 
{
	if (strcmp(_DTO_Phase, "umbenennen") == 0) //Phasen Überprüfung.
	{
		UpdateData(TRUE);
		
		//Schaltermarkierungen festlegen
		m_mark_1 = _T(".");
		m_mark_2 = _T("v");
		m_mark_3 = _T("b");
		m_mark_4 = _T("O");
		m_mark_5 = _T("-");
		m_mark_6 = _T("O");
	
	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch schreiben:
	  //Durchgang 1/3	
		
		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );
	
		//Schreibt DOS Batch Befehlszeile: move verschiebt DTMNEU.lnk zurück.
		fprintf (	outStream1, 
				
					"@echo off\necho -\necho DTO-Batch 3/1: Bild_Dateien_umbenennen\necho %s %s\nmove %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\DTMNEU.lnk %s\n",
					
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag, m_DTO_Typ,
					_DTO_ini_pfad_dtmneu	
			    );	
	
		//Schreibt DOS Batch Befehlszeile: move schiebt DTMNEU.exe zurück.
		fprintf (	outStream1, 
					
					"move %s%s_%s_%s_%s_%s\\DTMNEU.exe %s\n",
 
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
					_DTO_ini_pfad_dtmneu 
			    );
	
		//Schreibt DOS Batch Befehlszeile: dir erstellt eine nach datum geordnete Verzeichnisdatei ~dirjpg.txt der geordneten JPGs. 
		fprintf (	outStream1, 
				
					"dir %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\*.%s /b /n /o:d  > %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\~dirjpg.txt\n",
 						
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad, m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat,m_DTO_Tag,	m_DTO_Typ
		    	);
	
		if (m_crw_schalter == 1) //Wenn Schalter für RAW ein:
		{
			//schreibt DOS Batch Befehlszeileszeile: dir erstellt eine nach name geordnete verzeichnisdatei ~dirraw raw dateien 
			fprintf (	outStream1, 
					
						"dir %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\*.%s /b /n > %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\~dirraw.txt\n",
 						
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp, _DTO_ini_rawtyp,
						m_DTO_Pfad, m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,	
									m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_rawtyp
					);
		}
    
		fclose( outStream1 );

	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch ausführen:
	  //Durchgang 1/3

		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 

	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch schreiben:
	  //Durchgang 2/3
	
		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );
	
		//Schreibt DOS Batch Befehlszeile: DTORD generiert rename BATCH ~renjpg.bat 
		fprintf (	outStream1, 
				
					"@echo off\necho -\necho DTO-Batch 3/2: Bild_Dateien_umbenennen\necho %s %s\n%sDTORD %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\~dirjpg.txt %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\~renjpg.bat %s %s %s 0\necho -\n",
 				
					dbuffer, tbuffer,
					_DTO_ini_pfad_dtord,		
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ,
					m_DTO_Jahr,	// DTORD Argument -Jahr-
					m_DTO_Monat,// DTORD Argument -Monat-
					m_DTO_Tag	// DTORD Argument -Tag-
				);
	
	
		fclose( outStream1 );

	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch ausführen:
	  //Durchgang 2/3

		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 

		/////////////////////////////////////////////////////////////////////////////////////////////////////
		//Anhängen an von RAW Verarbeitungsparametern:
		if ( m_crw_schalter == 1 && strcmp(_DTO_ini_param, "_srp+-") != 0) //Wenn Schalter für RAW ein und RAW Verarbeitungsparameter angeführt:
		{
		  //////////////////////////////////////////////////////////////////////////////////////////////////////
		  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch schreiben:
		  //IF bedingter Durchgang 
			
			outStream1 = fopen ("~tmp01.bat", "w");

			_strdate( dbuffer );    
			_strtime( tbuffer );

			strncpy (_DTO_lw, m_DTO_Pfad, 2); //Laufwerk.

			//Schreibt DOS Batch Befehlszeile: DTPRM modifiziert rename Batch ~renjpg.bat zu ~renjpg01.bat
			fprintf (	outStream1, 
				
						"@echo off\necho -\necho DTO-Batch 3/RAW_Verarbeitungs_Parameter: Bild_Dateien_umbenennen\necho %s %s\n%sDTPRM  %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\~renjpg.bat %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\~renjpg01.bat %s\necho -\n",
 				
						dbuffer, tbuffer,
						_DTO_ini_pfad_dtprm,		
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ,
						_DTO_ini_param	// DTPRM Argument -Parameter-
					);

			//Schreibt DOS Batch Befehlszeile: (aktualisiert das Laufwerk) cd wechselt das Verzeichnis zum JPG Bildordner und führt ~renjpg01.bat aus. 
			fprintf (	outStream1, 
						
						"%s\ncd %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\\n~renjpg01.bat\n",
 				
						_DTO_lw,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,	
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
					);

			fclose( outStream1 );

		  /////////////////////////////////////////////////////////////////////////////////////////////////////
	      //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch ausführen:
	      //IF bedingter Durchgang
		
			//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
			if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
			//Temporäre DOS Batch ausführen:
			if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
			if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
			system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 
		}
		
		else //Wenn keine RAW Verarbeitungsparameter angeführt:
		{
		
		  //////////////////////////////////////////////////////////////////////////////////////////////////////
		  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch schreiben:
		  //ELSE bedingter Durchgang  

			outStream1 = fopen ("~tmp01.bat", "w");

			_strdate( dbuffer );    
			_strtime( tbuffer );

			strncpy (_DTO_lw, m_DTO_Pfad, 2); //Laufwerk.
			
			//Schreibt DOS Batch Befehlszeile: (aktualisiert das Laufwerk) cd wechselt das Verzeichnis zum JPG Bildordner und führt ~renjpg.bat aus
			fprintf (	outStream1, 
				
						"@echo off\necho -\necho DTO-Batch 3/keine_RAW_mit_Verarbeitungs_Parametern: Bild_Dateien_umbenennen\necho %s %s\n%s\ncd %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\\n~renjpg.bat\n",
 				
						dbuffer, tbuffer,
						_DTO_lw,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
					);

			fclose( outStream1 );

		  /////////////////////////////////////////////////////////////////////////////////////////////////////
	      //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch ausführen:
	      //ELSE bedingter Durchgang  
	
			//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
			if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
			//Temporäre DOS Batch ausführen:
			if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
			if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log");
	
			system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 
		}
	
		if (m_crw_schalter == 1) //Wenn Schalter für RAW ein:
		{
	  ////////////////////////////////////////////////////////////////////////////////////////////////////
      //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch schreiben:
      //Durchgang RAW

			outStream1 = fopen ("~tmp01.bat", "w");

			_strdate( dbuffer );    
			_strtime( tbuffer );

			strncpy (_DTO_lw, m_DTO_Pfad, 2); //Laufwerk.
	
			//Schreibt DOS Batch Befehlszeile: dir erstellt eine nach Name (Laufindex) geordnete Verzeichnisdatei ~dirnumjpg.txt der JPGs. 
			fprintf (	outStream1, 
				
						"@echo off\necho -\necho DTO-Batch 3/RAW: Bild_Dateien_umbenennen\necho %s %s\ndir %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.%s /b /n > %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\~dirnumjpg.txt\n",
 						
						dbuffer, tbuffer,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name, 
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_bildtyp,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
					);
	
			//Schreibt DOS Batch Befehlszeile: DTNUM generiert die Rename Batch ~renraw.bat. 
			fprintf (	outStream1, 
				
						"%sDTNUM %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\~dirraw.txt %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\~dirnumjpg.txt %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\~renraw.bat 0 0 %s %s\necho -\n",
 				
						_DTO_ini_pfad_dtnum,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_rawtyp,
						_DTO_ini_num_i,
						_DTO_ini_num_k
					);
		
			//Schreibt DOS Batch Befehlszeile: cd wechselt das Verzeichnis zum RAW Bildordner und führt ~renraw.bat aus. 
			fprintf (	outStream1, 
				
						"%s\ncd %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\\n~renraw.bat\n",
					
						_DTO_lw,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp
					);
		
			fclose( outStream1 );
		
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//Schritt 3 - Dateien umbenennen / Temporäre DOS Batch ausführen:
			//Durchgang RAW
	
			//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
			if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
			//Temporäre DOS Batch ausführen:
			if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
			if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log");
	
			system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 
		}

	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch schreiben:
	  //Durchgang 3/3

		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );

		 //Schreibt DOS Batch Befehlszeile: md erstellt einen temporären Ordner ~tmp.  
		fprintf (	outStream1, 
				
					"@echo off\necho -\necho DTO-Batch 3/3: Bild_Dateien_umbenennen\necho %s %s\nmd %s%s_%s_%s_%s_%s\\~temp\n", 
 				
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name
				);

		//Schreibt DOS Batch Befehlszeile: move verschiebt alle 20*.bildtyp in den Ordner ~tmp.  
		fprintf (	outStream1, 
				
					"move %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\20*.%s %s%s_%s_%s_%s_%s\\~temp\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name
				);

		//Schreibt DOS Batch Befehlszeile: move verschiebt alle 20*.[RAW]  in ~tmp.  
		fprintf (	outStream1, 
				
					"move %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\20*.%s %s%s_%s_%s_%s_%s\\~temp\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp, _DTO_ini_rawtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name
				);

		//Schreibt DOS Batch Befehlszeile: del löscht alle Dateien im Ordner bild.  
		fprintf (	outStream1, 
				
					"del /f /q %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.*\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);

		//schreibt DOS Batch Befehlszeileszeile: del löscht alle Dateien in ordner RAW. 
		fprintf (	outStream1, 
				
					"del /f /q %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\*.*\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp
				);
	
		//Schreibt DOS Batch Befehlszeile: move verschiebt alle 20*.bildtyp aus ~tmp zurück in den Ordner bild. 
		fprintf (	outStream1, 
				
					"move %s%s_%s_%s_%s_%s\\~temp\\20*.%s %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name, _DTO_ini_bildtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);

		//Schreibt DOS Batch Befehlszeileszeile: move verschiebt alle 20*.[RAW]s aus ~tmp zurück in den Ordner RAW.
		fprintf (	outStream1, 
				
					"move %s%s_%s_%s_%s_%s\\~temp\\20*.%s %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name, _DTO_ini_rawtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp
				);
	
		//Schreibt DOS Batch Befehlszeile: md erstellt das Verzeichnis ~O_MPG_.
		fprintf (	outStream1, 
				
					"md %s%s_%s_%s_%s_%s\\~O_MPG_%s_%s_%s_%s_bild\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);
	
		//Schreibt DOS Batch Befehlszeile: copy kopiert die geordneten JPGs von vom Ordner bild in ~O_MPG_. 
		fprintf (	outStream1, 
				
					"xcopy %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.%s %s%s_%s_%s_%s_%s\\~O_MPG_%s_%s_%s_%s_bild\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);
	
		 //Schreibt DOS Batch Befehlszeile: rd löscht den Ordner ~tmp.  
		fprintf (	outStream1, 
				
					"rd /s /q %s%s_%s_%s_%s_%s\\~temp\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name
				);
	
		//Schreibt DOS Batch Befehlszeile: rd löscht den Ordner ~O_ORDNEN_. 
		fprintf (	outStream1, 
				
					"rd /s /q %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);
	
		fclose( outStream1 );

	  /////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 3 - Dateien umbenennen / Temporäre DOS Batch ausführen:
	  //Durchgang 3/3
	
		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 

		UpdateData(FALSE);
	
		strcpy (_DTO_Phase, "reinigen"); //Phasen Variable aktualisieren.
		strcpy (_DTO_subPhase, "neuordnen"); //Subphasen Variable aktualisieren.
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schritt 3.1 - Dateien neu ordnen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::Onneuordnen() 
{
	if (strcmp(_DTO_subPhase, "neuordnen") == 0) //Subphasen Überprüfung.
	{
		UpdateData(TRUE);
	
		//Schaltermarkierungen festlegen
		m_mark_1 = _T("v");
		m_mark_2 = _T("b");
		m_mark_3 = _T("O");
		m_mark_4 = _T("-");
		m_mark_5 = _T("O");
		m_mark_6 = _T("-");
	
	 //////////////////////////////////////////////////////////////////////////////////////////////////////
	 //Schritt 3.1 - Dateien neu ordnen / Temporäre DOS Batch schreiben:

		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );

		//Schreibt DOS Batch Befehlszeile: del löscht alle Dateien in Ordner bild.
		fprintf (	outStream1, 
				
					"@echo off\necho -\necho DTO-Batch 3.1: neu_ordnen\necho %s %s\ndel /f /q %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.*\n",
 				
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);

		//Schreibt DOS Batch Befehlszeile: rd löscht den Ordner ~O_MPG_.
		fprintf (	outStream1, 
				
					"rd /s /q %s%s_%s_%s_%s_%s\\~O_MPG_%s_%s_%s_%s_bild\\\n",
 				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,	
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);

		//Schreibt DOS Batch Befehlszeile: rd löscht den Ordner ~tmp_DTMNEU.
		fprintf (	outStream1, 
					
					"rd /s /q %s%s_%s_%s_%s_%s\\~tmp_DTMNEU\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
				);

		//Schreibt DOS Batch Befehlszeile: md erstellt den temporären Ordnungsordner ~O_ORDNEN.
		fprintf (	outStream1, 
				
					"md %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n", 
				
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);
	
		//Schreibt DOS Batch Befehlszeile: move verschiebt DTMNEU.lnk in den temporären Ordnungsordner ~O_ORDNEN.
		fprintf (	outStream1, 
				
					"move %sDTMNEU.lnk %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n",
								
					_DTO_ini_pfad_dtmneu, 
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
				);
	
		//Schreibt DOS Batch Befehlszeile: move verschiebt DTMNEU.exe in den Hauptordner.
		fprintf (	outStream1, 
			
					"move %sDTMNEU.exe %s%s_%s_%s_%s_%s\\\n",
								
					_DTO_ini_pfad_dtmneu, 
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name
				);

		//Schreibt DOS Batch Befehlszeile: xcopy kopiert JPGs vom temporären Sicherungsordner ~tmp_URKOPIE in den Ordner bild.
		fprintf (	outStream1, 
				
					"xcopy %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_bild\\*.%s %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat,m_DTO_Tag,m_DTO_Typ,m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat,m_DTO_Tag,m_DTO_Typ,m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
				);
				
		//Schreibt DOS Batch Befehlszeile: xcopy kopiert JPGs in den temporären Ordnungsordner ~O_ORDNEN.
		fprintf (	outStream1, 
				
					"xcopy %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_bild\\*.%s %s%s_%s_%s_%s_%s\\~O_ORDNEN_%s_%s_%s_%s_bild\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_bildtyp,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr, m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ									
				);	
	
		if (m_crw_schalter == 1) //Wenn Schalter für RAW ein:
		{
			//Schreibt DOS Batch Befehlszeile: del löscht alle Dateien in Ordner RAW.
			fprintf (	outStream1, 
				
						"del /f /q %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\*.*\n",
 				
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, _DTO_ini_rawtyp	
					);

			//Schreibt DOS Batch Befehlszeile: xcopy kopiert RAWs vom temporären Sicherungsordner ~tmp_URKOPIE in den Ordner RAW.
			fprintf (	outStream1, 
					
						"xcopy %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_%s\\*.%s %s%s_%s_%s_%s_%s\\%s_%s_%s_%s_%s\\\n",
								
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,	
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ,	_DTO_ini_rawtyp, _DTO_ini_rawtyp,
						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_rawtyp									
					);
		}

		fclose( outStream1 );

	 //////////////////////////////////////////////////////////////////////////////////////////////////////
	 //Schritt 3.1 - Dateien neu ordnen / Temporäre DOS Batch ausführen:

		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log"); 
	
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 
	
		UpdateData(FALSE);
	
		strcpy (_DTO_Phase, "umbenennen"); //Phasen Variable aktualisieren.
		strcpy (_DTO_subPhase, "neuerstellen"); //Subphasen Variable aktualisieren.
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schritt 4 - temporäre Dateien und Ordner löschen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::Onreinigen() 
{
	if (strcmp (_DTO_Phase, "reinigen") == 0) //Phasen Überprüfung.
	{
		UpdateData(TRUE);

		//Schaltermarkierungen festlegen
		m_mark_1 = _T("O");
		m_mark_2 = _T("-");
		m_mark_3 = _T("-");
		m_mark_4 = _T("-");
		m_mark_5 = _T("-");
		m_mark_6 = _T("-");
	
	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 4 - temporäre Dateien und Ordner löschen / Temporäre DOS Batch schreiben:
		
		outStream1 = fopen ("~tmp01.bat", "w");

		_strdate( dbuffer );    
		_strtime( tbuffer );

		//Schreibt DOS Batch Befehlszeile: rd löscht den Ordner ~O_MPG_. 
		fprintf (	outStream1, 
				
					"@echo off\necho -\necho DTO-Batch 4: Ordnerstruktur_reinigen\necho %s %s\nrd /s /q %s%s_%s_%s_%s_%s\\~O_MPG_%s_%s_%s_%s_bild\\\n",
 					
					dbuffer, tbuffer,
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ
				);

		//Schreibt DOS Batch Befehlszeile: rd löscht den temporären Sicherungsordner ~tmp_URKOPIE bild.
		fprintf (	outStream1, 
				
					"rd /s /q %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_bild\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
				);

		//Schreibt DOS Batch Befehlszeile: rd löscht den Ordner ~tmp_DTMNEU.
		fprintf (	outStream1, 
				
					"rd /s /q %s%s_%s_%s_%s_%s\\~tmp_DTMNEU\\\n",
								
					m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
								m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ
				);

		if (m_crw_schalter == 1) //schalter für RAW ein
		{
			//Schreibt DOS Batch Befehlszeile: rd löscht den temporären Sicherungsordner ~tmp_URKOPIE RAW
			fprintf (	outStream1, 
					
						"rd /s /q %s%s_%s_%s_%s_%s\\~tmp_URKOPIE_%s_%s_%s_%s_%s\\\n",

						m_DTO_Pfad,	m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag, m_DTO_Typ, m_DTO_Name,
									m_DTO_Jahr,	m_DTO_Monat, m_DTO_Tag,	m_DTO_Typ, _DTO_ini_rawtyp									
					);
		}

		fclose( outStream1 );

	  //////////////////////////////////////////////////////////////////////////////////////////////////////
	  //Schritt 4 - temporäre Dateien und Ordner löschen / Temporäre DOS Batch ausführen:

		//Temporäre DOS Batch editieren, ggf.ausführen (Shell oder Mausclick)
		if (atoi(_DTO_ini_check_view) == 1) system("notepad ~tmp01.bat");
	
		//Temporäre DOS Batch ausführen:
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) != 1) system("~tmp01.bat"); 
		if (atoi(_DTO_ini_check_auto) == 1 && atoi(_DTO_ini_check_log) == 1) system("~tmp01.bat >> dto.log");
		
		system("del ~tmp01.bat"); //Temporäre DOS Batch löschen. 
	
		UpdateData(FALSE);
	
		strcpy (_DTO_Phase, "erstellen"); //Phasen Variable aktualisieren.
		strcpy (_DTO_subPhase, "off"); //Subphasen Variable aktualisieren.
	}
}

//Schalter Notiz: dialog/button/style/auto OFF stellen.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schalter für RAW
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::OnCheckCrw() 
{
	UpdateData(TRUE);
	
	if(m_crw_schalter == 1) 
	{	m_crw_schalter = 0; }
	 
	else				 
	{	m_crw_schalter = 1; }
	
	UpdateData(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schalter Einstellungen
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::Onrawparameter() 
{
	//Dialogaufruf:
	DTO_einstellungen dlg_DTO_einstellungen;
	dlg_DTO_einstellungen.DoModal();
	
	//Aktualisieren der Einstellungen, einlesen von dto.ini.
	
	UpdateData(TRUE);
		
	memStream = fopen ("dto.ini", "r");
	
	char	//Temporäre Variablen, da im Dialog Einstellungen keine Veränderungen stattfinden.
			__tmp01[50], __tmp02[5], __tmp03[2], __tmp04[2], __tmp05[2], __tmp06[2];
	
	fscanf(	memStream, 
			
			"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
				
			__tmp01, __tmp02, __tmp03, __tmp04,	__tmp05, __tmp06,
			_DTO_ini_bildtyp,
			_DTO_ini_rawtyp,
			_DTO_ini_param,
			_DTO_ini_num_i,
			_DTO_ini_num_k,
			_DTO_ini_pfad_dtmneu,
			_DTO_ini_pfad_dtord,
			_DTO_ini_pfad_dtnum,
			_DTO_ini_pfad_dtprm,
			_DTO_ini_check_ini,
			_DTO_ini_check_auto,
			_DTO_ini_check_view,
			_DTO_ini_check_log
		  );
		
	fclose( memStream );
		
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schalter DTO - Dokumentation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::Onhilfe() 
{
	//_spawnlp( _P_NOWAIT, "acrobat.exe", "acrobat.exe", "dto_ao.pdf", NULL );
	system("start dto_ao.pdf"); //Ruft die DTO-Dokumentation als .pdf Datei auf.
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schalter DTO - Info Fenster
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::Oninfo() 
{
	DTO_info dlg_DTO_info;
	dlg_DTO_info.DoModal();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Schalter Beenden
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDTODlg::OnCancel() 
{		
	if (atoi(_DTO_ini_check_ini) == 1) //Wenn schalter ini ein, aktuelle Einstellungen in dto.ini schreiben.
	{
		UpdateData(TRUE);
		
		memStream = fopen ("dto.ini", "w");

		fprintf(	memStream, 
					
					"%s\n%s\n%s\n%s\n%s\n%i\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
				
					m_DTO_Pfad,
					m_DTO_Jahr,
					m_DTO_Monat,
					m_DTO_Tag,
					m_DTO_Typ,
					m_crw_schalter,
					_DTO_ini_bildtyp,
					_DTO_ini_rawtyp,
					_DTO_ini_param,
					_DTO_ini_num_i,
					_DTO_ini_num_k,
					_DTO_ini_pfad_dtmneu,
					_DTO_ini_pfad_dtord,
					_DTO_ini_pfad_dtnum,
					_DTO_ini_pfad_dtprm,
					_DTO_ini_check_ini,
					_DTO_ini_check_auto,
					_DTO_ini_check_view,
					_DTO_ini_check_log
			   );

		fclose( memStream );
	
		UpdateData(FALSE);
	}

	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////ENDE//



