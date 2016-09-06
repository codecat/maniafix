#include "scripter.h"
#include "utils.h"

namespace Scripter
{
	extern HANDLE process = 0;
	extern int written = 0;

	void init()
	{
		process = GetCurrentProcess();
	}
}
