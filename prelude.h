/*
    Copyright (C) 2018  Zaoqi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _HEAD_prelude_
#define _HEAD_prelude_


#define define_type typedef

#define true 1
#define false 0

#define ref(x) ((x)*)
#define un_ref(x) (*(x))
#define to_ref(x) (&(x))
#define ref_any (void*)

#define eq_p(x,y) x==y

#define INLINE static inline
INLINE void make_void(){}

#define declare_private(t, n) static t n
#define declare_public(t, n) extern t n
#define define_private(t, n, x) declare_private(t, n);t n=x
#define define_public(t, n, x) declare_public(t, n);t n=x
#define define_private_zero(t, n) declare_private(t, n);t n
#define define_public_zero(t, n) declare_public(t, n);t n

//例子
//define_private_function(int add(int x, int y))({
//	x+y;
//});
#define _HELPER_prelude_function_(value) {return value;}
#define declare_private_function(retnameargs) static retnameargs
#define define_private_function(retnameargs) static retnameargs _HELPER_prelude_function_
#define declare_public_function(retnameargs) extern retnameargs
#define define_public_function(retnameargs) extern retnameargs _HELPER_prelude_function_
#define declare_inline_function(retnameargs) INLINE retnameargs
#define define_inline_function(retnameargs) INLINE retnameargs _HELPER_prelude_function_

#define record(x) struct x;typedef struct x x;struct x
#define anonymous_record struct
#define enumeration(x) enum x;typedef enum x x;enum x
#define anonymous_enumeration enum

//let_cc(t,x)({ ... });
// static ref_any _TEMP_let_cc_;
//_TEMP_let_cc_state_##x##_ 
//	false 运行
//	true 正常返回，中断（都已写入_TEMP_let_cc_##x##_）
#define let_cc(t, x) _HELPER_prelude_let_cc_A_(t, x) _HELPER_prelude_let_cc_B_
#define _HELPER_prelude_let_cc_A_(t, x) ((t)({\
	t _TEMP_let_cc_##x##_; \
	unsigned char _TEMP_let_cc_state_##x##_=false; \
	_TEMP_let_cc_out_##x##_: \
	while(true){ \
		if(_TEMP_let_cc_state_##x##_){ \
			_TEMP_let_cc_=&_TEMP_let_cc_##x##_; \
			break;} \
		_TEMP_let_cc_##x##_=
#define _HELPER_prelude_let_cc_B_(value) (value);_TEMP_let_cc_state_##x##_=true;}*_TEMP_let_cc_;}))
#define throw(x, v) ({_TEMP_let_cc_##x##_=v;_TEMP_let_cc_state_##x##_=true;goto _TEMP_let_cc_out_##x##_;*((void*)0);})


#endif
