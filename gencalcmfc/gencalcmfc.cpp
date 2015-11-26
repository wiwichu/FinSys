// gencalcmfc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "gencalcmfc.h"

#include "MainFrm.h"
//#include "FastDates.h"
//#include "RateCurvesScreen.h"
#include "BondCalculator.h"
#include "ChildFrm.h"
#include "gencalcmfcDoc.h"
#include "gencalcmfcView.h"
//#include "Holidays.h"
//#include "Holal.h"
//#include "Holquick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcApp

BEGIN_MESSAGE_MAP(CGencalcmfcApp, CWinApp)
	//{{AFX_MSG_MAP(CGencalcmfcApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_DATES_HOLIDAYS, OnHolidays)
	ON_COMMAND(ID_DATES_QUICKHOLIDAY, OnDatesQuickholiday)
	ON_COMMAND(ID_CALCULATOR_RATECURVES, OnCalculatorRatecurves)
	ON_COMMAND(ID_CALCULATOR_NEWBOND, OnCalculatorNewbond)
	ON_COMMAND(ID_HolidayCode, OnHolidayCode)
	ON_COMMAND(ID_CALCULATOR_FRNS, OnCalculatorFrns)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcApp construction

CGencalcmfcApp::CGencalcmfcApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGencalcmfcApp object

CGencalcmfcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcApp initialization

BOOL CGencalcmfcApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_GENCALTYPE,
		RUNTIME_CLASS(CGencalcmfcDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CGencalcmfcView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
//	db_type = db_odbc_type;
//	db_type = db_odbc_access_type;
//	db_type = db_internal_array_type;
//	DB_Local = new CDB(db_type);

//	DB_Local = new CDB();
/*
	if(!DB_Local->GetDBStat()) {

		return FALSE;

	}
*/	
//	DB_Local->SetODBCAccessType();
//
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGencalcmfcApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGencalcmfcApp commands

void CGencalcmfcApp::OnBondCalc() 
{
	// TODO: Add your command handler code here

	CBondCalcWnd* BondCalcWnd = new CBondCalcWnd;	
/*
	BondCalcWnd->LoadFrame(IDR_GENCALTYPE, 
							WS_TABSTOP | WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,  
							NULL, 
							NULL);
*/
//
	BondCalcWnd->Create(NULL, 
						NULL,
						WS_CHILD 
							| WS_TABSTOP 
							| WS_BORDER 
							| WS_CAPTION 
							| WS_SYSMENU
							| WS_MAXIMIZE
							| WS_MAXIMIZEBOX
							| WS_MINIMIZEBOX,  
						CFrameWnd::rectDefault, 
						NULL,
						NULL);
//
	// The window has been initialized, so show and update it.
	BondCalcWnd->ShowWindow(SW_SHOW);
	BondCalcWnd->UpdateWindow();

}

//BondCalcWnd()
//{
//
//}


void CGencalcmfcApp::OnHolidays()
{
	// TODO: Add your command handler code here

//	DB_Local->InitDB();
/*
	CHolidays* Holidays = new CHolidays(DB_Local);	

	Holidays->Create(NULL, 
						NULL,
						WS_CHILD 
							| WS_TABSTOP 
							| WS_BORDER 
							| WS_CAPTION 
							| WS_SYSMENU
							| WS_MAXIMIZE
							| WS_MAXIMIZEBOX
							| WS_MINIMIZEBOX,  
						CFrameWnd::rectDefault, 
						NULL,
						NULL);
	// The window has been initialized, so show and update it.
	Holidays->ShowWindow(SW_SHOW);
	Holidays->UpdateWindow();
*/
}

void CGencalcmfcApp::OnDatesQuickholiday() 
{
	BOOL return_BOOL;
	BOOL return_int;
	// TODO: Add your command handler code here

//	Quick_Dates * QD = new Quick_Dates;	
//	return_BOOL = QD->Create(IDD_Quick_Dates,NULL);
//	CHolCal* QD = new CHolCal;	

//	DB_Local->InitDB();

//	CHolCal* QD = new CHolCal(NULL, DB_Local);	
//	CFastDates* QD = new CFastDates(NULL, DB_Local);	
//	return_BOOL = QD->Create(NULL);
//	return_BOOL = Holidays->Create(IDD_QuickDates,NULL);
//	return_BOOL = QD->SetDB(DB_Local);

}

void CGencalcmfcApp::OnCalculatorRatecurves() 
{
	BOOL return_BOOL;
	BOOL return_int;
	// TODO: Add your command handler code here
/*
	DB_Local->InitDB();

	RateCurvesScreen * RCS = new RateCurvesScreen;	
	return_BOOL = RCS->Create(NULL);
*/	
}

void CGencalcmfcApp::OnCalculatorNewbond() 
{
	// TODO: Add your command handler code here
	BOOL return_BOOL;
	BOOL return_int;

//	DB_Local->InitDB();

//	CBondCalculator * CBC = new CBondCalculator(NULL, DB_Local);	
	CBondCalculator * CBC = new CBondCalculator(NULL);	
	return_BOOL = CBC->Create(NULL);
	
}

void CGencalcmfcApp::OnHolidayCode() 
{
	// TODO: Add your command handler code here
	BOOL return_BOOL;
	BOOL return_int;
/*
	DB_Local->InitDB();

	CHolidayCode * HoliCode = new CHolidayCode(NULL, DB_Local);	
	return_BOOL = HoliCode->Create(NULL);
*/	
}

void CGencalcmfcApp::OnCalculatorFrns() 
{
	// TODO: Add your command handler code here
	BOOL return_BOOL;
	BOOL return_int;
/*
	DB_Local->InitDB();

	CFRNCAlc * FRNC = new CFRNCAlc(NULL, DB_Local);	
	return_BOOL = FRNC->Create(NULL);
*/	
}
