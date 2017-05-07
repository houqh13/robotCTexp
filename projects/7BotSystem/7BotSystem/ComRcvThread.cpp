// CComRcvThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "ComRcvThread.h"
#include "define.h"

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <string>


// CComRcvThread

IMPLEMENT_DYNCREATE(CComRcvThread, CWinThread)

CComRcvThread::CComRcvThread()
	: m_hCom(INVALID_HANDLE_VALUE)
	, m_sCom("")
	, m_pSerialDlg(NULL)
{
}

CComRcvThread::CComRcvThread(CString comName)
	: m_hCom(INVALID_HANDLE_VALUE)
	, m_sCom(comName)
	, m_pSerialDlg(NULL)
{
}

CComRcvThread::~CComRcvThread()
{
}

BOOL CComRcvThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��

	// �򿪴���
	m_hCom = CreateFile(m_sCom, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_COMERROR, (int)(void *)this, NULL);
		return TRUE;
	}

	// ���ô���
	SetupComm(m_hCom, 256, 256);		// ��������С
	DCB dcb;
	GetCommState(m_hCom, &dcb);
	dcb.BaudRate = CBR_115200;			// ������
	dcb.ByteSize = 8;					// ����λ
	dcb.Parity = NOPARITY;				// У��λ
	dcb.StopBits = ONESTOPBIT;			// ֹͣλ
	SetCommState(m_hCom, &dcb);
	COMMTIMEOUTS timeouts;				// ��ʱ
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	SetCommTimeouts(m_hCom, &timeouts);
	PurgeComm(m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR);		// ��ջ�����
	

	// �򿪴������������Ϣ
	if (m_pSerialDlg == NULL)
	{
		m_pSerialDlg = new CSerialDlg();
		m_pSerialDlg->Create(IDD_SERIAL_DIALOG);
	}
  	m_pSerialDlg->ShowWindow(SW_SHOW);
	AfxGetApp()->m_pMainWnd->PostMessage(WM_COMSUCCESS, (int)(void *)this, NULL);

	return TRUE;
}

int CComRcvThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����

	// �رմ���
	if (m_pSerialDlg != NULL)
	{
		delete m_pSerialDlg;
	}

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CComRcvThread, CWinThread)
	ON_THREAD_MESSAGE(WM_CLOSETHREAD, OnCloseThread)
	ON_THREAD_MESSAGE(WM_RECEIVE, OnReceive)
END_MESSAGE_MAP()


// CComRcvThread ��Ϣ�������


void CComRcvThread::OnCloseThread(WPARAM wParam, LPARAM lParam)
{
	AfxEndThread(0);
}


void CComRcvThread::OnReceive(WPARAM wParam, LPARAM lParam)
{
	char readBuffer[256];
	DWORD readBytes;

	if (ReadFile(m_hCom, readBuffer, strlen(readBuffer), &readBytes, NULL))
	{
		CString str = _T("");
		for (int i = 0; i < strlen(readBuffer); i++)
		{
			if (readBuffer[i] == (char)0xFE)
			{
				// TODO...
			}
			else if (readBuffer[i] < 0)
			{
				break;
			}
			str += readBuffer[i];
		}
		m_pSerialDlg->m_sText += str;
		m_pSerialDlg->UpdateData(FALSE);
		if (m_pSerialDlg->m_bAutoScroll)
		{
			//(CEdit *)(m_pSerialDlg->GetDlgItem(IDC_EDIT_TEXT));
		}
	}
}

