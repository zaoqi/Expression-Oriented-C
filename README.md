# 安装

复制文件```
module<
>module
require<
>require
```。

# 模块

```C
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
```

一个模块以`#include "module<"`开始，`#include ">module"`结束。

# 导入

```C
#include "require<"
#include "test.c"
#include ">require"
```

导入`#include "require<"`开始，`#include ">require"`结束。直接include `*.c`文件。

# 物
+ `record(名字){...};` 代替struct。自动 typedef struct 名字 名字;
+ `enumeration(名字){...};` 类似record
+ `define_type` typedef
+ `define_private_function` `define_public_function` `define_private_inline_function` `define_public_inline_function` 定义函数。
+ `({ ... })` 最后一行作为值，无需return等
