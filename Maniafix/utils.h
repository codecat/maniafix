#ifndef SCRIPTER_UTILS_H_INCLUDED
#define SCRIPTER_UTILS_H_INCLUDED

namespace Scripter
{
	namespace Utils
	{
		int patch(unsigned int ptr, void* buffer, unsigned int len);

		template<typename TF>
		void hook_call(unsigned int ptr, TF func, unsigned int fillnop = 0)
		{
			unsigned char* buff = new unsigned char[5 + fillnop];
			buff[0] = 0xE8; // CALL rel32

			*(unsigned int*)(buff + 1) = (unsigned int)((int)(void*)func - (int)ptr - 5);

			if (fillnop > 0)
				memset(buff + 5, 0x90, fillnop);

			patch(ptr, buff, 5 + fillnop);

			delete[] buff;
		}

		void hook_jmp(unsigned int ptr, void* func);

		inline void call(unsigned int ptr)
		{
			(
				(void(*)())
				ptr
			)();
		}

		template<typename T1>
		inline void call(unsigned int ptr, T1 p1)
		{
			(
				(void(*)(T1))
				ptr
			)(p1);
		}

		template<typename T1, typename T2>
		inline void call(unsigned int ptr, T1 p1, T2 p2)
		{
			(
				(void(*)(T1, T2))
				ptr
			)(p1, p2);
		}

		template<typename T1, typename T2, typename T3>
		inline void call(unsigned int ptr, T1 p1, T2 p2, T3 p3)
		{
			(
				(void(*)(T1, T2, T3))
				ptr
			)(p1, p2, p3);
		}

		template<typename T1, typename T2, typename T3, typename T4>
		inline void call(unsigned int ptr, T1 p1, T2 p2, T3 p3, T4 p4)
		{
			(
				(void(*)(T1, T2, T3, T4))
				ptr
			)(p1, p2, p3, p4);
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5>
		inline void call(unsigned int ptr, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
		{
			(
				(void(*)(T1, T2, T3, T4, T5))
				ptr
			)(p1, p2, p3, p4, p5);
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		inline void call(unsigned int ptr, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
		{
			(
				(void(*)(T1, T2, T3, T4, T5, T6))
				ptr
			)(p1, p2, p3, p4, p5, p6);
		}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		inline void call(unsigned int ptr, T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
		{
			(
				(void(*)(T1, T2, T3, T4, T5, T6, T7))
				ptr
			)(p1, p2, p3, p4, p5, p6, p7);
		}

		template<typename TR>
		inline TR callfunc(unsigned int ptr)
		{
			return (
				(TR(*)())
				ptr
			)();
		}

		template<typename TR, typename T1>
		inline TR callfunc(unsigned int ptr, T1 p1)
		{
			return (
				(TR(*)(T1))
				ptr
			)(p1);
		}

		template<typename TR, typename T1, typename T2>
		inline TR callfunc(unsigned int ptr, T1 p1, T2 p2)
		{
			return (
				(TR(*)(T1, T2))
				ptr
			)(p1, p2);
		}

		template<typename TR, typename T1, typename T2, typename T3>
		inline TR callfunc(unsigned int ptr, T1 p1, T2 p2, T3 p3)
		{
			return (
				(TR(*)(T1, T2, T3))
				ptr
			)(p1, p2, p3);
		}

		template<typename TR, typename T1, typename T2, typename T3, typename T4>
		inline TR callfunc(unsigned int ptr, T1 p1, T2 p2, T3 p3, T4 p4)
		{
			return (
				(TR(*)(T1, T2, T3, T4))
				ptr
			)(p1, p2, p3, p4);
		}
	}
}

#endif
