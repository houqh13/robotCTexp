#pragma once
#include "afxwin.h"


// CSerialDlg 对话框

class CSerialDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerialDlg)

public:
	CSerialDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerialDlg();

// 对话框数据
	enum { IDD = IDD_SERIAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_sText;
	CEdit m_cText;
	bool m_bAutoScroll;
	CButton m_cAutoScroll;
	afx_msg void OnBnClickedButtonAutoScroll();
};
