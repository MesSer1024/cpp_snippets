#include "Services/CallCounter.h"

namespace ddahlkvist
{

CallCounter::CallCounter(u32 maxValue)
	: _maxValue(maxValue)
	, _currentValue(0u)
{}

u32 CallCounter::increment()
{
	_currentValue = (_currentValue + 1) % _maxValue;
	return _currentValue;
}

u32 CallCounter::read() const
{
	return _currentValue;
}

}