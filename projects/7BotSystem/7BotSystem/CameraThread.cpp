// CameraThread.cpp : 实现文件
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
	// TODO: 在此执行任意逐线程初始化
	capture.open(CV_CAP_DSHOW);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 1280);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

	string road = "C:/Users/houqh13/Documents/Arduino/Almighty/robotCTexp/outputs/capture.avi";
	video.open(road, CV_FOURCC('M','P','4','2'), 10, Size(1280, 720), true);

	Sleep(1000);
	capture >> frame;
	result.create(frame.size(), frame.type());
	
	return TRUE;
}

int CCameraThread::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	capture.release();
	destroyWindow("camera");

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
	capture >> frame;
	mark(wParam, lParam);

	imshow("camera", result);
	video << result;
	waitKey(1);
}


void CCameraThread::OnSaveFrame(WPARAM wParam, LPARAM lParam)
{
	capture >> frame;
	mark(true, false);

	//string road = "C:/Users/houqh13/Documents/Arduino/Almighty/robotCTexp/outputs/frame/"
	//	+ to_string(lParam) + ".jpg";
	//imwrite(road, result);

	double bx = blackRect.center.x - blackInitRect.center.x;
	double by = blackRect.center.y - blackInitRect.center.y;
	double dth = atan2(blackRect.center.y - whiteRect.center.y, blackRect.center.x - whiteRect.center.x)
		- atan2(blackInitRect.center.y - whiteInitRect.center.y, blackInitRect.center.x - whiteInitRect.center.x);
	double dd = max(blackRect.size.height, blackRect.size.width) / max(blackInitRect.size.height, blackInitRect.size.width);
	if (bx < 4 && bx > -4 && by < 4 && by > -4
		&& dth < 0.06 && dth > -0.06 && dd < 1.02 && dd > 0.98)
	{
		AfxGetApp()->m_pMainWnd->PostMessage(WM_NEXTSTEP, NULL, NULL);
	}
	else
	{
		delta[0] = bx;
		delta[1] = by;
		delta[2] = dth;
		delta[3] = dd;
		AfxGetApp()->m_pMainWnd->PostMessage(WM_ADJUST, (WPARAM)delta, NULL);
	}
}


// CCameraThread 图像处理程序


void CCameraThread::mark(bool fit, bool init)
{
	result = frame;

	if (fit)
	{
		Mat smooth, gray, binary;
		blur(frame, smooth, Size(3, 3));
		cvtColor(smooth, gray, COLOR_BGR2GRAY);
		threshold(gray, binary, 100, 255, CV_THRESH_BINARY);

		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(binary, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
		int select = 0;
		double area, perimeter, ratio, minRatio = 10;
		for (int i = 0; i < contours.size(); i++)
		{
			area = contourArea(contours.at(i));
			perimeter = arcLength(contours.at(i), true);
			if (area != 0)
			{
				ratio = perimeter * perimeter / (4 * 3.1415926536 * area);
				if (area > 12000 && ratio > 0 && ratio < minRatio)
				{
					select = i;
					minRatio = ratio;
				}
			}
		}
	
		if (init)
		{
			blackInitRect = fitEllipse(contours.at(select));
		}
		else
		{
			blackRect = fitEllipse(contours.at(select));
		}

		minRatio = 10;
		for (int i = hierarchy[select][2]; ; i = hierarchy[i][0])
		{
			if (i == -1)
			{
				break;
			}
			area = contourArea(contours.at(i));
			perimeter = arcLength(contours.at(i), true);
			if (area != 0)
			{
				ratio = perimeter * perimeter / (4 * 3.1415926536 * area);
				if (area > 2000 && ratio > 0 && ratio < minRatio)
				{
					select = i;
					minRatio = ratio;
				}
			}
		}

		if (init)
		{
			whiteInitRect = fitEllipse(contours.at(select));
		}
		else
		{
			whiteRect = fitEllipse(contours.at(select));
		}
	}
	
	ellipse(result, blackInitRect, Scalar(0, 255, 0), 3);
	ellipse(result, whiteInitRect, Scalar(0, 255, 0), 3);
	ellipse(result, blackRect, Scalar(0, 0, 255), 3);
	ellipse(result, whiteRect, Scalar(0, 0, 255), 3);
}