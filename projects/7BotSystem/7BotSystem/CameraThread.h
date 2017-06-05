#pragma once

#include <opencv.hpp>

using namespace cv;
using namespace std;

// CCameraThread

class CCameraThread : public CWinThread
{
	DECLARE_DYNCREATE(CCameraThread)

protected:
	CCameraThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCameraThread();

public:
	CCameraThread(int camID);
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	Mat frame;
	Mat result;
	VideoCapture capture;
	VideoWriter video;
	RotatedRect blackRect;
	RotatedRect whiteRect;
	RotatedRect blackInitRect;
	RotatedRect whiteInitRect;
	CStdioFile txtFile;
	afx_msg void OnCloseThread(WPARAM wParam, LPARAM lParam);
	afx_msg void OnFreshFrame(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSaveFrame(WPARAM wParam, LPARAM lParam);
	void mark(bool fit, bool init);

	double delta[4];
	int iterCount;
};


