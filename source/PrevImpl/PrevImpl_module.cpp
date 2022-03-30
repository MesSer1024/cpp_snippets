#include <iostream>
#include "PrevImpl/StructWithBitfields.h"
#include "PrevImpl/VectorBasics.h"
#include "PrevImpl/Zip.h"
#include <vector>
#include <typeinfo>
#include "PrevImpl/StructuredBindings.h"
#include "PrevImpl/Templates.h"
#include "PrevImpl/PrevImpl_module.h"

//////////////////////////////////////////////
// used by VectorBasics

namespace ddahlkvist
{

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

	void testStructuredBindingAndTuple()
	{


		using namespace std;

		vector<MyStruct> structs(3);
		vector<int> integers(3);

		cout << "---------------------" << endl;
		{
			cout << "ByValue_ByValue:" << endl;
			auto [a, b] = getTupleByValue(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "ByValue_ByConstValue:" << endl;
			const auto [a, b] = getTupleByValue(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "ByValue_ByConstRef:" << endl;
			// auto& [a, b] = getTupleByValue(structs, integers);
			const auto& [a, b] = getTupleByValue(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "ByValue_UniversalRef:" << endl;
			auto&& [a, b] = getTupleByValue(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		//////////////////////////////////////


		cout << "---------------------" << endl;
		{
			cout << "tupleWithRefs_ByValue:" << endl;
			auto [a, b] = tupleWithRefs(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "tupleWithRefs_ByConstValue:" << endl;
			const auto [a, b] = tupleWithRefs(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "tupleWithRefs_ByConstRef:" << endl;
			const auto& [a, b] = tupleWithRefs(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "tupleWithRefs_UniversalRef:" << endl;
			auto&& [a, b] = tupleWithRefs(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		//////////////////////////////////////


		cout << "---------------------" << endl;
		{
			cout << "getTupleReference_ByValue:" << endl;
			auto [a, b] = getTupleReference(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "getTupleReference_ByConstValue:" << endl;
			const auto [a, b] = getTupleReference(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "getTupleReference_ByConstRef:" << endl;
			const auto& [a, b] = getTupleReference(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}

		{
			cout << "getTupleReference_UniversalRef:" << endl;
			auto&& [a, b] = getTupleReference(structs, integers);
			cout << "Type: A=" << get_type_name<decltype(a)>() << ", B=" << get_type_name<decltype(b)>() << '\n';
			cout << "---------------------" << endl;
		}
	}

	void testStructuredBinding()
	{
		using namespace std;

		cout << "---------------------" << endl;
		cout << "---------------------" << endl;
		cout << "testStructuredBinding" << endl;
		cout << "---------------------" << endl;

		cout << "getByRef_to_auto: ";
		auto [a1, a2] = getDataWrapperByRef(); // Grabbing the "temporary" by value, so we are copying the data
		cout << endl << "getByRef_to_auto&: ";
		auto& [b1, b2] = getDataWrapperByRef(); // Grabbing the "temporary" by ref [sent by ref] 
		cout << endl << "getByRef_to_auto&&: ";
		auto&& [c1, c2] = getDataWrapperByRef(); // Universal reference to "temporary" [sent by ref] so this is by ref

		// showcase that the "aliased type" is of the same type here
		static_assert(std::is_same_v<decltype(a1), decltype(b1)> == true);
		static_assert(std::is_same_v<decltype(a1), decltype(c1)> == true);
		static_assert(std::is_same_v<decltype(a2), decltype(b2)> == true);
		static_assert(std::is_same_v<decltype(a2), decltype(c2)> == true);

		// showcase that the type of "bound variable" is not a reference
		static_assert(std::is_reference_v<decltype(a1)> == false);
		static_assert(std::is_reference_v<decltype(a2)> == false);

		cout << endl << "Rewriting in 'verbose' format: " << endl;
		// in practice this code is equivalent with
		auto temp1 = getDataWrapperByRef();
		auto&& t1_a1 = temp1.structs;
		auto&& t1_a2 = temp1.integers;

		auto& temp2 = getDataWrapperByRef();
		auto&& t2_a1 = temp2.structs;
		auto&& t2_a2 = temp2.integers;

		auto&& temp3 = getDataWrapperByRef();
		auto&& t3_a1 = temp3.structs;
		auto&& t3_a2 = temp3.integers;
	}

	void testTemplateCompileErrors()
	{
		//std::vector<MyStruct> structs;
		//MyStruct& foo = getFirst(structs);
	}


}

namespace ddahlkvist::previmpl
{
	PREVIMPL_PUBLIC void dummy() { } // this is here to always output a .lib-file

	void executePrevimpl()
	{
		testStructWithBitfields();

		runVectorExample();

		testZip2();
		testZip3();

		testStructuredBindingAndTuple();
		testStructuredBinding();

		testTemplateCompileErrors();
	}
}