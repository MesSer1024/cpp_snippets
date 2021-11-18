#pragma once

#include <vector>
#include <functional>
#include "BaseTypes.h"

//template <typename T>
//struct is_array_or_vector {
//    enum { value = false };
//};
//
//template <typename T, typename A>
//struct is_array_or_vector<std::vector<T, A>> {
//    enum { value = true };
//};
//
//template <typename T, std::size_t N>
//struct is_array_or_vector<std::array<T, N>> {
//    enum { value = true };
//};
//
//template <typename T>
//typename std::enable_if<is_array_or_vector<T>::value>::type
//f(T const&)
//{
//}

template<typename ElementA, typename ElementB>
struct ZippedRange
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

template<typename FirstContainer, typename SecondContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type
>
ZippedRange<typename FirstContainer::value_type, typename SecondContainer::value_type> zip(FirstContainer& first, SecondContainer& second)
{
	const u32 size1 = static_cast<u32>(std::distance(std::begin(first), std::end(first)));
	const u32 size2 = static_cast<u32>(std::distance(std::begin(second), std::end(second)));

	DD_ASSERT(size1 == size2);

	FirstElementType* it1 = &(*std::begin(first));
	SecondElementType* it2 = &(*std::begin(second));

	return ZippedRange<FirstElementType, SecondElementType>{it1, it2, size1};
}

void runMetaTests();