#pragma once
#include "afxwin.h"


// CSerialDlg �Ի���

class CSerialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialDlg)

public:
	CSerialDlg(CString title, CWnd* pParent = NULL);
	virtual ~CSerialDlg();

// �Ի�������
	enum { IDD = IDD_SERIAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_sTitle;
	CString m_sText;
	CEdit m_cText;
	bool m_bAutoScroll;
	CPoint m_nScroll;
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnBnClickedButtonAutoScroll();
};
