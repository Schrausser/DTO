#if !defined(AFX_DTO_INFO_H__A77BC93C_45E4_457D_9546_5E90B2A0A6B6__INCLUDED_)
#define AFX_DTO_INFO_H__A77BC93C_45E4_457D_9546_5E90B2A0A6B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DTO_info.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DTO_info dialog

class DTO_info : public CDialog
{
// Construction
public:
	DTO_info(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DTO_info)
	enum { IDD = IDD_DTO_info };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DTO_info)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DTO_info)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTO_INFO_H__A77BC93C_45E4_457D_9546_5E90B2A0A6B6__INCLUDED_)
