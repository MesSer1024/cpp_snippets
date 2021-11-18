#include <iostream>
#include "BaseTypes.h"

// This problem was done during investigation between "size" of structs on different compilers

enum MyEnum : u8
{
	MyEnum_Unknown = 0,
	MyEnum_CreationNotConfirmed,
	MyEnum_CreationConfirmed,
	MyEnum_DeletionNotConfirmed
};

// size is 24 on msvc --> always 16 on gcc/clang
struct StructWithBitfields
{
	u64 handle;
	u16 firstWrittenIndex;
	u16 lastWrittenIndex;
	enum MyEnum state;

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

// workaround for msvc
enum SmartEnum : u32
{
	MySmartEnum_Unknown = 0,
	MySmartEnum_CreationNotConfirmed,
	MySmartEnum_CreationConfirmed,
	MySmartEnum_DeletionNotConfirmed
};

struct SmartStructWithBitfields
{
	u64 handle;
	u16 firstWrittenIndex;
	u16 lastWrittenIndex;
	enum SmartEnum state : 8;

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
