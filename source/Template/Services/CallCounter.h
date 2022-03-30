#pragma once

#include <template_lib/template_lib_module.h>
#include <template_lib/Types.h>

namespace ddahlkvist
{

class CallCounter {
public:
	TEMPLATE_INTERNAL CallCounter(u32 maxValue);
	TEMPLATE_INTERNAL u32 increment();
	TEMPLATE_INTERNAL u32 read() const;
private:
	u32 _maxValue;
	u32 _currentValue;
};

}
