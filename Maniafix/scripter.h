#ifndef SCRIPTER_H_INCLUDED
#define SCRIPTER_H_INCLUDED

#include <Windows.h>

namespace Scripter
{
	extern HANDLE process;
	extern int written;

	void init();
}

#endif
