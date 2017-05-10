// SerialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "afxdialogex.h"
#include "Define.h"
#include "SerialDlg.h"


// CSerialDlg 对话框

IMPLEMENT_DYNAMIC(CSerialDlg, CDialogEx)

CSerialDlg::CSerialDlg(CString title, CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialDlg::IDD, pParent)
	, m_sTitle(title)
	, m_sText(_T(""))
	, m_bAutoScroll(true)
	, m_nScroll((0, 0))
{

}

CSerialDlg::~CSerialDlg()
{
}


void CSerialDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TEXT, m_sText);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_cText);
}


BEGIN_MESSAGE_MAP(CSerialDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AUTOSCROLL, &CSerialDlg::OnBnClickedButtonAutoScroll)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CSerialDlg 消息处理程序


BOOL CSerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_sTitle);
	this->GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_DISABLED);		// 禁用关闭按钮

	return true;
}


void CSerialDlg::OnBnClickedButtonAutoScroll()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bAutoScroll)
	{
		m_bAutoScroll = false;
		SetDlgItemText(IDC_BUTTON_AUTOSCROLL, _T("No Scroll"));
	}
	else
	{
		m_bAutoScroll = true;
		SetDlgItemText(IDC_BUTTON_AUTOSCROLL, _T("Auto Scroll"));
	}
}


BOOL CSerialDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (pCopyDataStruct->cbData > 0)
	{
		char *str = (char *)pCopyDataStruct->lpData;
		m_sText += str;

		if (m_bAutoScroll)
		{
			UpdateData(FALSE);
			m_cText.LineScroll(m_cText.GetLineCount());
		}
		else
		{
			m_nScroll.x = m_cText.GetScrollPos(SB_HORZ);
			m_nScroll.y = m_cText.GetScrollPos(SB_VERT);
			UpdateData(FALSE);
			m_cText.LineScroll(m_nScroll.y, m_nScroll.x);
		}
		Invalidate(FALSE);
	}

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
