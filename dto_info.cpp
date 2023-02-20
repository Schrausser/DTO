//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO - Dateiordnungs Werkzeug - Copyright (c) 2oo8 by Dietmar Schrausser
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO_info.cpp : implementation file
//
#include "stdafx.h"
#include "DTO.h"
#include "DTO_info.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

FILE *infostream;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DTO_info dialog

DTO_info::DTO_info(CWnd* pParent /*=NULL*/)
	: CDialog(DTO_info::IDD, pParent)
{
	//{{AFX_DATA_INIT(DTO_info)
	//}}AFX_DATA_INIT
}

void DTO_info::DoDataExchange(CDataExchange* pDX)
{	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DTO_info)
	//}}AFX_DATA_MAP
		
}

BEGIN_MESSAGE_MAP(DTO_info, CDialog)
	//{{AFX_MSG_MAP(DTO_info)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DTO_info::OnCancel() 
{
	char dbuffer [9],tbuffer [9];
	
	infostream = fopen ("dto.log", "a+");
	
	_strdate( dbuffer );    
	_strtime( tbuffer );

	fprintf(infostream,"-\nDTO-Info Dialog\n%s %s\n-\n", dbuffer, tbuffer);
	fprintf(infostream,"DTO - Dateiordnungs Werkzeug v[1.0]\n");
	fprintf(infostream,"Copyright (c) by Dietmar Schrausser\n");
	fprintf(infostream,"compiled on %s @ %s\n", __DATE__, __TIME__);
	fprintf(infostream,"-\n");

	fclose( infostream );
	
	CDialog::OnCancel();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT DTO_info::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}
