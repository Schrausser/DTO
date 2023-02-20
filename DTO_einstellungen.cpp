//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO - Dateiordnungs Werkzeug - Copyright (c) 2oo8 by Dietmar Schrausser
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO_einstellungen.cpp : implementation file
//
#include "stdafx.h"
#include "string.h"
#include "DTO.h"
#include "DTO_einstellungen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Globale  Variablen 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
char 	//Variablen für Einstellungen aus dto.ini.
		_DTO_Pfad[50],
		_DTO_Jahr[5], 
		_DTO_Monat[2], 
		_DTO_Tag[2], 
		_DTO_Typ[2], 
		_DTO_crw_schalter[2]; 

FILE *memStream1;
////////////////////////////////////////////////////////////////////////////////////////
// DTO_einstellungen dialog

DTO_einstellungen::DTO_einstellungen(CWnd* pParent /*=NULL*/)
	: CDialog(DTO_einstellungen::IDD, pParent)
{
	//{{AFX_DATA_INIT(DTO_einstellungen)
	m_ini_rawtyp = _T("");
	m_ini_parameter = _T("");
	m_ini_pfad_dtmneu = _T("");
	m_ini_pfad_dtord = _T("");
	m_ini_pfad_dtnum = _T("");
	m_num_i = 0;
	m_num_k = 0;
	m_ini_pfad_dtprm = _T("");
	m_ini_bildtyp = _T("");
	m_check_ini = 1;
	m_check_auto = 1;
	m_check_view = 0;
	m_check_log = 0;
	//}}AFX_DATA_INIT
}

