#include <stdio.h>
#include <string.h>

#include <Windows.h>

int main()
{
	char exe[] = "ManiaPlanet.exe";

	PROCESS_INFORMATION pi = { 0 };
	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	CreateProcess(NULL, exe, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);

	printf("Process started\n");

	const char* dll = "Maniafix.dll";

	LPVOID pLoadLib = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
	LPVOID pMemoryFnm = VirtualAllocEx(pi.hProcess, NULL, strlen(dll) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	WriteProcessMemory(pi.hProcess, pMemoryFnm, dll, strlen(dll) + 1, NULL);
	HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pLoadLib, pMemoryFnm, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	VirtualFreeEx(pi.hProcess, pMemoryFnm, strlen(dll) + 1, MEM_RELEASE);
	CloseHandle(hThread);

	printf("Dll injected\n");

	return 0;
}
