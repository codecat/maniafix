#include "utils.h"
#include "scripter.h"

#include <stdio.h>

namespace Scripter
{
	namespace Utils
	{
		int patch(unsigned int ptr, void* buffer, unsigned int len)
		{
			if (Scripter::process == 0)
				return 0;

			printf("Patching %08x with %d bytes\n", ptr, len);

			SIZE_T ret;
			WriteProcessMemory(GetCurrentProcess(), (void*)ptr, buffer, len, &ret);
			written += ret;
			return ret;
		}

		void hook_jmp(unsigned int ptr, void* func)
		{
			//TODO
		}
	}
}
