#include "prelude.h"
file(
define_private_function(int add(int x, int y))L
	x+y;
J;
define_private_function(void mkvoid2())L
	make_void();
J;
define_public_function(int main())L
	mkvoid2();
	0;
J;
define_public_function(int f_cc(int x))L
	let_cc(int, r)L
		x?0:r(1);
		2;
	J;
J;
)
