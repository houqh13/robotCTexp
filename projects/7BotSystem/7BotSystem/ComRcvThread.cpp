// CComRcvThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "7BotSystemDlg.h"
#include "ComRcvThread.h"
#include "define.h"

#include <string>


// CComRcvThread

IMPLEMENT_DYNCREATE(CComRcvThread, CWinThread)

CComRcvThread::CComRcvThread()
	: m_hCom(INVALID_HANDLE_VALUE)
	, m_sCom("")
	, m_sBuffer("")
{
}

CComRcvThread::CComRcvThread(CString comName, int ID)
	: m_hCom(INVALID_HANDLE_VALUE)
	, m_sCom(comName)
	, m_sBuffer("")
	, m_nID(ID)
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
	
	AfxGetApp()->m_pMainWnd->PostMessage(WM_COMSUCCESS, (int)(void *)this, NULL);

	return TRUE;
}

int CComRcvThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����

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
		m_sBuffer = "";
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
			m_sBuffer += readBuffer[i];
		}
		((CMy7BotSystemDlg *)AfxGetApp()->m_pMainWnd)->m_dlgCom[m_nID]->PostMessage(WM_BUFFERSHOW, (WPARAM)m_sBuffer, strlen(m_sBuffer));
		//m_pSerialDlg->m_sText += str;
		//if (m_pSerialDlg->m_bAutoScroll)
		//{
		//	m_pSerialDlg->UpdateData(FALSE);
		//	m_pSerialDlg->m_cText.LineScroll(m_pSerialDlg->m_cText.GetLineCount());
		//}
		//else
		//{
		//	m_pSerialDlg->m_nScroll.x = m_pSerialDlg->m_cText.GetScrollPos(SB_HORZ);
		//	m_pSerialDlg->m_nScroll.y = m_pSerialDlg->m_cText.GetScrollPos(SB_VERT);
		//	m_pSerialDlg->UpdateData(FALSE);
		//	m_pSerialDlg->m_cText.LineScroll(m_pSerialDlg->m_nScroll.y, m_pSerialDlg->m_nScroll.x);
		//}
		//m_pSerialDlg->Invalidate();
	}
}

