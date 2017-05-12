// CameraThread.cpp : 实现文件
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "CameraThread.h"
#include "Define.h"

cv::Mat frame;
cv::VideoCapture capture(0);

// CCameraThread

IMPLEMENT_DYNCREATE(CCameraThread, CWinThread)

CCameraThread::CCameraThread()
	//: capture(0)
{
}

CCameraThread::CCameraThread(int camID)
	//: capture(camID)
{
}

CCameraThread::~CCameraThread()
{
}

BOOL CCameraThread::InitInstance()
{
	// TODO: 在此执行任意逐线程初始化
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);
	capture >> frame;
	
	return TRUE;
}

int CCameraThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCameraThread, CWinThread)
	ON_THREAD_MESSAGE(WM_CLOSETHREAD, OnCloseThread)
	ON_THREAD_MESSAGE(WM_FRESHFRAME, OnFreshFrame)
	ON_THREAD_MESSAGE(WM_SAVEFRAME, OnSaveFrame)
END_MESSAGE_MAP()


// CCameraThread 消息处理程序


void CCameraThread::OnCloseThread(WPARAM wParam, LPARAM lParam)
{
	AfxEndThread(0);
}


void CCameraThread::OnFreshFrame(WPARAM wParam, LPARAM lParam)
{
	//capture >> frame;
	//cv::imshow("camera", frame);
}


void CCameraThread::OnSaveFrame(WPARAM wParam, LPARAM lParam)
{
	Sleep(2000);

	capture >> frame;
	capture >> frame;
	capture >> frame;
	std::string road = "C:/Users/houqh13/Documents/Arduino/Almighty/robotCTexp/outputs/frame/"
		+ std::to_string(lParam) + ".jpg";
	cv::imwrite(road, frame);
}