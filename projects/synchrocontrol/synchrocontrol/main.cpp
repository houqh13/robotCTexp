#include <opencv.hpp>
#include <stdio.h>
#include <string>
#include <Windows.h>

using namespace cv;
using namespace std;

int main() {
	// 定义串口句柄
	HANDLE hCom3 = INVALID_HANDLE_VALUE;
	HANDLE hCom4 = INVALID_HANDLE_VALUE;

	// 创建串口句柄
	// 设置串口访问类型为可读可写, 串口打开方式为同步I/O
	hCom3 = CreateFile(L"Com3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	hCom4 = CreateFile(L"Com4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	// 检测串口连接情况
	if (hCom3 == INVALID_HANDLE_VALUE)
	{
		int errorCode = GetLastError();
		printf("Open Com3 failed with error %d.\n", errorCode);
		return -1;
	}
	else
	{
		printf("Open Com3 success!\n");
	}
	if (hCom4 == INVALID_HANDLE_VALUE)
	{
		int errorCode = GetLastError();
		printf("Open Com4 failed with error %d.\n", errorCode);
		return -1;
	}
	else
	{
		printf("Open Com4 success!\n");
	}

	// 配置串口
	SetupComm(hCom3, 1024, 1024);		// 缓冲区大小
	SetupComm(hCom4, 1024, 1024);
	DCB dcb;
	GetCommState(hCom3, &dcb);
	dcb.BaudRate = CBR_115200;			// 波特率
	dcb.ByteSize = 8;					// 数据位
	dcb.Parity = NOPARITY;				// 校验位
	dcb.StopBits = ONESTOPBIT;			// 停止位
	SetCommState(hCom3, &dcb);
	SetCommState(hCom4, &dcb);

	// 清空缓冲区
	PurgeComm(hCom3, PURGE_RXCLEAR | PURGE_TXCLEAR);
	PurgeComm(hCom4, PURGE_RXCLEAR | PURGE_TXCLEAR);

	//char *writeBuffer[2] = {"254", "1"};				// 待发指令
	char writeBuffer[2] = {0xFE, 0x2};
	DWORD writeBytes;
	char readBuffer3[256];
	char readBuffer4[256];
	DWORD readBytes;
	
	Mat frame;							// 图像缓存
	VideoCapture capture(0);			// 连接摄像头

	// 主循环
	// 流程: 接收机械臂返回指令(上一步运动结束), 采集图像, 判断运动是否结束, 若结束则退出循环, 若未结束, 则发送下一步运动指令, 并进入下一循环
	while (true)
	{
		// 接收指令
		while (true)
		{
			if (!ReadFile(hCom3, readBuffer3, strlen(readBuffer3), &readBytes, NULL))
			{
				int errorCode = GetLastError();
				printf("Read Com3 failed with error %d.\n", errorCode);
				return -1;
			}
			if (readBuffer3[0] == 0xFE && readBuffer3[1] == 0x3)
			{
				break;
			}
		}
		while (true)
		{
			if (!ReadFile(hCom4, readBuffer4, strlen(readBuffer4), &readBytes, NULL))
			{
				int errorCode = GetLastError();
				printf("Read Com4 failed with error %d.\n", errorCode);
				return -1;
			}
			if (readBuffer4[0] == 0xFE && readBuffer4[1] == 0x3)
			{
				break;
			}
		}

		Sleep(500);						// 待机械臂稳定

		// 采集图像
		capture >> frame;
		imshow("test", frame);

		// 判断运动是否结束
		ReadFile(hCom3, readBuffer3, strlen(readBuffer3), &readBytes, NULL);
		if (readBuffer4[0] == 0xFE && readBuffer4[1] == 0x4)
		{
			break;
		}

		// 发送指令
		if (!WriteFile(hCom3, writeBuffer, strlen(writeBuffer), &writeBytes, NULL))
		{
			int errorCode = GetLastError();
			printf("Write Com3 failed with error %d.\n", errorCode);
			return -1;
		}
		if (!WriteFile(hCom4, writeBuffer, strlen(writeBuffer), &writeBytes, NULL))
		{
			int errorCode = GetLastError();
			printf("Write Com4 failed with error %d.\n", errorCode);
			return -1;
		}
	}
	

	// 发送指令
	/*for (int i = 0; i < 2; i++)
	{
		if (!WriteFile(hCom3, writeBuffer[i], strlen(writeBuffer[i]), &writeBytes, NULL))
		{
			int errorCode = GetLastError();
			printf("Write Com3 failed with error %d.\n", errorCode);
			return -1;
		}
		Sleep(1000);
	}*/

	// 去除后半部分无用字符
	/*string str = "";
	for (int i = 0; i < strlen(readBuffer); i++)
	{
		if (readBuffer[i] < 0)
		{
			break;
		}
		str += readBuffer[i];
	}
	printf(str.c_str());*/

	// 关闭串口
	CloseHandle(hCom3);
	CloseHandle(hCom4);

	return 0;
}
