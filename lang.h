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
#	error "requires C99 or later or C++11 or later"
#endif

#ifndef EOC_TEMP_static/* EOC_TEMP_static */
#define EOC_TEMP_static

#define EOC_HELPER_nothing

#ifdef __cplusplus
#	define EOC_HELPER_staticDefine_inlineDefine static
#	define EOC_HELPER_externDefine_inlineDefine inline
#	define EOC_HELPER_externDeclare_inlineDefine inline
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	define EOC_HELPER_staticDefine_inlineDefine static inline
#	define EOC_HELPER_externDefine_inlineDefine extern inline
#	define EOC_HELPER_externDeclare_inlineDefine inline
#else
#	error ""
#endif

#define define_type typedef

#if defined(__cplusplus) && __cplusplus >= 201103L
#	define restrict
#	include <cstddef>
	using std::size_t;
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
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	include <stddef.h>
#	include <stdint.h>
#else
#	error "need <stdint.h>"
#endif
#define int8 int_least8_t
#define int16 int_least16_t
#define int32 int_least32_t
#define int64 int_least64_t
#define nat8 uint_least8_t
#define nat16 uint_least16_t
#define nat32 uint_least32_t
#define nat64 uint_least64_t
#define nat_pointer uintptr_t
#define int_pointer intptr_t
#define byte nat8
#define signed_byte int8

#define ref(x) ((x)*)
#define un_ref(x) (*(x))
#define to_ref(x) (&(x))
#define ref_any (void*)

#define cast(x, t) ((t)x)
#define eq_p(x,y) ((x)==(y))
#define not_eq_p(x,y) ((x)!=(y))
#if !(defined(__cplusplus) || defined(not))
#	define not(x) (!(x))
#endif
#define and2(x, y) ((x)&&(y))
#define and_s(...) EOC_HELPER_reduce(and2, __VA_ARGS__)
#define or2(x, y) ((x)||(y))
#define or_s(...) EOC_HELPER_reduce(or2, __VA_ARGS__)

EOC_HELPER_staticDefine_inlineDefine void make_void(void){}

#define declare_record(x) struct x;typedef struct x x
#define define_record(x) declare_record(x);struct x
#define anonymous_record struct
#define declare_enumeration(x) enum x;typedef enum x x
#define define_enumeration(x) declare_enumeration(x);enum x
#define anonymous_enumeration enum

#if defined(__cplusplus)
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#	include <stdbool.h>
#else
#	define bool unsigned char
#	define true 1
#	define false 0
#	define __bool_true_false_are_defined 1
#endif

#define id(x) x

/* let_current_continuation_notFirstClass(x,t)({ ... }); */
#define let_current_continuation_notFirstClass(x,t) EOC_HELPER_let_cc_A(t, x) EOC_HELPER_let_cc_B
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
/* continuation_notFirstClass_throw(x,v,t) t是表达式本身的 */
#define continuation_notFirstClass_throw(x,v,t) ({ \
	EOC_TEMP_let_cc_value_##x##=v; \
	goto EOC_TEMP_let_cc_throw##x##; \
	t EOC_TEMP_throw; \
	EOC_TEMP_throw;})

/* if_then_else(b)({...})({...}); */
#define if_then_else(b) ((b)? EOC_HELPER_if_then_else_A
#define EOC_HELPER_if_then_else_A(b) (b): EOC_HELPER_if_then_else_B
#define EOC_HELPER_if_then_else_B(b) (b))

