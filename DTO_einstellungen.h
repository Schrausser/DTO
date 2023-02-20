#if !defined(AFX_DTO_EINSTELLUNGEN_H__2B20E00A_9E64_4F4E_A6E6_6B73AF52E3B8__INCLUDED_)
#define AFX_DTO_EINSTELLUNGEN_H__2B20E00A_9E64_4F4E_A6E6_6B73AF52E3B8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DTO_einstellungen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DTO_einstellungen dialog

class DTO_einstellungen : public CDialog
{
// Construction
public:
	DTO_einstellungen(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DTO_einstellungen)
	enum { IDD = IDD_DTO_einstellungen };
	CString	m_ini_rawtyp;
	CString	m_ini_parameter;
	CString	m_ini_pfad_dtmneu;
	CString	m_ini_pfad_dtord;
	CString	m_ini_pfad_dtnum;
	BOOL	m_check_ini;
	int		m_num_i;
	int		m_num_k;
	CString	m_ini_pfad_dtprm;
	CString	m_ini_bildtyp;
	BOOL	m_check_auto;
	BOOL	m_check_log;
	BOOL	m_check_view;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DTO_einstellungen)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DTO_einstellungen)
	afx_msg void OnCHECKeinstellungen();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKauto();
	afx_msg void OnCHECKview();
	afx_msg void OnCHECKlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTO_EINSTELLUNGEN_H__2B20E00A_9E64_4F4E_A6E6_6B73AF52E3B8__INCLUDED_)
