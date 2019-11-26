// UMXPlayer.h : main header file for the UMXPLAYER application
//

#if !defined(AFX_UMXPLAYER_H__13E0D0F5_6A3A_40C2_9CED_E16D68DD1071__INCLUDED_)
#define AFX_UMXPLAYER_H__13E0D0F5_6A3A_40C2_9CED_E16D68DD1071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUMXPlayerApp:
// See UMXPlayer.cpp for the implementation of this class
//

class CUMXPlayerApp : public CWinApp
{
public:
	CUMXPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUMXPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUMXPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMXPLAYER_H__13E0D0F5_6A3A_40C2_9CED_E16D68DD1071__INCLUDED_)
