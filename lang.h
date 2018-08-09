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
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(__cplusplus) && __cplusplus >= 201103L)
#else
#	error "need C99 or later or C++11 or later"
#endif

#ifndef EOC_TEMP_static/* EOC_TEMP_static */
#define EOC_TEMP_static

#define EOC_HELPER_nothing
#define EOC_HELPER_error(x) ERROR x ERROR

#ifdef __cplusplus
#	define EOC_HELPER_staticDefine_inlineDefine static
#	define EOC_HELPER_externDefine_inlineDefine inline
#	define EOC_HELPER_externDeclare_inlineDefine inline
#elif defined(__STDC_VERSION__)
#	define EOC_HELPER_staticDefine_inlineDefine static inline
#	define EOC_HELPER_externDefine_inlineDefine extern inline
#	define EOC_HELPER_externDeclare_inlineDefine inline
#else
#	error ""
#endif

#define define_type typedef

#if defined(__cplusplus)
#	define restrict
#	include <cstddef>
	using std::size_t;
	using std::ptrdiff_t;
#	include <cstdint>
	using std::int_least8_t;
	using std::int_least16_t;
	using std::int_least32_t;
	using std::int_least64_t;
	using std::uint_least8_t;
	using std::uint_least16_t;
	using std::uint_least32_t;
	using std::uint_least64_t;
	using std::uintptr_t;
	using std::intptr_t;
#elif defined(__STDC_VERSION__)
#	include <stddef.h>
#	include <stdint.h>
#else
#	error ""
#endif
#define int8 int_least8_t
#define int16 int_least16_t
#define int32 int_least32_t
#define int64 int_least64_t
#define nat8 uint_least8_t
#define nat16 uint_least16_t
#define nat32 uint_least32_t
#define nat64 uint_least64_t
#define ptr_t uintptr_t
#define byte nat8
#define signed_byte int8

#define ref(x) ((x)*)
#define un_ref(x) (*(x))
#define to_ref(x) (&(x))
#define ref_any (void*)

#define cast(x, t) ((t)x)
#define eq_p(x,y) ((x)==(y))
#define not_eq_p(x,y) ((x)!=(y))
#define not(x) (!(x))
#define and(x, y) ((x)&&(y))
#define or(x, y) ((x)||(y))

EOC_HELPER_staticDefine_inlineDefine void make_void(void){}

#define declare_record(x) struct x;typedef struct x x
#define define_record(x) declare_record(x);struct x
#define anonymous_record struct
#define declare_enumeration(x) enum x;typedef enum x x
#define define_enumeration(x) declare_enumeration(x);enum x
#define anonymous_enumeration enum

#if defined(__cplusplus)
#elif defined(__STDC_VERSION__)
#	include <stdbool.h>
#else
#	define bool unsigned char
#	define true 1
#	define false 0
#	define __bool_true_false_are_defined 1
#endif

#define id(x) x

//let_cc(t,x)({ ... });
#define let_cc(t, x) EOC_HELPER_let_cc_A(t, x) EOC_HELPER_let_cc_B
#define EOC_HELPER_let_cc_A(t, x) ({ \
	t EOC_TEMP_let_cc_return_value; \
	t EOC_TEMP_let_cc_value_##x##; \
	goto EOC_TEMP_let_cc_do_##x##; \
	EOC_TEMP_let_cc_throw##x##: \
	EOC_TEMP_let_cc_return_value= EOC_TEMP_let_cc_value_##x##; \
	goto EOC_TEMP_let_cc_return_label; \
	EOC_TEMP_let_cc_do_##x##:
#define EOC_HELPER_let_cc_B(value) \
	EOC_TEMP_let_cc_return_value=(value); \
	EOC_TEMP_let_cc_return_label: \
	EOC_TEMP_let_cc_return_value;})
#define throw(t, x, v) ({ \
	EOC_TEMP_let_cc_value_##x##=v; \
	goto EOC_TEMP_let_cc_throw##x##; \
	t EOC_TEMP_throw; \
	EOC_TEMP_throw;})

/*if_then_else(b)({...})({...});*/
#define if_then_else(b) ((b)? EOC_HELPER_if_then_else_A
#define EOC_HELPER_if_then_else_A(b) (b): EOC_HELPER_if_then_else_B
#define EOC_HELPER_if_then_else_B(b) (b))

