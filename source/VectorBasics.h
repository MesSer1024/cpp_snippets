#pragma once

#include "BaseTypes.h"
#include "Utility.h"
#include <vector>
#include <algorithm>
#include <functional>

// This code is meant to serve as an example to show when the different constructors and assignment operators are invoked and what might affect it [noexcept]
inline void writeCommand(const char* str) { printf("\n%s\n", str); }
inline void writeCommand(const char* str, u64 value) { printf("\n%s:%u\n", str, static_cast<u32>(value)); }
inline void writeCommand(const char* str, u64 prevValue, u64 newValue) { printf("\n%s:%u -> %u (elements)\n", str, static_cast<u32>(prevValue), static_cast<u32>(newValue)); }
inline void write(const char* str) { printf("%s", str); }
inline void writeDescription(const char* str) { printf("\n--------------------\n\t\t%s\n", str); }

extern u32 g_NaiveElementIndex;
extern u32 g_CorrectElementIndex;
extern u32 g_ComplexElementIndex;

struct NaiveElement
{
	// this object's MoveConstructor is not marked as "noexcept", it is not used by vector reallocations
	u32 dummyData;

	~NaiveElement()
	{
		write("N~");
	}

	NaiveElement()
	{
		write("N");
		dummyData = g_NaiveElementIndex++;
	}

	NaiveElement(const NaiveElement& other)
	{
		write("N&");
		dummyData = other.dummyData;
	}

	NaiveElement(NaiveElement&& other)
	{
		write("N&&");
		dummyData = other.dummyData;
	}

	void operator=(const NaiveElement& other)
	{
		write("N=&");
		dummyData = other.dummyData;
	}

	void operator=(NaiveElement&& other)
	{
		write("N=&&");
		dummyData = other.dummyData;
	}
};

struct CorrectElement
{
	u32 dummyData = 0;

	~CorrectElement()
	{
		write("C~");
	}

	CorrectElement()
	{
		write("C");
		dummyData = g_CorrectElementIndex++;
	}

	CorrectElement(const CorrectElement& other)
	{
		write("C&");
		dummyData = other.dummyData;
	}

	CorrectElement(CorrectElement&& other) noexcept
	{
		write("C&&");
		dummyData = other.dummyData;
	}

	void operator=(const CorrectElement& other)
	{
		write("C=&");
		dummyData = other.dummyData;
	}

	void operator=(CorrectElement&& other) noexcept
	{
		write("C=&&");
		dummyData = other.dummyData;
	}
};

struct ComplexElement
{
	struct InnerType
	{
		std::vector<int> integers;
		u32 things = 0;

		InnerType() = default;
		InnerType(const InnerType& other) = default;
		InnerType(InnerType&& other) = delete;
	};
	InnerType complexInnerData;
	u32 dummyData;

	~ComplexElement()
	{
		write("X~");
	}

	ComplexElement()
	{
		write("X");
		dummyData = g_ComplexElementIndex++;
	}

	ComplexElement(const ComplexElement& other)
	{
		write("X&");
		dummyData = other.dummyData;
	}

	ComplexElement(ComplexElement&& other) noexcept
	{
		write("X&&");
		dummyData = other.dummyData;
	}

	void operator=(const ComplexElement& other)
	{
		write("X=&");
		dummyData = other.dummyData;
	}

	void operator=(ComplexElement&& other) noexcept
	{
		write("X=&&");
		dummyData = other.dummyData;
	}
};

struct VectorExample
{
	void reserve(u32 numElements)
	{
		writeCommand("reserve", numElements);
		_naives.reserve(numElements);
		write("\n");
		_corrects.reserve(numElements);
		write("\n");
		_complex.reserve(numElements);
	}

	void resizeTo(u32 numElements)
	{
		writeCommand("resizeTo", numElements);
		_naives.resize(numElements);
		write("\n");
		_corrects.resize(numElements);
		write("\n");
		_complex.resize(numElements);
	}

	void shrinkToFit()
	{
		writeCommand("shrinkToFit");

		_naives.shrink_to_fit();
		write("\n");
		_corrects.shrink_to_fit();
		write("\n");

		_complex.shrink_to_fit();
	}

	void clear()
	{
		writeCommand("clear", _naives.size());
		_naives.clear();
		write("\n");
		_corrects.clear();
		write("\n");
		_complex.clear();
	}

