#pragma once
#include "afxwin.h"


// CSerialDlg �Ի���

class CSerialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialDlg)

public:
	CSerialDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerialDlg();

// �Ի�������
	enum { IDD = IDD_SERIAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sText;
	CEdit m_cText;
	bool m_bAutoScroll;
	CButton m_cAutoScroll;
	afx_msg void OnBnClickedButtonAutoScroll();
};
