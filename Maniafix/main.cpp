#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <Windows.h>

#include "scripter.h"
#include "utils.h"

static char* WideToAscii(wchar_t* orig)
{
	int len = wcslen(orig) + 1;
	char* buffer = (char*)malloc(len + 1);
	wcstombs(buffer, orig, len);
	return buffer;
}

static void* g_hookUnacquireDevice = nullptr;
static IDirectInputDevice8* g_hookUnacquireDinputDevice = nullptr;

static void HookUnacquire()
{
	// We get a (semi-random) property from the direct input device..
	DIPROPSTRING prop;
	prop.diph.dwSize = sizeof(DIPROPSTRING);
	prop.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	prop.diph.dwObj = 0;
	prop.diph.dwHow = DIPH_DEVICE;

	HRESULT hres = g_hookUnacquireDinputDevice->GetProperty(DIPROP_PRODUCTNAME, &prop.diph);

	// Get the device name as reported by Maniaplanet
	char* szName = WideToAscii(*(wchar_t**)((char*)g_hookUnacquireDevice + 0x30));

	// ..and if this succeeds, it's not a mouse or keyboard, so it must be a joystick.
	// There must be a cleaner way to check this?
	if (SUCCEEDED(hres)) {
		// We skip the Unacquire call!
		Scripter::Utils::log("Skipping '%s'", szName);
	} else {
		// We manually call Unacquire.
		Scripter::Utils::log("Unacquiring '%s' %p", szName, g_hookUnacquireDinputDevice);
		g_hookUnacquireDinputDevice->Unacquire();
	}

	free(szName);
}

static char* g_hookUnacquireName = nullptr;

static __declspec(naked) void _HookUnacquire()
{
	__asm {
		push eax;
		push ebx;
		push ecx;
		push edx;
		push ebp;
		push esi;
		push edi;
	}

	__asm {
		mov g_hookUnacquireDevice, edi;
		mov g_hookUnacquireDinputDevice, ecx;
	}

	HookUnacquire();

	__asm {
		pop edi;
		pop esi;
		pop ebp;
		pop edx;
		pop ecx;
		pop ebx;
		pop eax;
		ret;
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason != DLL_PROCESS_ATTACH) {
		return TRUE;
	}

	Scripter::Utils::log("Maniafix initializing...");

	Scripter::init();

	char fnmBuffer[1024];
	GetModuleFileNameA(NULL, fnmBuffer, 1024);
	char* szExeName = strrchr(fnmBuffer, '\\') + 1;

	Scripter::Utils::log("Exe name: %s", szExeName);

	if (!strcmp(szExeName, "TmForever.exe")) {
		// Old fix: Disable all Unacquire calls on TmForever
		//unsigned char arr[] = { 0xEB, 0x35 };
		//Scripter::Utils::patch(0x008FB36B, arr, 2);

		// This is delayed due to encrypted game binary, see dinput_hook.cpp

	} else if (!strcmp(szExeName, "ManiaPlanet.exe")) {
		// New fix: Manually call Unacquire only for Mouse and Keyboard, so that it doesn't act strange on ShootMania
		Scripter::Utils::hook_call(0x004BE83D, _HookUnacquire, 46 - 5);

	} else {
		Scripter::Utils::log("Unknown process name!");
		return TRUE;
	}

	Scripter::Utils::log("Maniafix initialized successfully!");
	return TRUE;
}
