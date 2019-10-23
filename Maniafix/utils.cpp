#include "utils.h"
#include "scripter.h"

#include <stdio.h>

#include <share.h>

namespace Scripter
{
	namespace Utils
	{
		void log(const char* str, ...)
		{
#ifdef _DEBUG
			FILE* fh = _fsopen("maniafix.log", "ab", _SH_DENYWR);

			va_list va;
			va_start(va, str);
			fprintf(fh, "[%d] ", GetCurrentProcessId());
			vfprintf(fh, str, va);
			fprintf(fh, "\n");
			va_end(va);

			fclose(fh);
#endif
		}

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
