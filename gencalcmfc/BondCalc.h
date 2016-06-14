/////////////////////////////////////////////////////////////////////////////
// BondCalc dialog

class BondCalc : public CDialog
{
// Construction
public:
	BondCalc(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BondCalc)
	enum { IDD = IDD_BondCalc };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BondCalc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BondCalc)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
