// UMXPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UMXPlayer.h"
#include "UMXPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUMXPlayerDlg dialog

CUMXPlayerDlg::CUMXPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUMXPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUMXPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUMXPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUMXPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

void UselessFunction()
{
	printf("UselessFunction called for some reason...");
}

BEGIN_MESSAGE_MAP(CUMXPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CUMXPlayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnRadio6)
	ON_BN_CLICKED(IDC_PLAYBTN, OnPlaybtn)
	ON_BN_CLICKED(IDC_PAUSEBTN, OnPausebtn)
	ON_BN_CLICKED(IDC_STOPBTN, OnStopbtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUMXPlayerDlg message handlers

BOOL CUMXPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	// get the filename label :)
	fileNameCaption = GetDlgItem(IDC_FILENAME);
	
	// radio buttons
	radio1 = GetDlgItem(IDC_RADIO1);
	radio2 = GetDlgItem(IDC_RADIO2);
	radio3 = GetDlgItem(IDC_RADIO3);
	radio4 = GetDlgItem(IDC_RADIO4);
	radio5 = GetDlgItem(IDC_RADIO5);
	radio6 = GetDlgItem(IDC_RADIO6);

	modName = GetDlgItem(IDC_MODNAME);
	musPos = GetDlgItem(IDC_MUSPOS);

	// check box

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(BST_CHECKED);

	// INIT BASS
	
	if(BASSMOD_Init(-1, 44100, 0) == FALSE) {
		AfxMessageBox("Failed to initalize BASSMOD", 0, 0);	
		exit(1);
	}

	// init timer

	SetTimer(3549, 100, NULL);

	// get device description

	CWnd* deviceDesctiptionCaption = GetDlgItem(IDC_DEVICECAPTION);

	if(BASSMOD_GetDeviceDescription(0) == NULL)
	{
		AfxMessageBox("Failed to get device description", 0, 0);
		deviceDesctiptionCaption->SetWindowText("Failed to get device description");
	}
	else
	{
		CString deviceText = BASSMOD_GetDeviceDescription(0);
		deviceDesctiptionCaption->SetWindowText(deviceText);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUMXPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUMXPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUMXPlayerDlg::OnButton1() 
{
	char* file;
	const TCHAR szFilter[] = _T("UMX files (*.umx)");

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO2))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO3))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO4))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO5))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO6))->SetCheck(BST_UNCHECKED);

	((CButton*)GetDlgItem(IDC_STOPBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);

	CFileDialog dlg(TRUE, _T("*.umx"), _T("*.umx"), OFN_FILEMUSTEXIST, szFilter, this);  
	
	if(dlg.DoModal() == IDOK)
	{
		BASSMOD_MusicStop();
		BASSMOD_MusicFree();
		CString sFilePath = dlg.GetPathName();
		fileNameCaption->SetWindowText(sFilePath);

		file = sFilePath.GetBuffer(sFilePath.GetLength());

		// play umx
		
		BOOL musicLoaded = 0;

		if(((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
		{

		    musicLoaded = BASSMOD_MusicLoad(
			FALSE,
			file,
			0,
			0,
			BASS_MUSIC_LOOP|BASS_MUSIC_POSRESET);
		} else {
			musicLoaded = BASSMOD_MusicLoad(
			FALSE,
			file,
			0,
			0,
			BASS_MUSIC_LOOP);
		}
		if(!musicLoaded)
		{
			char err[100];
			sprintf(err, "Failed to open UMX file.\nError code is: %i", BASSMOD_ErrorGetCode());
			AfxMessageBox(err, 0, 0);
			exit(1);
		}
		
		if(BASSMOD_MusicPlay())
		{
			BASSMOD_MusicSetPositionScaler(10); 
			radio1->EnableWindow(TRUE);
			radio2->EnableWindow(TRUE);
			radio3->EnableWindow(TRUE);
			radio4->EnableWindow(TRUE);
			radio5->EnableWindow(TRUE);
			radio6->EnableWindow(TRUE);

			CheckRadioButton(IDC_RADIO1, IDC_RADIO1, IDC_RADIO1);

			((CButton*)GetDlgItem(IDC_STOPBTN))->EnableWindow(TRUE);
			((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(TRUE);

			char* musicName;
			musicName = BASSMOD_MusicGetName();
			modName->SetWindowText(musicName);
		}
	}
}

void CUMXPlayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	BASSMOD_MusicStop();
	BASSMOD_MusicFree();
	BASSMOD_Free();

	ExitProcess(0);
}

void CUMXPlayerDlg::OnRadio1() 
{
	BASSMOD_MusicStop();
	BASSMOD_MusicSetPosition(MAKELONG(0,0));
	BASSMOD_MusicPlay();
}

void CUMXPlayerDlg::OnRadio3() 
{
	BASSMOD_MusicStop();
	BASSMOD_MusicSetPosition(MAKELONG(1,0));
	BASSMOD_MusicPlay();
}

void CUMXPlayerDlg::OnRadio2() 
{
	BASSMOD_MusicStop();
	BASSMOD_MusicSetPosition(MAKELONG(2,0));	
	BASSMOD_MusicPlay();
}

void CUMXPlayerDlg::OnRadio4() 
{
	BASSMOD_MusicStop();
	BASSMOD_MusicSetPosition(MAKELONG(3,0));
	BASSMOD_MusicPlay();
}

void CUMXPlayerDlg::OnRadio5() 
{
	BASSMOD_MusicStop();
	BASSMOD_MusicSetPosition(MAKELONG(4,0));
	BASSMOD_MusicPlay();
}

void CUMXPlayerDlg::OnRadio6() 
{
	BASSMOD_MusicStop();
	BASSMOD_MusicSetPosition(MAKELONG(5,0));
	BASSMOD_MusicPlay();
}

void CUMXPlayerDlg::OnPlaybtn() 
{
	BASSMOD_MusicPlay();
	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_STOPBTN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(TRUE);

	radio1->EnableWindow(TRUE);
	radio2->EnableWindow(TRUE);
	radio3->EnableWindow(TRUE);
	radio4->EnableWindow(TRUE);
	radio5->EnableWindow(TRUE);
	radio6->EnableWindow(TRUE);
}

void CUMXPlayerDlg::OnPausebtn() 
{
	BASSMOD_MusicPause();
	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(TRUE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_STOPBTN))->EnableWindow(FALSE);

	radio1->EnableWindow(FALSE);
	radio2->EnableWindow(FALSE);
	radio3->EnableWindow(FALSE);
	radio4->EnableWindow(FALSE);
	radio5->EnableWindow(FALSE);
	radio6->EnableWindow(FALSE);
}

void CUMXPlayerDlg::OnStopbtn() 
{
	BASSMOD_MusicStop();
	((CButton*)GetDlgItem(IDC_STOPBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_PAUSEBTN))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_PLAYBTN))->EnableWindow(TRUE);

	radio1->EnableWindow(FALSE);
	radio2->EnableWindow(FALSE);
	radio3->EnableWindow(FALSE);
	radio4->EnableWindow(FALSE);
	radio5->EnableWindow(FALSE);
	radio6->EnableWindow(FALSE);
}

void CUMXPlayerDlg::OnTimer(UINT nIDEvent) 
{

	if(nIDEvent == 3549)
	{
		if(BASSMOD_MusicIsActive())
		{
			posrow=BASSMOD_MusicGetPosition();
			row=HIWORD(posrow)/10;
			pos=LOWORD(posrow);
			sprintf(musposBuf, "Position: %i, Row: %i, Order: %i", posrow, row, pos);
			musPos->SetWindowText(musposBuf);
		}
		else
		{
			musPos->SetWindowText("Not Opened");
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CUMXPlayerDlg::OnCheck1() 
{
		AfxMessageBox("Changes will be applied when you reopen the UMX file.", 0, 0);
}
