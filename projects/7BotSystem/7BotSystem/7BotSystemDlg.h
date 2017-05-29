
// 7BotSystemDlg.h : 头文件
//

#pragma once

#include "Arm7Bot.h"
#include "CameraThread.h"
#include "ComRcvThread.h"
#include "Define.h"
#include "SerialDlg.h"


// CMy7BotSystemDlg 对话框
class CMy7BotSystemDlg : public CDialogEx
{
// 构造
public:
	CMy7BotSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY7BOTSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComRcvThread *m_thCom[2];
	CSerialDlg *m_dlgCom[2];
	CCameraThread *m_thCamera;
	bool m_bMoveFinish[2];
	bool m_bReverse;
	bool m_bFocusing;
	bool m_bScanning;
	afx_msg void OnBnClickedButtonOpenCom3();
	afx_msg void OnBnClickedButtonOpenCom4();
	afx_msg void OnBnClickedButtonCloseCom3();
	afx_msg void OnBnClickedButtonCloseCom4();
	afx_msg void OnBnClickedButtonOpenCamera();
	afx_msg void OnBnClickedButtonCloseCamera();
	afx_msg void OnBnClickedButtonFocus();
	afx_msg void OnBnClickedButtonStart();
	afx_msg LRESULT OnComError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnComSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnMoveFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAdjust(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNextStep(WPARAM wParam, LPARAM lParam);

private:
	Arm7Bot arm;
	PVector center;
	double radius;
	double angle;
	double delta;
	PVector j6;
	PVector vec56;
	PVector vec67;
	int calculate();
};
