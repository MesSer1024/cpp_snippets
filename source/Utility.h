#pragma once

#include <vector>
#include <functional>
#include "BaseTypes.h"

namespace utility
{
	//////////////////////////////////////////////

	void runUtilityTests();

	//////////////////////////////////////////////

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
	ZippedRange<typename FirstContainer::value_type, typename SecondContainer::value_type> zipTwoContainers(FirstContainer& first, SecondContainer& second)
	{
		const u32 size1 = static_cast<u32>(std::distance(std::begin(first), std::end(first)));
		const u32 size2 = static_cast<u32>(std::distance(std::begin(second), std::end(second)));

		DD_ASSERT(size1 == size2);

		FirstElementType* it1 = &(*std::begin(first));
		SecondElementType* it2 = &(*std::begin(second));

		return ZippedRange<FirstElementType, SecondElementType>{it1, it2, size1};
	}

	//////////////////////////////////////////////

	template<typename Container, typename Predicate>
	u32 unstableEraseUsingLoop(Container& container, Predicate&& predicate)
	{
		const auto begin = container.begin();
		auto it = begin;
		auto end = container.end();

		while (it != end)
		{
			if (predicate(*it))
			{
				auto& destination = *it;
				auto& from = *--end;
				destination = std::move(from); // TODO: need to solve edge cases related to end being moved in as last element and the "ending with empty scenario"
				continue;
			}
			it++;
		}

		return static_cast<u32>(std::distance(begin, end));
	}

} // namespace utility

template<typename FirstContainer, typename SecondContainer,
	typename FirstElementType = typename FirstContainer::value_type,
	typename SecondElementType = typename SecondContainer::value_type
>
utility::ZippedRange<typename FirstContainer::value_type, typename SecondContainer::value_type> zip(FirstContainer& first, SecondContainer& second)
{
	return utility::zipTwoContainers(first, second);
}