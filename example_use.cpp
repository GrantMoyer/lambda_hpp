// compile with C++20
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <numeric>
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
	// ranges::find_if(arr, λ(_2 < 4)); // illegal
	// > error: invalid operands to binary expression ('λ::unassigned' and 'int')
	// >     ranges::find_if(arr, λ(_2 < 4)); // illegal
	// >                            ~~ ^ ~

	// λ expressions implicitly capture variables by reference.
	auto n = ranges::count_if(arr, λ(_ % e == 0));
	cout << "number of elements divisible by " << e << '\n';
	cout << n << "\n\n";
	// > number of elements divisible by 3
	// > 3

	// ranges::transform takes an unary operation, but not all parameters need to
	// be used in the λ expression.
	ranges::transform(arr, arr.data(), λ(0));
	cout << "array filled with zeros:\n";
	cout << range_printer{arr} << "\n\n";
	// > array filled with zeros:
	// > 0, 0, 0, 0, 0, 0, 0, 0, 0

	// Methods on λ expression parameters can be called like normal.
	array<string, 9> arr2{};
	char c = 'a';
	ranges::for_each(arr2, λ(_.push_back(c++)));
	cout << "array of strings:\n";
	cout << range_printer{arr2} << "\n\n";
	// > array of strings:
	// > a, b, c, d, e, f, g, h, i

	// It's even possible to store a λ expression to an intermediate variable.
	auto join_with_dash = λ(_1 + '-' + _2);
	auto s = reduce(arr2.begin() + 1, arr2.end(), arr2[0], join_with_dash);
	cout << "joined strings:\n";
	cout << s << '\n';
	// > joined strings:
	// > a-b-c-d-e-f-g-h-i
}

template<typename R> ostream& operator<<(ostream& os, const range_printer<R>& rp) {
	for (const auto& val : rp.r) {
		if (&val != rp.r.begin()) os << ", ";
		os << val;
	}
	return os;
}