void DTO_einstellungen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DTO_einstellungen)
	DDX_Text(pDX, IDC_EDIT_01, m_ini_rawtyp);
	DDX_Text(pDX, IDC_EDIT_02, m_ini_parameter);
	DDX_Text(pDX, IDC_EDIT_03, m_ini_pfad_dtmneu);
	DDX_Text(pDX, IDC_EDIT_04, m_ini_pfad_dtord);
	DDX_Text(pDX, IDC_EDIT_05, m_ini_pfad_dtnum);
	DDX_Text(pDX, IDC_EDIT_06, m_ini_pfad_dtprm);
	DDX_Text(pDX, IDC_EDIT_num_i, m_num_i);
	DDX_Text(pDX, IDC_EDIT_num_k, m_num_k);
	DDX_Text(pDX, IDC_EDIT_2, m_ini_bildtyp);
	DDX_Check(pDX, IDC_CHECK_einstellungen, m_check_ini);
	DDX_Check(pDX, IDC_CHECK_auto, m_check_auto);
	DDX_Check(pDX, IDC_CHECK_log, m_check_log);
	DDX_Check(pDX, IDC_CHECK_view, m_check_view);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(DTO_einstellungen, CDialog)
	//{{AFX_MSG_MAP(DTO_einstellungen)
	ON_BN_CLICKED(IDC_CHECK_einstellungen, OnCHECKeinstellungen)
	ON_BN_CLICKED(IDC_CHECK_auto, OnCHECKauto)
	ON_BN_CLICKED(IDC_CHECK_view, OnCHECKview)
	ON_BN_CLICKED(IDC_CHECK_log, OnCHECKlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO_einstellungen message handlers
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL DTO_einstellungen::OnInitDialog() 
{	
	CDialog::OnInitDialog();

  //Bei Dialoginitialisierung: Einlesen der Einstellungen aus dto.ini.
	
	UpdateData(TRUE);
	
	memStream1 = fopen ("dto.ini", "r");
	
	char    _bildtyp[5],	
		    _rawtyp[5],
			_param[50],
			_num_i[3],
			_num_k[3],
			_pfad_dtmneu[100],
			_pfad_dtord[100],
			_pfad_dtnum[100],
			_pfad_dtprm[100],
			_check_ini[2],
			_check_auto[2],
			_check_view[2],
			_check_log[2];
			     
	fscanf(	memStream1, 
			
			"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s", 
			
			_DTO_Pfad,
			_DTO_Jahr, 
			_DTO_Monat, 
			_DTO_Tag, 
			_DTO_Typ,
			_DTO_crw_schalter,
			_bildtyp,
			_rawtyp,
			_param,
			_num_i,
			_num_k,
			_pfad_dtmneu,
			_pfad_dtord,
			_pfad_dtnum,
			_pfad_dtprm,
			_check_ini,
			_check_auto,
			_check_view,
			_check_log
		  );
		
	//Variablenintialisierung aus dto.ini, Dialogausgabe. 
	m_ini_bildtyp = _bildtyp;
	m_ini_rawtyp = _rawtyp;
	m_ini_parameter = _param;
	m_num_i = atoi(_num_i);
	m_num_k = atoi(_num_k);
	m_ini_pfad_dtmneu = _pfad_dtmneu;
	m_ini_pfad_dtord = _pfad_dtord;
	m_ini_pfad_dtnum = _pfad_dtnum;
	m_ini_pfad_dtprm = _pfad_dtprm;
	m_check_ini = atoi(_check_ini);
	m_check_auto = atoi(_check_auto);
	m_check_view = atoi(_check_view);
	m_check_log = atoi(_check_log);
		
	fclose( memStream1 );

	UpdateData(FALSE);

	return TRUE;  	              
}

//Schalter Notiz: dialog/button/style/auto OFF stellen.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Schalter auto 
//Wenn (1) werden die DOS Batches automatisch ausgeführt,(0) erfordert händische Ausführung.
void DTO_einstellungen::OnCHECKauto() 
{
	UpdateData(TRUE);
	
	if(m_check_auto == 1) 
	{ m_check_auto = 0;} 
	else				 
	{ m_check_auto = 1;}
	
	UpdateData(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Schalter view 
//Wenn (1) werden die zur Ausführung bereiten DOS Batches via notepad geöffnet.
void DTO_einstellungen::OnCHECKview() 
{
	UpdateData(TRUE);
	
	if(m_check_view == 1) 
	{ m_check_view = 0;} 
	else				 
	{ m_check_view = 1;}
	
	UpdateData(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Schalter log
//Wenn (1) wird eine Log Datei angelegt.
void DTO_einstellungen::OnCHECKlog() 
{
	UpdateData(TRUE);
	
	if(m_check_log == 1) 
	{ m_check_log = 0;} 
	else				 
	{ m_check_log = 1;}
	
	UpdateData(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Schalter ini 
//Wenn (1) werden die aktuellen Einstellungen bei Programmende in dto.ini geschrieben. 

void DTO_einstellungen::OnCHECKeinstellungen() 
{
	UpdateData(TRUE);
	
	if(m_check_ini == 1) 
	{ m_check_ini = 0;} 
	else				 
	{ m_check_ini = 1;}
	
	UpdateData(FALSE);	
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO - Einstellungen beenden
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DTO_einstellungen::OnCancel() 
{
	UpdateData(TRUE);

  //Ausgeben der Einstellungen in dto.ini.
	
	if (m_ini_parameter == "") m_ini_parameter = "_srp+-"; //Bezeichnung wenn kein Verarbeitungsparameter.

	memStream1 = fopen ("dto.ini", "w");

	fprintf( memStream1, 
			
			"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%i\n%i\n%s\n%s\n%s\n%s\n%i\n%i\n%i\n%i\n", 
			
			_DTO_Pfad,
			_DTO_Jahr, 
			_DTO_Monat, 
			_DTO_Tag, 
			_DTO_Typ,
			_DTO_crw_schalter,
			m_ini_bildtyp,
			m_ini_rawtyp, 
			m_ini_parameter,
			m_num_i,
			m_num_k,
			m_ini_pfad_dtmneu, 
			m_ini_pfad_dtord, 
			m_ini_pfad_dtnum,
			m_ini_pfad_dtprm,
			m_check_ini,
			m_check_auto,
			m_check_view,
			m_check_log
		  );
		
	fclose( memStream1 );

	UpdateData(FALSE);
	
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

