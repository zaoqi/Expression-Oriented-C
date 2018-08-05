#include "module<"
#include "stdio.h"
define_public_function(int add1(int x))({
	lambda(int)(x+1)();
})
define_public_function(int main())({
	int (*f)(int)=add1;
	printf("%d\n", f(1));
	0;
})
#include ">module"
