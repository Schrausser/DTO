// DTO.h : main header file for the DTO application
//

#if !defined(AFX_DTO_H__1A7AA197_E788_4450_9E0E_ECE6E18001CF__INCLUDED_)
#define AFX_DTO_H__1A7AA197_E788_4450_9E0E_ECE6E18001CF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDTOApp:
// See DTO.cpp for the implementation of this class
//

class CDTOApp : public CWinApp
{
public:
	CDTOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDTOApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTO_H__1A7AA197_E788_4450_9E0E_ECE6E18001CF__INCLUDED_)
