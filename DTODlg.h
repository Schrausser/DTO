// DTODlg.h : header file
//

#if !defined(AFX_DTODLG_H__7D4BAEDD_3916_4988_80D8_4D0C19E4DBB9__INCLUDED_)
#define AFX_DTODLG_H__7D4BAEDD_3916_4988_80D8_4D0C19E4DBB9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDTODlg dialog

class CDTODlg : public CDialog
{
// Construction
public:
	CDTODlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDTODlg)
	enum { IDD = IDD_DTO_DIALOG };
	CString	m_DTO_Pfad;
	CString	m_DTO_Jahr;
	CString	m_DTO_Monat;
	CString	m_DTO_Tag;
	CString	m_DTO_Name;
	int		m_DTO_Rest_n;
	CString	m_DTO_Typ;
	BOOL	m_crw_schalter;
	CString	m_mark_1;
	CString	m_mark_2;
	CString	m_mark_3;
	CString	m_mark_4;
	CString	m_mark_5;
	CString	m_mark_6;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDTODlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDTODlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Oninfo();
	afx_msg void OnOrdnererstellen();
	afx_msg void OndDateienordnen();
	afx_msg void OnCheckCrw();
	afx_msg void OnDateienumbenennen();
	afx_msg void Onneuordnen();
	afx_msg void Onreinigen();
	afx_msg void Onhilfe();
	virtual void OnCancel();
	afx_msg void Onrawparameter();
	afx_msg void Onneuerstellen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTODLG_H__7D4BAEDD_3916_4988_80D8_4D0C19E4DBB9__INCLUDED_)
