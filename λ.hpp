#pragma once

namespace λ {
// "unassigned" is used a placeholder type for unused parameters.
//
// Trying to perform any operation on an unassigned should fail to compile.
struct unassigned {
	// Taking the address of an unassigned parameter should not compile
	void operator&() = delete;
};
}

// λ(expr) can be used as nicer way to write [=](…){return expr;}.
//
// expr may use the implicitly defnined parameters _1, _2, _3, and _4. When
// passed as a function-typed argument, each parameter's type will be deduced
// appropriately. All un-deduced parameters will default to the unassigned
// type, and trying to used them will fail to compile.
#define λ(expr) ( \
	[=]< \
		class T1 = λ::unassigned, \
		class T2 = λ::unassigned, \
		class T3 = λ::unassigned, \
		class T4 = λ::unassigned \
	>(T1 _1 = {}, T2 _2 = {}, T3 _3 = {}, T4 _4 = {}) \
	{auto& _ = _1; return expr;} \
)
