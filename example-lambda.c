#include "module<"
#include "stdio.h"
define_public_function(int main())({
	int (*f)(int)=lambda(int, int x)(x+1);
	printf("%d", f(1));
	0;
})
#include ">module"
