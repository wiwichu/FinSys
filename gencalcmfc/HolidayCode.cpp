// CHolidayCode.cpp : implementation file
//

#include "stdafx.h"
#include "gencalcmfc.h"
#include "HolidayCode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHolidayCode dialog


CHolidayCode::CHolidayCode(CWnd* pParent /*=NULL*/)
	: CDialog(CHolidayCode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHolidayCode)
	//}}AFX_DATA_INIT
}


CHolidayCode::CHolidayCode(CWnd* pParent, /*=NULL*/ CDB * DB_parm)
	: CDialog(CHolidayCode::IDD, pParent), cholicodeproc (DB_parm)
{

	if ((TotalCodes = new int ) == NULL)

	{

		return_state = return_err_ins_mem;
		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);


	}

	else
	{

		*TotalCodes = 0;

		DB_local = DB_parm;

		DB_local->InitDB();

	}
}

void CHolidayCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHolidayCode)
	DDX_Control(pDX, IDC_Edit_Codedescription, m_CodeDescription);
	DDX_Control(pDX, IDC_Edit_Code, m_NewCode);
	DDX_Control(pDX, UpdateCode, m_Update);
	DDX_Control(pDX, DeleteCode, m_Delete);
	DDX_Control(pDX, IDC_CHolidayCode, m_CHolidayCode);
	//}}AFX_DATA_MAP
}


BOOL CHolidayCode::Create( CWnd* pParentWnd) 
{

	return_BOOL = TRUE;

	return_BOOL = CDialog::Create(IDD, pParentWnd);

	DB_local->GetStatementHandle(&localhandles);

	return_state = Setholicodearray(TotalCodes);

	for (element_count = 0; element_count <
	  *TotalCodes; ++element_count)
	{
/*
		return_state = GetHoliCode(&local_holicode,element_count);
		m_CHolidayCode.AddString(local_holicode.code);
*/
		return_state = GetHoliCode(holicodehold,element_count);
		m_CHolidayCode.AddString(holicodehold);

	}
	
	return return_BOOL;

}

BEGIN_MESSAGE_MAP(CHolidayCode, CDialog)
	//{{AFX_MSG_MAP(CHolidayCode)
	ON_CBN_SELCHANGE(IDC_CHolidayCode, OnSelchangeCHolidayCode)
	ON_BN_CLICKED(UpdateCode, OnUpdateCode)
	ON_BN_CLICKED(DeleteCode, OnDeleteCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHolidayCode message handlers

void CHolidayCode::OnSelchangeCHolidayCode() 
{
	// TODO: Add your control notification handler code here

	int LBPos;
	LBPos = m_CHolidayCode.GetCurSel();
	m_CHolidayCode.GetLBText( LBPos, local_holicode.code);
	m_NewCode.SetWindowText(local_holicode.code);

	return_state = GetHoliCode(&local_holicode,
		local_holicode.code);

	
	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

	}
	else
	{
	
		m_CodeDescription.SetWindowText(local_holicode.description);

	}


}

void CHolidayCode::OnUpdateCode() 
{
	// TODO: Add your control notification handler code here


	m_NewCode.GetWindowText( local_holicode.code,sizeof(local_holicode.code));
	m_CodeDescription.GetWindowText(local_holicode.description,
		sizeof(local_holicode.description));

	return_state = SetHoliCode(local_holicode);

	
	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

	}
	else
	{
		return_state = Setholicodearray(TotalCodes);

		m_CHolidayCode.ResetContent();


		for (element_count = 0; element_count <
		*TotalCodes; ++element_count)
		{
/*
			return_state = GetHoliCode(&local_holicode,element_count);
			m_CHolidayCode.AddString(local_holicode.code);
*/
			return_state = GetHoliCode(holicodehold,element_count);
			m_CHolidayCode.AddString(holicodehold);

		}
	}
	
}

void CHolidayCode::OnDeleteCode() 
{
	// TODO: Add your control notification handler code here

	return_state = DeleteHoliCode(local_holicode);
	
	if (return_state != return_success)
	{

		errtext(return_state, err_msg);

		::MessageBox(NULL,err_msg,"",MB_OK);

	}
	else
	{
		return_state = Setholicodearray(TotalCodes);

		m_CHolidayCode.ResetContent();


		for (element_count = 0; element_count <
		*TotalCodes; ++element_count)
		{
/*
			return_state = GetHoliCode(&local_holicode,element_count);
			m_CHolidayCode.AddString(local_holicode.code);
*/
			return_state = GetHoliCode(holicodehold,element_count);
			m_CHolidayCode.AddString(holicodehold);
		}
	}
	
}
