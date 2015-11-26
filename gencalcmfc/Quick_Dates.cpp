// Quick_Dates.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "Quick_Dates.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Quick_Dates dialog


Quick_Dates::Quick_Dates(CWnd* pParent /*=NULL*/)
	: CDialog(Quick_Dates::IDD, pParent)
{
	//{{AFX_DATA_INIT(Quick_Dates)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Quick_Dates::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Quick_Dates)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Quick_Dates, CDialog)
	//{{AFX_MSG_MAP(Quick_Dates)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Quick_Dates message handlers
