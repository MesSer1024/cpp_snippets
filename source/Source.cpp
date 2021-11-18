#include <iostream>
#include "StructWithBitfields.h"
#include "VectorBasics.h"
#include "Meta.h"

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

u32 g_NaiveElementIndex = 0;
u32 g_CorrectElementIndex = 0;
u32 g_ComplexElementIndex = 0;


int main()
{
	using namespace std;

	testStructWithBitfields();

	runVectorExample();

	runMetaTests();

	cin.get();
	return 0;
}