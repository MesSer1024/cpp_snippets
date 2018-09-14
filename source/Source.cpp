#include <iostream>
#include "StructWithBitfields.h"

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

int main()
{
	using namespace std;

	testStructWithBitfields();
	cin.get();
	return 0;
}