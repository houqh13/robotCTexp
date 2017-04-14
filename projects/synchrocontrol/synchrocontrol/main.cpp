#include <stdio.h>
#include <string>
#include <Windows.h>
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

	char *writeBuffer[2] = {"254", "1"};				// 待发指令
	DWORD writeBytes;
	char readBuffer[1024];
	DWORD readBytes;

	Sleep(7500);

	// 发送指令
	for (int i = 0; i < 3; i++)
	{
		if (!WriteFile(hCom3, writeBuffer[i], strlen(writeBuffer[i]), &writeBytes, NULL))
		{
			int errorCode = GetLastError();
			printf("Write Com3 failed with error %d.\n", errorCode);
			return -1;
		}
		Sleep(1000);
	}
	Sleep(500);

	// 接收返回信息
	if (!ReadFile(hCom3, readBuffer, strlen(readBuffer), &readBytes, NULL))
	{
		int errorCode = GetLastError();
		printf("Read Com3 failed with error %d.\n", errorCode);
		return -1;
	}

	// 去除后半部分无用字符
	string str = "";
	for (int i = 0; i < strlen(readBuffer); i++)
	{
		if (readBuffer[i] < 0)
		{
			break;
		}
		str += readBuffer[i];
	}
	printf(str.c_str());

	// 关闭串口
	CloseHandle(hCom3);

	return 0;
}