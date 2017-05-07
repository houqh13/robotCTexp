// ComRcvThread.cpp : 实现文件
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "ComRcvThread.h"
#include "define.h"

#include <fcntl.h>
#include <io.h>
#include <iostream>


// ComRcvThread

IMPLEMENT_DYNCREATE(ComRcvThread, CWinThread)

ComRcvThread::ComRcvThread()
	: hCom(INVALID_HANDLE_VALUE)
	, strCom("")
{
}

ComRcvThread::ComRcvThread(CString comName)
	: hCom(INVALID_HANDLE_VALUE)
	, strCom(comName)
{
}

ComRcvThread::~ComRcvThread()
{
}

BOOL ComRcvThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化

	// 打开串口
	hCom = CreateFile(strCom, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hCom == INVALID_HANDLE_VALUE)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_COMERROR, (int)(void *)this, NULL);
		//return TRUE;
	}

	// 打开控制台输出串口信息
	AllocConsole();
	SetConsoleTitle(_T("Serial Monitor on ") + strCom);
	*stdin = *(_fdopen(_open_osfhandle((intptr_t)::GetStdHandle(STD_INPUT_HANDLE), _O_TEXT), "r"));
	*stdout = *( _fdopen(_open_osfhandle((intptr_t)::GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT), "wt"));
	std::ios_base::sync_with_stdio();

	return TRUE;
}

int ComRcvThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理

	// 关闭控制台
	FreeConsole();

	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(ComRcvThread, CWinThread)
	ON_THREAD_MESSAGE(WM_CLOSETHREAD, OnCloseThread)
END_MESSAGE_MAP()


// ComRcvThread 消息处理程序


void ComRcvThread::OnCloseThread(WPARAM wParam, LPARAM lParam)
{
	AfxEndThread(0);
}