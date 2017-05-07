// SerialDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "SerialDlg.h"
#include "afxdialogex.h"


// CSerialDlg 对话框

IMPLEMENT_DYNAMIC(CSerialDlg, CDialogEx)

CSerialDlg::CSerialDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerialDlg::IDD, pParent)
	, m_sText(_T(""))
	, m_bAutoScroll(true)
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
	DDX_Control(pDX, IDC_BUTTON_AUTOSCROLL, m_cAutoScroll);
}


BEGIN_MESSAGE_MAP(CSerialDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AUTOSCROLL, &CSerialDlg::OnBnClickedButtonAutoScroll)
END_MESSAGE_MAP()


// CSerialDlg 消息处理程序


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
