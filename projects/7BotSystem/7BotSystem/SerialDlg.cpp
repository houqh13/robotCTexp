// SerialDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "afxdialogex.h"
#include "Define.h"
#include "SerialDlg.h"


// CSerialDlg �Ի���

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


// CSerialDlg ��Ϣ�������


BOOL CSerialDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(m_sTitle);
	this->GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE, MF_DISABLED);		// ���ùرհ�ť

	return true;
}


void CSerialDlg::OnBnClickedButtonAutoScroll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
