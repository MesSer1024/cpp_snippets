#include "Services/CallCounter.h"

#include <gtest/gtest.h>
#include <template_lib/Types.h>

namespace ddahlkvist
{

class CallCounterFixture : public testing::Test {
public:
    CallCounterFixture()
        : _maxValue(17)
        , _counter(_maxValue)
    {}

protected:
    void SetUp() override { 
        
    }
    void TearDown() override { 
    }

    u32 _maxValue;
    CallCounter _counter;
};

TEST_F(CallCounterFixture, read_initializedToZero) {
    EXPECT_EQ(_counter.read(), 0u);
}

TEST_F(CallCounterFixture, increment_incrementsOnEachCall) {
    for (uint i = 1; i < 5; ++i)
    {
        const auto value = _counter.increment();
        const auto expected = i;
        EXPECT_EQ(value, expected);
    }
}

TEST_F(CallCounterFixture, increment_wrapsOnMaxValue) {
	const auto end = _maxValue + 8;
	for (uint i = 1; i < end; ++i)
	{
		auto value = _counter.increment();
		auto expected = i % _maxValue;
		EXPECT_EQ(value, expected);
	}
}

TEST_F(CallCounterFixture, read_sameAsIncrementedValue) {
	const auto end = _maxValue + 8;
	for (uint i = 1; i < end; ++i)
	{
		auto incValue = _counter.increment();
		auto readValue = _counter.read();
		auto expected = i % _maxValue;
		EXPECT_EQ(incValue, readValue);
		EXPECT_EQ(readValue, expected);
	}
}

}

