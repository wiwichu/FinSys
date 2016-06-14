// Holquick.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "Holquick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHolquick dialog


CHolquick::CHolquick(CWnd* pParent /*=NULL*/)
	: CDialog(CHolquick::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHolquick)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHolquick::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHolquick)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHolquick, CDialog)
	//{{AFX_MSG_MAP(CHolquick)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHolquick message handlers
