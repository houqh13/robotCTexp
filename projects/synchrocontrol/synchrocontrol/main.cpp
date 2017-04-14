#include <stdio.h>
#include <string>
#include <Windows.h>
using namespace std;

int main() {
	// ���崮�ھ��
	HANDLE hCom3 = INVALID_HANDLE_VALUE;
	HANDLE hCom4 = INVALID_HANDLE_VALUE;

	// �������ھ��
	// ���ô��ڷ�������Ϊ�ɶ���д, ���ڴ򿪷�ʽΪͬ��I/O
	hCom3 = CreateFile(L"Com3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	hCom4 = CreateFile(L"Com4", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	// ��⴮���������
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

	// ���ô���
	SetupComm(hCom3, 1024, 1024);		// ��������С
	SetupComm(hCom4, 1024, 1024);
	DCB dcb;
	GetCommState(hCom3, &dcb);
	dcb.BaudRate = CBR_115200;			// ������
	dcb.ByteSize = 8;					// ����λ
	dcb.Parity = NOPARITY;				// У��λ
	dcb.StopBits = ONESTOPBIT;			// ֹͣλ
	SetCommState(hCom3, &dcb);
	SetCommState(hCom4, &dcb);

	// ��ջ�����
	PurgeComm(hCom3, PURGE_RXCLEAR | PURGE_TXCLEAR);
	PurgeComm(hCom4, PURGE_RXCLEAR | PURGE_TXCLEAR);

	char *writeBuffer[2] = {"254", "1"};				// ����ָ��
	DWORD writeBytes;
	char readBuffer[1024];
	DWORD readBytes;

	Sleep(7500);

	// ����ָ��
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

	// ���շ�����Ϣ
	if (!ReadFile(hCom3, readBuffer, strlen(readBuffer), &readBytes, NULL))
	{
		int errorCode = GetLastError();
		printf("Read Com3 failed with error %d.\n", errorCode);
		return -1;
	}

	// ȥ����벿�������ַ�
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

	// �رմ���
	CloseHandle(hCom3);

	return 0;
}