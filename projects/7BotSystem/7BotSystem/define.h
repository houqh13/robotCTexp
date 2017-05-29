
// define.h
// 项目中所有自定义宏定义

#pragma once

#include "PVector.h"
#include "stdafx.h"


// Arm7Bot 参数


// 常数
#define SERVO_NUM		7
#define PI				3.14159265358979323846
#define HALF_PI			3.14159265358979323846 / 2

// 机械臂长度参数
#define LENGTH_A		120.00
#define LENGTH_B		40.00
#define LENGTH_C		198.50
#define LENGTH_D		30.05
#define LENGTH_E		77.80
#define LENGTH_F		22.10
#define LENGTH_G		12.00
#define LENGTH_H		29.42

// 图像标定参数
#define DELTA			26.105
#define ALPHATAN		0.87118

// 7BotSystem 自定义消息列表


// 主线程控制消息
#define WM_CLOSETHREAD		WM_USER + 0x01
#define WM_RECEIVE			WM_USER + 0x02
#define WM_MOVEANGLE		WM_USER + 0x03
#define WM_FRESHFRAME		WM_USER + 0x04
#define WM_SAVEFRAME		WM_USER + 0x05
//#define WM_GETINITPOS		WM_USER + 0x06

// 工作线程通知消息
#define WM_COMERROR			WM_USER + 0x11
#define WM_COMSUCCESS		WM_USER + 0x12
#define WM_MOVEFINISH		WM_USER + 0x13
#define WM_NEXTSTEP			WM_USER + 0x14
#define WM_ADJUST			WM_USER + 0x15