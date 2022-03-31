#pragma once

#include <type_traits>
#include <iostream>

//////////////////////////////////////////////
namespace ddahlkvist
{

struct B
{
protected:
   virtual void Foo() {}
};

// Neither trivial nor standard-layout
struct A : B
{
   int a;
   int b;
   void Foo() override {} // Virtual function
};

// Trivial but not standard-layout
struct C
{
   int a;
private:
   int b;   // Different access control
};

// Standard-layout but not trivial
struct D
{
   int a;
   int b;
   D() {} //User-defined constructor
};

struct POD
{
   int a;
   int b;
};

void showcaseCoreTypeTraits()
{
	// AFAIK: as of 2022-03-31
	// is_standard_layout<T> is referring to if the "memory layout" is compatible with a c generated memory layout [different accessors (public, private, protected) would allow the compiler to reorder the elements which would not guarantee stability]
	// is_trivial<T> would specify if the data can be specified without a user specified ctor/dtor [is safe to memcpy]
	// [DEPRECATED] is_pod<T> means both is_trivial<T> and is_standard_layout<T>, is deprecated as of c++20 and replaced with the 2 different type_traits explained above

	using namespace std;

   cout << boolalpha;
   cout << "A is trivial is " << is_trivial<A>() << endl; // false
   cout << "A is standard-layout is " << is_standard_layout<A>() << endl;  // false

   cout << "C is trivial is " << is_trivial<C>() << endl; // true
   cout << "C is standard-layout is " << is_standard_layout<C>() << endl;  // false

   cout << "D is trivial is " << is_trivial<D>() << endl;  // false
   cout << "D is standard-layout is " << is_standard_layout<D>() << endl; // true

   cout << "POD is trivial is " << is_trivial<POD>() << endl; // true
   cout << "POD is standard-layout is " << is_standard_layout<POD>() << endl; // true
}
}