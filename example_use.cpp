// compile with C++20
#include <algorithm>
#include <array>
#include <iostream>
#include "λ.hpp"

using namespace std;

// Wrapper type for printing ranges as comma seperated lists
template<typename R> struct range_printer {const R& r;};
template<typename R> ostream& operator<<(ostream& os, const range_printer<R>& rp);

int main() {
	array arr{8, 5, 4, 2, 9, 6, 7, 3, 1};

	// ranges::sort takes a comparison function with two parameters.
	ranges::sort(arr, λ(_1 > _2));
	cout << "sorted array:\n";
	cout << range_printer{arr} << "\n\n";
	// > sorted array:
	// > 9, 8, 7, 6, 5, 4, 3, 2, 1

	// ranges::find_if takes a predicate function with one parameter. For
	// convenience "_" may be used as an alias for "_1".
	auto e = *ranges::find_if(arr, λ(_ < 4));
	cout << "first element less than 4:\n";
	cout << e << "\n\n";
	// > first element less than 4:
	// > 3

	// note that trying to use an unexpected parameter results in a compile error.
	// auto e = *ranges::find_if(arr, λ(_2 < 4)); // illegal
	// > error: invalid operands to binary expression ('λ::unassigned' and 'int')
	// >     auto e = *ranges::find_if(arr, λ(_2 < 4));
	// >                                      ~~ ^ ~

	// λ expressions implicitly capture local variables by value.
	auto n = ranges::count_if(arr, λ(_ % e == 0));
	cout << "number of elements divisible by " << e << '\n';
	cout << n << "\n\n";
	// > number of elements divisible by 3
	// > 3

	// ranges::transform takes an unary operation, but not all parameters need to
	// be used in the λ expression.
	ranges::transform(arr, arr.data(), λ(0));
	cout << "array filled with zeros:\n";
	cout << range_printer{arr} << '\n';
	// > array filled with zeros:
	// > 0, 0, 0, 0, 0, 0, 0, 0, 0
}

template<typename R> ostream& operator<<(ostream& os, const range_printer<R>& rp) {
	for (const auto& val : rp.r) {
		if (&val != rp.r.begin()) os << ", ";
		os << val;
	}
	return os;
}
