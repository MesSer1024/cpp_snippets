#pragma once

namespace ddahlkvist
{
	using u8 = unsigned char;
	using u16 = unsigned short;
	using u32 = unsigned long;
	using u64 = unsigned long long;
	
	using s8 = signed char;
	using s16 = signed short;
	using s32 = signed long;
	using s64 = signed long long;
	
	using uint = u32;
	using usize = u64;
	using uptr = u64;
}

#include <cassert>
namespace ddahlkvist
{
#if defined(DD_DEBUG) || defined(DD_RELEASE)
#define DD_ASSERT(x) assert(x)
//#define DD_ASSERT(condition) if(condition) {} else {throw 404;}
#elif defined (DD_FINAL)
#define DD_ASSERT(x) do {} while (false)
#endif
}