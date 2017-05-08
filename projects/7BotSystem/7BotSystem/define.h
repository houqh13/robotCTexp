
// define.h
// 项目中所有自定义宏定义

#pragma once

#include "stdafx.h"


// 7BotSystem 自定义消息列表


// 主线程控制消息
#define WM_CLOSETHREAD		WM_USER + 0x01
#define WM_RECEIVE			WM_USER + 0x02

// 工作线程通知消息
#define WM_COMERROR			WM_USER + 0x10
#define WM_COMSUCCESS		WM_USER + 0x11
#define WM_BUFFERSHOW		WM_USER + 0x12