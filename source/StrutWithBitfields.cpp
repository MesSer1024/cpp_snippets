#include <iostream>
#include "BaseTypes.h"


// if defined, size is 16 otherwise 24 on msvc --> always 16 on gcc/clang
#define be_smart


#ifdef be_smart
enum MyEnum : u32
#else
enum MyEnum : u8
#endif
{
	MyEnum_Unknown = 0,
	MyEnum_CreationNotConfirmed,
	MyEnum_CreationConfirmed,
	MyEnum_DeletionNotConfirmed
};

struct MyStruct
{
	u64 handle;
	u16 firstWrittenIndex;
	u16 lastWrittenIndex;
#ifdef be_smart
	enum MyEnum state : 8;
#else
	enum MyEnum state;
#endif

	u32 pendingInit : 1;
	u32 pendingDelete : 1;
	u32 pendingFlush : 1;
	u32 isFlushed : 1;
	u32 hasDirtyStates : 1;
	u32 hasModifiedMask : 1;
	u32 pendingNewBaseline : 1;
	u32 isStaticNetObject : 1;
	u32 countToNextBaseLine : 8;
	u32 pendingNewBaselineIndex : 4;
};

void runStructWithBitfields()
{
	u32 size = sizeof(MyStruct);
	u32 alignment = alignof(MyStruct);


#ifdef be_smart
	printf("I'm smart!\n");
#endif
	printf("sizeof(MyStruct): %u, align %u\n", size, alignment);
}