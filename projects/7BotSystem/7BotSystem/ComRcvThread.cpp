// CComRcvThread.cpp : 实现文件
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "7BotSystemDlg.h"
#include "ComRcvThread.h"
#include "Define.h"

#include <string>


// CComRcvThread

IMPLEMENT_DYNCREATE(CComRcvThread, CWinThread)

CComRcvThread::CComRcvThread()
	: m_hCom(INVALID_HANDLE_VALUE)
	, m_sCom("")
	, m_bMoveFinish(true)
{
}

CComRcvThread::CComRcvThread(CString comName, int ID)
	: m_hCom(INVALID_HANDLE_VALUE)
	, m_sCom(comName)
	, m_nID(ID)
	, m_bMoveFinish(true)
{
}

CComRcvThread::~CComRcvThread()
{
}

BOOL CComRcvThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化

	// 打开串口
	m_hCom = CreateFile(m_sCom, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hCom == INVALID_HANDLE_VALUE)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_COMERROR, m_nID, NULL);
		return TRUE;
	}

	// 配置串口
	SetupComm(m_hCom, 1024, 1024);		// 缓冲区大小
	DCB dcb;
	GetCommState(m_hCom, &dcb);
	dcb.BaudRate = CBR_115200;			// 波特率
	dcb.ByteSize = 8;					// 数据位
	dcb.Parity = NOPARITY;				// 校验位
	dcb.StopBits = ONESTOPBIT;			// 停止位
	SetCommState(m_hCom, &dcb);
	COMMTIMEOUTS timeouts;				// 超时
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	SetCommTimeouts(m_hCom, &timeouts);
	PurgeComm(m_hCom, PURGE_RXCLEAR | PURGE_TXCLEAR);		// 清空缓冲区
	
	AfxGetApp()->m_pMainWnd->PostMessage(WM_COMSUCCESS, m_nID, NULL);

	return TRUE;
}

int CComRcvThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CComRcvThread, CWinThread)
	ON_THREAD_MESSAGE(WM_CLOSETHREAD, OnCloseThread)
	ON_THREAD_MESSAGE(WM_RECEIVE, OnReceive)
	ON_THREAD_MESSAGE(WM_MOVEANGLE, OnMoveAngle)
END_MESSAGE_MAP()


// CComRcvThread 消息处理程序


void CComRcvThread::OnCloseThread(WPARAM wParam, LPARAM lParam)
{
	CloseHandle(m_hCom);
	AfxEndThread(0);
}


void CComRcvThread::OnReceive(WPARAM wParam, LPARAM lParam)
{
	char readBuffer[1024];
	DWORD readBytes;

	if (ReadFile(m_hCom, readBuffer, strlen(readBuffer), &readBytes, NULL))
	{
		strcpy(m_sReadBuffer, "");
		int i = 0;
		for (int j = 0; j < strlen(readBuffer); j++)
		{
			if (readBuffer[j] == (char)0xFD)
			{
				j++;
				if (readBuffer[j++] == (char)0x01)
				{
					m_bMoveFinish = true;
					
					DWORD writeBytes;
					m_sWriteBuffer[0] = (char)0xFE;
					m_sWriteBuffer[1] = (char)0x01;
					if (!WriteFile(m_hCom, m_sWriteBuffer, 3, &writeBytes, NULL))
					{
						AfxMessageBox(m_sCom + _T("发送失败！"));
					}

					AfxGetApp()->m_pMainWnd->PostMessage(WM_MOVEFINISH, m_nID, NULL);
				}
				// TODO...
			}
			else if (readBuffer[j] < 0)
			{
				break;
			}
			m_sReadBuffer[i] = readBuffer[j];
			i++;
		}
		m_sReadBuffer[i] = 0;
		COPYDATASTRUCT cds;
		cds.dwData = 0;
		cds.cbData = strlen(m_sReadBuffer);
		cds.lpData = (void *)m_sReadBuffer;
		((CMy7BotSystemDlg *)AfxGetApp()->m_pMainWnd)->m_dlgCom[m_nID]->SendMessage(WM_COPYDATA, (WPARAM)this->m_hThread, (LPARAM)&cds);
	}
}


void CComRcvThread::OnMoveAngle(WPARAM wParam, LPARAM lParam)
{
	Sleep(5000);

	double angles[SERVO_NUM];
	DWORD writeBytes;
	m_sWriteBuffer[0] = (char)0xFE;
	m_sWriteBuffer[1] = (char)0x09;
	for (int i = 0; i < SERVO_NUM; i++)
	{
		angles[i] = *(double *)(wParam + i * sizeof(double));
		m_sWriteBuffer[2 * i + 2] = (int)(angles[i] * 1000 / PI) / 128;
		m_sWriteBuffer[2 * i + 3] = (int)(angles[i] * 1000 / PI) % 128;
	}

	m_bMoveFinish = false;

	if (!WriteFile(m_hCom, m_sWriteBuffer, 2 * SERVO_NUM + 2, &writeBytes, NULL))
	{
		AfxMessageBox(m_sCom + _T("发送失败！"));
	}
}
