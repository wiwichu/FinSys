// BondCalc.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "BondCalc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BondCalc dialog


BondCalc::BondCalc(CWnd* pParent /*=NULL*/)
	: CDialog(BondCalc::IDD, pParent)
{
	//{{AFX_DATA_INIT(BondCalc)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BondCalc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BondCalc)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BondCalc, CDialog)
	//{{AFX_MSG_MAP(BondCalc)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BondCalc message handlers
