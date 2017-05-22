// CameraThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "7BotSystem.h"
#include "CameraThread.h"
#include "Define.h"


// CCameraThread

IMPLEMENT_DYNCREATE(CCameraThread, CWinThread)

CCameraThread::CCameraThread()
{
}

CCameraThread::CCameraThread(int camID)
{
}

CCameraThread::~CCameraThread()
{
}

BOOL CCameraThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	capture.open(CV_CAP_DSHOW);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	Sleep(2000);
	capture >> frame;
	result.create(frame.size(), frame.type());
	
	return TRUE;
}

int CCameraThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCameraThread, CWinThread)
	ON_THREAD_MESSAGE(WM_CLOSETHREAD, OnCloseThread)
	ON_THREAD_MESSAGE(WM_FRESHFRAME, OnFreshFrame)
	ON_THREAD_MESSAGE(WM_SAVEFRAME, OnSaveFrame)
END_MESSAGE_MAP()


// CCameraThread ��Ϣ�������


void CCameraThread::OnCloseThread(WPARAM wParam, LPARAM lParam)
{
	AfxEndThread(0);
}


void CCameraThread::OnFreshFrame(WPARAM wParam, LPARAM lParam)
{
	//capture >> frame;

	//mark();

	//imshow("camera", result);
	//waitKey(30);
}


void CCameraThread::OnSaveFrame(WPARAM wParam, LPARAM lParam)
{
	Sleep(2000);

	capture >> frame;
	capture >> frame;
	std::string road = "C:/Users/houqh13/Documents/Arduino/Almighty/robotCTexp/outputs/frame/"
		+ std::to_string(lParam) + ".jpg";
	imwrite(road, frame);
}


// CCameraThread ͼ�������


void CCameraThread::mark()
{
	Mat edge, gray;
	cvtColor(frame, gray, CV_BGR2GRAY);
	Canny(gray, edge, 8, 20);
	result = Scalar::all(0);
	frame.copyTo(result, edge);
}