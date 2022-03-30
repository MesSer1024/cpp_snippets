#pragma once

#include "template_lib/Types.h"
#include <iostream>

namespace ddahlkvist
{
	struct MyStruct {
		MyStruct()
		{
			using namespace std;
			std::cout << "MyStruct()" << endl;
		}

		MyStruct(const MyStruct& other)
		{
			value = other.value;
			using namespace std;
			cout << "(&)" << endl;
		}

		MyStruct(MyStruct&& other) noexcept
		{
			value = other.value;
			using namespace std;
			cout << "(&&)" << endl;
		}

		void operator=(const MyStruct& other)
		{
			value = other.value;
		}

		int value = 4;
	};

}


