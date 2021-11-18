#include "Utility.h"
#include "BaseTypes.h"
#include <vector>
#include <numeric>
#include <type_traits>

namespace utility
{
	void runUtilityTests()
	{
		struct MyStruct
		{
			u32 value = 0;
		};

		std::vector<int> integers(3);
		std::vector<MyStruct> structs(3);

		for (uint i = 0, end = integers.size(); i < end; ++i)
		{
			integers[i] = 1000 + i;
			structs[i].value = 200 + i;
		}

		printf("\n\n \t\tRunning UtilityTests:\n");
		// note to self: using structured binding for a tuple means we inherit the type from the individual field inside tuple: auto, auto&, auto&& is merely referring to how we deal with the "temporary"
		for (auto [i, j] : zip(integers, structs))
		{
			static_assert(std::is_same_v<decltype(i), int&> == true);
			static_assert(std::is_same_v<decltype(j), MyStruct&> == true);
		}

		for (auto [i, j] : zip(integers, structs))
		{
			printf("\n%u, %u", i, j.value);

			i += 20;
			j.value += 20;
		}
		printf("\n");

		for (auto [i, j] : zip(integers, structs))
		{
			printf("\n%u, %u", i, j.value);
		}
	}
}