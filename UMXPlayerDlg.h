// UMXPlayerDlg.h : header file
//

#if !defined(AFX_UMXPLAYERDLG_H__A190A77E_133D_483A_8FE1_3E106BCB5124__INCLUDED_)
#define AFX_UMXPLAYERDLG_H__A190A77E_133D_483A_8FE1_3E106BCB5124__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUMXPlayerDlg dialog

class CUMXPlayerDlg : public CDialog
{
// Construction
public:
	CUMXPlayerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUMXPlayerDlg)
	enum { IDD = IDD_UMXPLAYER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUMXPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	DWORD pos, row, posrow;
	char musposBuf[96];

	CWnd *fileNameCaption;
	CWnd *radio1;
	CWnd *radio2;
	CWnd *radio3;
	CWnd *radio4;
	CWnd *radio5;
	CWnd *radio6;

	CWnd *modName;
	CWnd *musPos;

	// Generated message map functions
	//{{AFX_MSG(CUMXPlayerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnDestroy();
	afx_msg void OnRadio1();
	afx_msg void OnRadio3();
	afx_msg void OnRadio2();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	afx_msg void OnPlaybtn();
	afx_msg void OnPausebtn();
	afx_msg void OnStopbtn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMXPLAYERDLG_H__A190A77E_133D_483A_8FE1_3E106BCB5124__INCLUDED_)
