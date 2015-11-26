// BondCalcScreen.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "BondCalcScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBondCalcScreen dialog


CBondCalcScreen::CBondCalcScreen(CWnd* pParent /*=NULL*/)
	: CDialog(CBondCalcScreen::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBondCalcScreen)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBondCalcScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBondCalcScreen)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBondCalcScreen, CDialog)
	//{{AFX_MSG_MAP(CBondCalcScreen)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBondCalcScreen message handlers
