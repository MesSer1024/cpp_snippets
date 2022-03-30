#pragma once

#include <algorithm>
#include <functional>
#include "BaseTypes.h"

namespace ddahlkvist
{

template <class T>
constexpr std::string_view
get_type_name()
{
    using namespace std;
#ifdef __clang__
    string_view p = __PRETTY_FUNCTION__;
    return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
    string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return string_view(p.data() + 36, p.size() - 36 - 1);
#  else
    return string_view(p.data() + 49, p.find(';', 49) - 49);
#  endif
#elif defined(_MSC_VER)
    string_view p = __FUNCSIG__;
    return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

template<typename FirstContainer, typename SecondContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type
>
std::tuple<FirstElementType, SecondElementType> getTupleByValue(FirstContainer& first, SecondContainer& second)
{
	const u32 size1 = static_cast<u32>(std::distance(std::begin(first), std::end(first)));
	const u32 size2 = static_cast<u32>(std::distance(std::begin(second), std::end(second)));

	FirstElementType* it1 = &(*std::begin(first));
	SecondElementType* it2 = &(*std::begin(second));

	return { *it1, *it2 };
}

template<typename FirstContainer, typename SecondContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type
>
std::tuple<FirstElementType&, SecondElementType&> tupleWithRefs(FirstContainer& first, SecondContainer& second)
{
	const u32 size1 = static_cast<u32>(std::distance(std::begin(first), std::end(first)));
	const u32 size2 = static_cast<u32>(std::distance(std::begin(second), std::end(second)));

	FirstElementType* it1 = &(*std::begin(first));
	SecondElementType* it2 = &(*std::begin(second));

	return { *it1, *it2 };
}

template<typename FirstContainer, typename SecondContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type
>
std::tuple<FirstElementType, SecondElementType>& getTupleReference(FirstContainer& first, SecondContainer& second)
{
	FirstElementType* it1 = &(*std::begin(first));
	SecondElementType* it2 = &(*std::begin(second));

	static std::tuple<FirstElementType, SecondElementType> value = { *it1, *it2 };
	return value;
}

struct DataWrapper
{
	DataWrapper()
	{
		structs.resize(10);
		integers.resize(10);
	}

	DataWrapper(const DataWrapper& other)
	{
		printf("DataWrapper(DataWrapper&)\n" );

		structs = other.structs;
		integers = other.integers;
	}

	DataWrapper(DataWrapper&& other) noexcept
	{
		printf("DataWrapper(DataWrapper&&)");

		structs = std::move(other.structs);
		integers = std::move(other.integers);
	}

	std::vector<MyStruct> structs;
	std::vector<int> integers;
};

static DataWrapper s_data;

DataWrapper& getDataWrapperByRef()
{
	return s_data;
}
}