/* 例 lambda(int, int x)({x+y;}) */
/* 例 lambda_withTypeOfBody(int, int x __ int)({x+y;}) */
#if defined(__cplusplus) && __cplusplus >= 201103L
#	define lambda(...) [&](__VA_ARGS__) EOC_HELPER_lambda
#	define lambda_withTypeOfBody(...) [&](EOC_HELPER_init(__VA_ARGS__))->EOC_HELPER_tail(__VA_ARGS__) EOC_HELPER_lambda
#	define EOC_HELPER_lambda(x) {return (x);}
#else
#	define lambda(...) EOC_HELPER_error("lambda requires C++11 or later, lambda_withTypeOfBody requires GCC or C++11 or later")
#	if defined(__GNUC__)
#		define lambda_withTypeOfBody(...) \
			({EOC_HELPER_tail(__VA_ARGS__) EOC_TEMP_lambda(EOC_HELPER_init(__VA_ARGS__)) EOC_HELPER_lambda_withTypeOfBody
#		define EOC_HELPER_lambda_withTypeOfBody(x) {return (x);}EOC_TEMP_lambda;})
#	else
#		define lambda_withTypeOfBody(...) EOC_HELPER_error("lambda requires C++11 or later, lambda_withTypeOfBody requires GCC or C++11 or later")
#	endif
#endif
#define __ ,

#define var_lambda_withTypeOfBody(ider, ...) EOC_HELPER_tail(__VA_ARGS__) (*ider)(EOC_HELPER_init(__VA_ARGS__))

#define var(...) EOC_HELPER_with_count(EOC_HELPER_var, __VA_ARGS__)
#define EOC_HELPER_var2(ider, t) t ider
#if defined(__cplusplus) && __cplusplus >= 201103L
#	define EOC_HELPER_var1(ider) auto ider
#else
#	define EOC_HELPER_var1(ider) EOC_HELPER_error("auto requires C++11 or later")
#endif

#define EOC_HELPER_global_nothing
#define EOC_HELPER_global_ignore(x) EOC_HELPER_global_nothing

#define EOC_HELPER_declare_lambda(prefix, ...) EOC_HELPER_with_count(EOC_HELPER_declare_lambda, prefix, __VA_ARGS__)
#define EOC_HELPER_declare_lambda2(prefix, retnameargs) prefix retnameargs;
#define EOC_HELPER_declare_lambda3(prefix, nameargs, ret) prefix ret nameargs;

#define EOC_HELPER_define_lambda(prefix, ...) EOC_HELPER_with_count(EOC_HELPER_define_lambda, prefix, __VA_ARGS__)
#define EOC_HELPER_define_lambda2(prefix, retnameargs) prefix retnameargs EOC_HELPER_define_lambda_B
#define EOC_HELPER_define_lambda3(prefix, nameargs, ret) prefix ret nameargs EOC_HELPER_define_lambda_B
#define EOC_HELPER_define_lambda_B(x) {return (x);}

/* declare_public(var(x, int)) */
#define declare_public(typeid) extern typeid
#define declare_public_lambda(...) EOC_HELPER_declare_lambda(extern, ...)
#define declare_public_inline_lambda(...) EOC_HELPER_declare_lambda(EOC_HELPER_externDeclare_inlineDefine, __VA_ARGS__)

#define define_private(...) EOC_HELPER_with_count(EOC_HELPER_define_private, __VA_ARGS__)
#define define_public(...) EOC_HELPER_with_count(EOC_HELPER_externDefine_inlineDefine, __VA_ARGS__)

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
#undef EOC_TEMP_state
#ifdef EOC_require
#	define EOC_TEMP_state 0
#else
#	define EOC_TEMP_state 1
#endif
#if defined(EOC_TEMP_define_re)/* EOC_TEMP_define_re */
#undef declare_private
#undef EOC_HELPER_define_private1
#undef EOC_HELPER_define_private2
#undef EOC_HELPER_define_public1
#undef EOC_HELPER_define_public2
#undef declare_private_lambda
#undef define_private_lambda
#undef declare_private_inline_lambda
#undef define_private_inline_lambda
#undef define_public_lambda
#undef define_public_inline_lambda
#endif/* EOC_TEMP_define_re */
#ifdef EOC_require/* EOC_require */
#define declare_private(typeid) EOC_HELPER_global_nothing
#define EOC_HELPER_define_private1(typeid) EOC_HELPER_global_nothing
#define EOC_HELPER_define_private2(typeid, x) EOC_HELPER_global_nothing
#define EOC_HELPER_define_public1(typeid) declare_public(typeid)
#define EOC_HELPER_define_public2(typeid, x) declare_public(typeid)
#define declare_private_lambda(...) EOC_HELPER_global_nothing
#define define_private_lambda(...) EOC_HELPER_global_ignore
#define declare_private_inline_lambda(...) EOC_HELPER_global_nothing
#define define_private_inline_lambda(...) EOC_HELPER_global_ignore
#define define_public_lambda(...) declare_public_lambda(__VA_ARGS__); EOC_HELPER_global_ignore
#define define_public_inline_lambda(...) EOC_HELPER_define_lambda(EOC_HELPER_externDeclare_inlineDefine, __VA_ARGS__)
#else/* EOC_require */
#define declare_private(typeid) static typeid
#define EOC_HELPER_define_private1(typeid) static typeid
#define EOC_HELPER_define_private2(typeid, x) static typeid=x
#define EOC_HELPER_define_public1(typeid) typeid
#define EOC_HELPER_define_public2(typeid, x) typeid=x
#define declare_private_lambda(...) EOC_HELPER_declare_lambda(static, __VA_ARGS__)
#define define_private_lambda(...) EOC_HELPER_define_lambda(static, __VA_ARGS__)
#define declare_private_inline_lambda(...) EOC_HELPER_declare_lambda(EOC_HELPER_staticDefine_inlineDefine, __VA_ARGS__)
#define define_private_inline_lambda(...) EOC_HELPER_define_lambda(EOC_HELPER_staticDefine_inlineDefine, __VA_ARGS__)
#define define_public_lambda(...) EOC_HELPER_define_lambda(extern, __VA_ARGS__)
#define define_public_inline_lambda(...) EOC_HELPER_define_lambda(EOC_HELPER_externDefine_inlineDefine, __VA_ARGS__)
#endif/* EOC_require */
#endif/* EOC_TEMP_define */