	void eraseFromFront(u32 numElements)
	{
		const u32 prev = static_cast<u32>(_naives.size());
		writeCommand("eraseFromFront", prev, prev-numElements);
		_naives.erase(_naives.begin(), _naives.begin() + numElements);
		write("\n");
		_corrects.erase(_corrects.begin(), _corrects.begin() + numElements);
		write("\n");
		_complex.erase(_complex.begin(), _complex.begin() + numElements);
	}

	using TupleState = std::tuple<std::vector<NaiveElement>, std::vector<CorrectElement>, std::vector<ComplexElement>>;

	TupleState cloneToOutput()
	{
		return { _naives, _corrects, _complex };
	}

	void populateByMove(TupleState&& incoming)
	{
		_naives = std::move(std::get<0>(incoming));
		_corrects = std::move(std::get<1>(incoming));
		_complex = std::move(std::get<2>(incoming));
	}

	template<typename Predicate>
	void unstableEraseUsingPartition(Predicate predicate)
	{
		writeCommand("unstableEraseUsingPartition");

		{
			auto pivot = std::partition(_naives.begin(), _naives.end(), std::not_fn(predicate));
			const u32 newSize = static_cast<u32>(std::distance(_naives.begin(), pivot));
			_naives.resize(newSize);
		}
		write("\n");
		{
			auto pivot = std::partition(_corrects.begin(), _corrects.end(), std::not_fn(predicate));
			const u32 newSize = static_cast<u32>(std::distance(_corrects.begin(), pivot));
			_corrects.resize(newSize);
		}
		write("\n");
		{
			auto pivot = std::partition(_complex.begin(), _complex.end(), std::not_fn(predicate));
			const u32 newSize = static_cast<u32>(std::distance(_complex.begin(), pivot));
			_complex.resize(newSize);
		}
	}

	template<typename Predicate>
	void unstableEraseUsingLoop(Predicate&& predicate)
	{
		writeCommand("unstableEraseUsingLoop");

		{
			auto newSize = utility::unstableEraseUsingLoop(_naives, predicate);
			_naives.resize(newSize);
		}
		write("\n");
		{
			auto newSize = utility::unstableEraseUsingLoop(_corrects, predicate);
			_corrects.resize(newSize);
		}
		write("\n");
		{
			auto newSize = utility::unstableEraseUsingLoop(_complex, predicate);
			_complex.resize(newSize);
		}
	}

	void printEntries()
	{
		writeCommand("PrintEntries:");
		//std::vector<NaiveElement>::value_type& foo = _naives[0];

		for (auto& e : _naives)
			printf("%u, ", e.dummyData);
		write("\n");
		for (auto& e : _corrects)
			printf("%u, ", e.dummyData);
		write("\n");
		for (auto& e : _complex)
			printf("%u, ", e.dummyData);
	}


private:
	std::vector<NaiveElement> _naives;
	std::vector<CorrectElement> _corrects;
	std::vector<ComplexElement> _complex;
};

inline void runVectorExample()
{
	VectorExample wrapper;

	writeDescription("[reserve] will move/copy elements");
	wrapper.resizeTo(4);
	wrapper.reserve(10);

	writeDescription("[resize] upsizing: if insufficient memory --> move to new memory location");
	wrapper.resizeTo(10);
	wrapper.resizeTo(20);

	writeDescription("[resize] downsizing will not move elements");
	wrapper.resizeTo(19);
	wrapper.resizeTo(10);

	writeDescription("[shrinkToFit] might move elements into a specific memory area with exact size (TODO: INSERT_LINK_TO_STANDARD)");
	wrapper.shrinkToFit();
	wrapper.resizeTo(5);
	wrapper.shrinkToFit();
	wrapper.shrinkToFit();

	writeDescription("[erase] will use assignment operator");
	wrapper.resizeTo(10);
	wrapper.eraseFromFront(2);

	writeDescription("[cloneToOutput] will use copy operator");
	wrapper.resizeTo(10);
	auto state = wrapper.cloneToOutput();

	writeDescription("[unstableEraseIf] will use assignment operator");
	wrapper.unstableEraseUsingPartition([](auto&& a) -> bool { return a.dummyData == 4 || a.dummyData == 25; });

	writeDescription("[populateByMove] will use MoveConstructor");
	wrapper.populateByMove(std::move(state));

	writeDescription("[unstableEraseUsingLoop] will use assignment operator");
	wrapper.unstableEraseUsingLoop([](auto&& a) -> bool { return a.dummyData == 4 || a.dummyData == 25; });

	wrapper.printEntries();

	writeDescription("[LEAVE_SCOPE]");
}