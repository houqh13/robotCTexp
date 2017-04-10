
#include <Windows.h>
using namespace std;

int main() {
	HANDLE hCom3 = INVALID_HANDLE_VALUE;
	HANDLE hCom4 = INVALID_HANDLE_VALUE;

	hCom3 = CreateFile(L"Com3", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
}