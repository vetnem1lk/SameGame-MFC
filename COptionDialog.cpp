// COptionDialog.cpp: файл реализации
//

#include "pch.h"
#include "SameGame.h"
#include "COptionDialog.h"
#include "afxdialogex.h"


// Диалоговое окно COptionDialog

IMPLEMENT_DYNAMIC(COptionDialog, CDialog)

COptionDialog::COptionDialog(bool bRowColumn, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_OPTIONS, pParent)
	, m_nValue1(0)
	, m_nValue2(0)
	, m_bRowColumnDialog(bRowColumn)
{

}

COptionDialog::~COptionDialog()
{
}

void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT_1, m_ctrlStaticText1);
	DDX_Control(pDX, IDC_STATIC_TEXT_2, m_ctrlStaticText2);
	DDX_Text(pDX, IDC_EDIT_VALUE_1, m_nValue1);
	DDX_Text(pDX, IDC_EDIT_VALUE_2, m_nValue2);
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULTS, &COptionDialog::OnBnClickedButtonDefaults)
END_MESSAGE_MAP()


// Обработчики сообщений COptionDialog


void COptionDialog::OnBnClickedButtonDefaults()
{
	if (m_bRowColumnDialog)
		m_nValue1 = m_nValue2 = 15; // board size 15x15
	else
		m_nValue1 = m_nValue2 = 35; // block size 35x35

	// Update element parameters to new values
	UpdateData(false);
}

BOOL COptionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (m_bRowColumnDialog)
	{
		//  update the title of the dialog box
		SetWindowText(_T("Update number of blocks"));
		//  update "Static Text" elements
		m_ctrlStaticText1.SetWindowText(_T("Rows"));
		m_ctrlStaticText2.SetWindowText(_T("Columns"));
	}
	else
	{
		SetWindowText(_T("Update block size"));
		m_ctrlStaticText1.SetWindowText(_T("Block width"));
		m_ctrlStaticText2.SetWindowText(_T("Block height"));
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