/*例 lambda(int, int x, int y)({x+y;}) */
/* GCC */
#define lambda(return_type, ...) ({return_type EOC_TEMP_lambda EOC_HELPER_function_args(__VA_ARGS__) EOC_HELPER_lambda
#define EOC_HELPER_lambda(value) {return (value);}EOC_TEMP_lambda;})

/*参考https://blog.csdn.net/u011787119/article/details/53815950*/
#define EOC_HELPER_attr(args) args
#define EOC_HELPER_count_parms_helper(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NUM, ...) NUM
#define EOC_HELPER_count_parms_A(...) EOC_HELPER_attr(EOC_HELPER_count_parms_helper(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define EOC_HELPER_count_parms(...) EOC_HELPER_count_parms_A(_none, ## __VA_ARGS__)
#define EOC_HELPER_symbol_append(arg1, arg2) arg1 ## arg2
#define EOC_HELPER_symbol_append_with_macro(arg1, arg2) EOC_HELPER_symbol_append(arg1, arg2)

#define EOC_HELPER_count_parms_assert0()
#define EOC_HELPER_count_parms_assert1() EOC_HELPER_error("this compiler does not offers an extension that allows ## to appear after a comma and before __VA_ARGS__ , in which case the ## does nothing when __VA_ARGS__ is non-empty, but removes the comma when __VA_ARGS__ is empty")
EOC_HELPER_attr(EOC_HELPER_symbol_append_with_macro(EOC_HELPER_count_parms_assert, EOC_HELPER_count_parms()) ())

#define var(...) \
	EOC_HELPER_attr( \
		EOC_HELPER_symbol_append_with_macro(EOC_HELPER_var, EOC_HELPER_count_parms(__VA_ARGS__)) \
		(__VA_ARGS__))
#define EOC_HELPER_var2(ider, t) t ider
#define EOC_HELPER_var1(ider) auto ider
#define var_lambda(ider, ret, ...) ret (*ider) EOC_HELPER_function_args(__VA_ARGS__)

#define EOC_HELPER_global_nothing
#define EOC_HELPER_function(x) {return (x);}
#define EOC_HELPER_global_ignore(x) EOC_HELPER_global_nothing
#ifdef __cplusplus /* __cplusplus */
#define EOC_HELPER_function_args(...) (__VA_ARGS__)
#else /* __cplusplus */
#define EOC_HELPER_function_args(...) EOC_HELPER_attr(EOC_HELPER_function_args_A(__VA_ARGS__))
#define EOC_HELPER_function_args_A(...) \
	EOC_HELPER_attr( \
		EOC_HELPER_symbol_append_with_macro(EOC_HELPER_function_args, EOC_HELPER_count_parms(__VA_ARGS__)) \
		(__VA_ARGS__))
#define EOC_HELPER_function_args0() (void)
#define EOC_HELPER_function_args1(...) (__VA_ARGS__)
#define EOC_HELPER_function_args2(...) (__VA_ARGS__)
#define EOC_HELPER_function_args3(...) (__VA_ARGS__)
#define EOC_HELPER_function_args4(...) (__VA_ARGS__)
#define EOC_HELPER_function_args5(...) (__VA_ARGS__)
#define EOC_HELPER_function_args6(...) (__VA_ARGS__)
#define EOC_HELPER_function_args7(...) (__VA_ARGS__)
#define EOC_HELPER_function_args8(...) (__VA_ARGS__)
#define EOC_HELPER_function_args9(...) (__VA_ARGS__)
#define EOC_HELPER_function_args10(...) (__VA_ARGS__)
#endif /* __cplusplus */

#define define_private(...) \
	EOC_HELPER_attr( \
		EOC_HELPER_symbol_append_with_macro(EOC_HELPER_define_private, EOC_HELPER_count_parms(__VA_ARGS__)) \
		(__VA_ARGS__))
#define define_public(...) \
	EOC_HELPER_attr( \
		EOC_HELPER_symbol_append_with_macro(EOC_HELPER_define_public, EOC_HELPER_count_parms(__VA_ARGS__)) \
		(__VA_ARGS__))

