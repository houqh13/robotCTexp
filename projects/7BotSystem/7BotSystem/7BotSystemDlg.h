
// 7BotSystemDlg.h : ͷ�ļ�
//

#pragma once

#include "Arm7Bot.h"
#include "ComRcvThread.h"
#include "Define.h"
#include "SerialDlg.h"


// CMy7BotSystemDlg �Ի���
class CMy7BotSystemDlg : public CDialogEx
{
// ����
public:
	CMy7BotSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY7BOTSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComRcvThread *m_thCom[2];
	CSerialDlg *m_dlgCom[2];
	bool m_bMoveFinish[2];
	bool m_bReverse;
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonOpenCom3();
	afx_msg void OnBnClickedButtonOpenCom4();
	afx_msg void OnBnClickedButtonCloseCom3();
	afx_msg void OnBnClickedButtonCloseCom4();
	afx_msg LRESULT OnComError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnComSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMoveFinish(WPARAM wParam, LPARAM lParam);

private:
	Arm7Bot arm;
	PVector center;
	double radius;
	double angle;
	double delta;
	int calculate();
};
