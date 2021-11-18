#pragma once

#include <vector>
#include <functional>
#include "BaseTypes.h"

//////////////////////////////////////////////

namespace zip_details
{
	//////////////////////////////////////////////

	template<typename ElementA, typename ElementB>
	struct ZippedRange2
	{
		struct It
		{
			ElementA* _first;
			ElementB* _second;

			void operator++()
			{
				_first++;
				_second++;
			}

			std::tuple<ElementA&, ElementB&> operator*()
			{
				// given for(auto [f,b] : zip(foo, bar))
				// we are producing "It<foo, bar>", this is then the automatic transformation when accessing each entry
				// by returning a reference to each element, we allow it to be modified
				return { *_first, *_second };
			}

			bool operator!=(const It& other) const
			{
				return _first != other._first;
			}
		};

		ElementA* _begin1;
		ElementB* _begin2;
		u32 _size;

		It begin() { return It{ _begin1, _begin2 }; }
		It end() { return It{ _begin1 + _size, _begin2 + _size }; }
	};
	//////////////////////////////////////////////

	template<typename ElementA, typename ElementB, typename ElementC>
	struct ZippedRange3
	{
		struct It
		{
			ElementA* _first;
			ElementB* _second;
			ElementC* _third;

			void operator++()
			{
				_first++;
				_second++;
				_third++;
			}

			std::tuple<ElementA&, ElementB&, ElementC&> operator*()
			{
				return { *_first, *_second, *_third };
			}

			bool operator!=(const It& other) const
			{
				return _first != other._first;
			}
		};

		ElementA* _begin1;
		ElementB* _begin2;
		ElementC* _begin3;
		u32 _size;

		It begin() { return It{ _begin1, _begin2, _begin3 }; }
		It end() { return It{ _begin1 + _size, _begin2 + _size, _begin3 + _size }; }
	};

	//////////////////////////////////////////////

	template<typename FirstContainer, typename SecondContainer,
		typename FirstElementType = typename FirstContainer::value_type,
		typename SecondElementType = typename SecondContainer::value_type
	>
		ZippedRange2<FirstElementType, SecondElementType> zipTwoContainers(FirstContainer& first, SecondContainer& second)
	{
		const u32 size1 = static_cast<u32>(std::distance(std::begin(first), std::end(first)));
		const u32 size2 = static_cast<u32>(std::distance(std::begin(second), std::end(second)));

		DD_ASSERT(size1 == size2);

		FirstElementType* it1 = &(*std::begin(first));
		SecondElementType* it2 = &(*std::begin(second));

		return ZippedRange2<FirstElementType, SecondElementType>{it1, it2, size1};
	}

	template<typename FirstContainer, typename SecondContainer, typename ThirdContainer,
		typename FirstElementType = typename FirstContainer::value_type,
		typename SecondElementType = typename SecondContainer::value_type,
		typename ThirdElementType = typename ThirdContainer::value_type
	>
		ZippedRange3<FirstElementType, SecondElementType, ThirdElementType> zipThreeContainers(FirstContainer& first, SecondContainer& second, ThirdContainer& third)
	{
		const u32 size1 = static_cast<u32>(std::distance(std::begin(first), std::end(first)));
		const u32 size2 = static_cast<u32>(std::distance(std::begin(second), std::end(second)));
		const u32 size3 = static_cast<u32>(std::distance(std::begin(third), std::end(third)));

		DD_ASSERT(size1 == size2);
		DD_ASSERT(size1 == size3);

		FirstElementType* it1 = &(*std::begin(first));
		SecondElementType* it2 = &(*std::begin(second));
		ThirdElementType* it3 = &(*std::begin(third));

		return ZippedRange3<FirstElementType, SecondElementType, ThirdElementType>{it1, it2, it3, size1};
	}


} // namespace utility

/// <summary>
/// Function will wrap 2 containers, making it possible to write a range based for and utilize structured binding to access all individual elements
/// std::vector<int> integers;
/// std::vector<MyStruct> structs;
/// 
/// for(auto [a, b] = zip(integers, structs)
/// {
///		a = 13;
///		b = MyStruct(13);
/// }
/// 
/// instead of:
/// assert(integers.size() == structs.size());
/// for(uint i=0, end = integers.size(); i < end; ++i)
/// {
///		integers[i] = 13;
///		structs[i] = MyStruct(13);
/// }
/// </summary>
template<typename FirstContainer, typename SecondContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type
>
zip_details::ZippedRange2<FirstElementType, SecondElementType> zip(FirstContainer& first, SecondContainer& second)
{
	return zip_details::zipTwoContainers(first, second);
}

template<typename FirstContainer, typename SecondContainer, typename ThirdContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type,
	typename ThirdElementType = typename ThirdContainer::value_type
>
zip_details::ZippedRange3<FirstElementType, SecondElementType, ThirdElementType> zip(FirstContainer& first, SecondContainer& second, ThirdContainer& third)
{
	return zip_details::zipThreeContainers(first, second, third);
}