#define declare_public(ider, t) extern t ider
#define declare_public_lambda(ider, ret, ...) extern ret ider EOC_HELPER_function_args(__VA_ARGS__)
#endif/* EOC_TEMP_static */
/* 有
EOC_require
EOC_TEMP_state
	0 require
	1 define
*/
#undef EOC_TEMP_define
#undef EOC_TEMP_define_re
#if defined(EOC_TEMP_state)
#	if (EOC_TEMP_state==1 && defined(EOC_require)) || (EOC_TEMP_state==0 && !defined(EOC_require))
#		define EOC_TEMP_define EOC_HELPER_nothing
#		define EOC_TEMP_define_re EOC_HELPER_nothing
#	endif
#else
#	define EOC_TEMP_define
#endif
#if defined(EOC_TEMP_define)/* EOC_TEMP_define */
#ifdef EOC_require
#	define EOC_TEMP_state 0
#else
#	define EOC_TEMP_state 1
#endif
#if defined(EOC_TEMP_define_re)/* EOC_TEMP_define_re */
#undef declare_private
#undef EOC_HELPER_define_private2
#undef EOC_HELPER_define_private3
#undef EOC_HELPER_define_public2
#undef EOC_HELPER_define_public3
#undef declare_private_lambda
#undef define_private_lambda
#undef declare_private_inline_lambda
#undef define_private_inline_lambda
#undef declare_public_lambda
#undef define_public_inline_lambda
#endif/* EOC_TEMP_define_re */
#ifdef EOC_require/* EOC_require */
#define declare_private(ider, t) EOC_HELPER_global_nothing
#define EOC_HELPER_define_private2(ider, t) EOC_HELPER_global_nothing
#define EOC_HELPER_define_private3(ider, t, x) EOC_HELPER_global_nothing
#define EOC_HELPER_define_public2(ider, t) declare_public(ider, t)
#define EOC_HELPER_define_public3(ider, t, x) declare_public(ider, t)
#define declare_private_lambda(ider, ret, ...) EOC_HELPER_global_nothing
#define define_private_lambda(ider, ret, ...) EOC_HELPER_global_ignore
#define declare_private_inline_lambda(ider, ret, ...) EOC_HELPER_global_nothing
#define define_private_inline_lambda(ider, ret, ...) EOC_HELPER_global_ignore
#define define_public_lambda(ider, ret, ...) EOC_HELPER_attr(declare_public_lambda(ider, ret, __VA_ARGS__)); EOC_HELPER_global_ignore
#define define_public_inline_lambda(ider, ret, ...) EOC_HELPER_externDeclare_inlineDefine ret ider EOC_HELPER_function_args(__VA_ARGS__) EOC_HELPER_function
#else/* EOC_require */
#define declare_private(ider, t) static t ider
#define EOC_HELPER_define_private2(ider, t) static t ider
#define EOC_HELPER_define_private3(ider, t, x) static t ider=x
#define EOC_HELPER_define_public2(ider, t) t ider
#define EOC_HELPER_define_public3(ider, t, x) t ider=x
#define declare_private_lambda(ider, ret, ...) static ret ider EOC_HELPER_function_args(__VA_ARGS__)
#define define_private_lambda(ider, ret, ...) static ret ider EOC_HELPER_function_args(__VA_ARGS__) EOC_HELPER_function
#define declare_private_inline_lambda(ider, ret, ...) EOC_HELPER_staticDefine_inlineDefine ret ider EOC_HELPER_function_args(__VA_ARGS__)
#define define_private_inline_lambda(ider, ret, ...) EOC_HELPER_staticDefine_inlineDefine ret ider EOC_HELPER_function_args(__VA_ARGS__) EOC_HELPER_function
#define define_public_lambda(ider, ret, ...)  extern ret ider EOC_HELPER_function_args(__VA_ARGS__) EOC_HELPER_function
#define define_public_inline_lambda(ider, ret, ...) EOC_HELPER_externDefine_inlineDefine ret ider EOC_HELPER_function_args(__VA_ARGS__) EOC_HELPER_function
#endif/* EOC_require */
#endif/* EOC_TEMP_define */
