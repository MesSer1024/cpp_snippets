#pragma once

#include <algorithm>
#include <functional>
#include "BaseTypes.h"

namespace containers
{
	template<typename Container, typename Predicate>
	u32 unstableEraseUsingLoop(Container& container, Predicate&& predicate)
	{
		// this seems to be the fastest approach, other scenarios seems to swap two elements whereas this will only move from end to "entry"
		// swap is in theory the "correct" behavior but...

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

		const u32 newSize = static_cast<u32>(std::distance(begin, end));
		container.resize(newSize);
		return newSize;
	}

	template<typename Container, typename Predicate>
	void unstableEraseUsingPartition(Container& container, Predicate&& predicate)
	{
		// overall the fastest and most correct approach, will swap the elements matching predicate, taking from the end
		auto first = std::begin(container);

		// fast and clean approach, but will end up invoking "swap" on the entries instead of just "move clone" from "last"
		auto pivot = std::partition(first, container.end(), std::not_fn(predicate));
		const u32 newSize = static_cast<u32>(std::distance(first, pivot));
		container.resize(newSize);
	}
} // namespace containers
