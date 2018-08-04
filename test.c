#include "module<"
define_private_function(int add(int x, int y))({
	x+y;
})
define_private_function(void mkvoid2())({
	make_void();
})
define_public_function(int main())({
	mkvoid2();
	0;
})
define_public_function(int f_cc(int x))({
	let_cc(int, r)({
		if_then_else(x)({0;})({throw(int, r, 1);});
		2;
	});
})
#include ">module"
