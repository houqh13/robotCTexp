
// define.h
// ��Ŀ�������Զ���궨��

#pragma once

#include "PVector.h"
#include "stdafx.h"


// Arm7Bot ����


// ����
#define SERVO_NUM		7
#define PI				3.14159265358979323846
#define HALF_PI			3.14159265358979323846 / 2

// ��е�۳��Ȳ���
#define LENGTH_A		120.00
#define LENGTH_B		40.00
#define LENGTH_C		198.50
#define LENGTH_D		30.05
#define LENGTH_E		77.80
#define LENGTH_F		22.10
#define LENGTH_G		12.00
#define LENGTH_H		29.42

// ͼ��궨����
#define DELTA			26.105
#define ALPHATAN		0.87118

// 7BotSystem �Զ�����Ϣ�б�


// ���߳̿�����Ϣ
#define WM_CLOSETHREAD		WM_USER + 0x01
#define WM_RECEIVE			WM_USER + 0x02
#define WM_MOVEANGLE		WM_USER + 0x03
#define WM_FRESHFRAME		WM_USER + 0x04
#define WM_SAVEFRAME		WM_USER + 0x05
//#define WM_GETINITPOS		WM_USER + 0x06

// �����߳�֪ͨ��Ϣ
#define WM_COMERROR			WM_USER + 0x11
#define WM_COMSUCCESS		WM_USER + 0x12
#define WM_MOVEFINISH		WM_USER + 0x13
#define WM_NEXTSTEP			WM_USER + 0x14
#define WM_ADJUST			WM_USER + 0x15