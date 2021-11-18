#include <iostream>
#include "StructWithBitfields.h"
#include "VectorBasics.h"
#include "Zip.h"
#include <vector>

//////////////////////////////////////////////
// used by VectorBasics

u32 g_NaiveElementIndex = 0;
u32 g_CorrectElementIndex = 0;
u32 g_ComplexElementIndex = 0;

//////////////////////////////////////////////

void testStructWithBitfields()
{
u32 size = sizeof(StructWithBitfields);
	u32 alignment = alignof(StructWithBitfields);

	u32 smartSize = sizeof(SmartStructWithBitfields);
	u32 smartAlignment = alignof(SmartStructWithBitfields);

	printf("sz | align  name_of_struct\n");
	printf("--------------------------\n");
	printf("%u | %u -- StructWithBitfields\n", size, alignment);
	printf("%u | %u -- SmartStructWithBitfields\n", smartSize, smartAlignment);
}

//////////////////////////////////////////////

void testZip2()
{
	struct MyStruct
	{
		u32 value = 0;
	};

	std::vector<int> integers(3);
	std::vector<MyStruct> structs(3);

	uint i = 0;
	for (auto [a, b] : zip(integers, structs))
	{
		a = 1000 + i;
		b.value = 200 + i;
		i++;
	}

	printf("\n\n \t\tTest Zip2:\n");
	// note to self: using structured binding for a tuple means we inherit the type from the individual field inside tuple: auto, auto&, auto&& is merely referring to how we deal with the "temporary"
	for (auto [a, b] : zip(integers, structs))
	{
		static_assert(std::is_same_v<decltype(a), int&> == true);
		static_assert(std::is_same_v<decltype(b), MyStruct&> == true);
	}

	for (auto [a, b] : zip(integers, structs))
	{
		printf("\n%u, %u", a, b.value);

		a += 20;
		b.value += 20;
	}
	printf("\n");

	for (auto [a, b] : zip(integers, structs))
	{
		printf("\n%u, %u", a, b.value);
	}
}

void testZip3()
{
	struct MyStruct
	{
		u32 value = 0;
	};

	std::vector<int> integers(3);
	std::vector<MyStruct> structs(3);
	std::vector<float> floats(3);

	uint i = 0;
	for (auto [a, b, c] : zip(integers, structs, floats))
	{
		a = 1000 + i;
		b.value = 200 + i;
		c = 3.0f + i * 0.11f;
		i++;
	}

	printf("\n\n \t\tTest Zip3:\n");

	for (auto [a, b, c] : zip(integers, structs, floats))
	{
		printf("\n%u, %u, %f", a, b.value, c);
	}
}

//////////////////////////////////////////////

int main()
{
	using namespace std;

	testStructWithBitfields();

	runVectorExample();

	testZip2();
	testZip3();

	cin.get();
	return 0;
}