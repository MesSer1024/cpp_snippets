#pragma once

#include <vector>
#include <functional>
#include "BaseTypes.h"
#include "PrevImpl_module.h"

namespace ddahlkvist
{
	PREVIMPL_PUBLIC void foo();

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
}

