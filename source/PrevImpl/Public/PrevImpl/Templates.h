#pragma once
#include <tuple>

namespace ddahlkvist
{
	// I want to make sure I can create a template that can return a user friendly compile error when we fail to use the "Container-specific" template

	//template<typename Container, typename ContainerElement = typename Container::value_type>
	//ContainerElement& getFirst(Container& first)
	//{
	//	ContainerElement* it = std::begin(first);
	//	return *it;
	//}

	template<typename T> using Element = T::value_type;

	template<typename T, typename T::value_type>
	concept LinearCollection =
		requires(T& x) {
		typename T::value_type; // required nested member name
		x.size();
		//std::is_same_v<decltype(std::begin(x)), Element<T>*>;
	};

	//template<LinearCollection T>
	//Element<T>& getFirst(T& first)
	//{
	//	auto it = std::begin(first);
	//	return *it;
	//}
}