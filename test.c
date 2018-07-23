#include "prelude.h"
A(define_private_function(int add(int x, int y))L
	x+y;
J)
A(define_private_function(void mkvoid2())L
	make_void();
J)
A(define_public_function(int main())L
	mkvoid2();
	0;
J)
A(define_public_function(int f_cc(int x))L
	A(let_cc(int, r)L
		x?0:throw(r, 1);
		2;
	J)
J)
