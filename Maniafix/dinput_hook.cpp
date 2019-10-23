#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include "scripter.h"
#include "utils.h"

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	HRESULT ret = E_FAIL;

	char path[MAX_PATH] = { 0 };
	GetSystemDirectoryA(path, MAX_PATH);
	strcat_s(path, MAX_PATH, "\\dinput8.dll");
	HMODULE hDinputLib = LoadLibraryA(path);

	IDirectInputDevice8* device = nullptr;

	if (hDinputLib) {
		auto proc = (HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN))GetProcAddress(hDinputLib, "DirectInput8Create");
		if (proc) {
			ret = proc(hinst, dwVersion, riidltf, ppvOut, punkOuter);
			if (ret == DI_OK) {
				device = (IDirectInputDevice8*)*ppvOut;
			}
		}
	}

	char fnmBuffer[1024];
	GetModuleFileNameA(NULL, fnmBuffer, 1024);
	char* szExeName = strrchr(fnmBuffer, '\\') + 1;

	if (!strcmp(szExeName, "TmForever.exe")) {
		Scripter::Utils::log("Patching TmForever via DirectInput8Create");

		unsigned char arr[] = { 0xEB, 0x35 };
		Scripter::Utils::patch(0x008FB36B, arr, 2);
	}

	return ret;
}
