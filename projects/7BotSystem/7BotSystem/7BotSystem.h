
// 7BotSystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy7BotSystemApp:
// �йش����ʵ�֣������ 7BotSystem.cpp
//

class CMy7BotSystemApp : public CWinApp
{
public:
	CMy7BotSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy7BotSystemApp theApp;