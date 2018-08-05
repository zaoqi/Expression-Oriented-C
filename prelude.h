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
#ifndef _HEAD_prelude_static_//_HEAD_prelude_static_
#define _HEAD_prelude_static_


#ifdef __cplusplus
#  define _HELPER_prelude_inline_ 1
#  define _HELPER_prelude_staticDefine_inlineDefine_ inline
#  define _HELPER_prelude_externDefine_inlineDefine_ inline
#  define _HELPER_prelude_externDeclare_inlineDefine_ inline
#else
#  if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#    define _HELPER_prelude_inline_ 1
#    define _HELPER_prelude_staticDefine_inlineDefine_ static inline
#    define _HELPER_prelude_externDefine_inlineDefine_ extern inline
#    define _HELPER_prelude_externDeclare_inlineDefine_ inline
#  else
#    define _HELPER_prelude_inline_ 0
#    define _HELPER_prelude_staticDefine_inlineDefine_ static
#    define _HELPER_prelude_externDefine_inlineDefine_ extern
#    define _HELPER_prelude_externDeclare_inlineDefine_ ERROR_HELPER_prelude_externDeclare_inlineDefine_
#  endif
#endif

#define define_type typedef

#define _HELPER_prelude_global_nothing_
#define id(x) x

#if defined(__cplusplus)||defined(__STDBOOL_H)||defined(bool)||defined(true)||defined(false)
#else
#  define true 1
#  define false 0
#endif

#define ref(x) ((x)*)
#define un_ref(x) (*(x))
#define to_ref(x) (&(x))
#define ref_any (void*)

#define eq_p(x,y) x==y

_HELPER_prelude_staticDefine_inlineDefine_ void make_void(){}

#define record(x) struct x;typedef struct x x;struct x
#define anonymous_record struct
#define enumeration(x) enum x;typedef enum x x;enum x
#define anonymous_enumeration enum

//let_cc(t,x)({ ... });
#define let_cc(t, x) _HELPER_prelude_let_cc_A_(t, x) _HELPER_prelude_let_cc_B_
#define _HELPER_prelude_let_cc_A_(t, x) ({ \
	t _TEMP_prelude_let_cc_return_value_; \
	t _TEMP_prelude_let_cc_value_##x##_; \
	goto _TEMP_prelude_let_cc_do_##x##_; \
	_TEMP_prelude_let_cc_out_##x##_: \
	_TEMP_prelude_let_cc_return_value_= _TEMP_prelude_let_cc_value_##x##_; \
	goto _TEMP_prelude_let_cc_return_label_; \
	_TEMP_prelude_let_cc_do_##x##_:
#define _HELPER_prelude_let_cc_B_(value) \
	_TEMP_prelude_let_cc_return_value_=(value); \
	_TEMP_prelude_let_cc_return_label_: \
	_TEMP_prelude_let_cc_return_value_;})
#define throw(t, x, v) ({ \
	_TEMP_prelude_let_cc_value_##x##_=v; \
	goto _TEMP_prelude_let_cc_out_##x##_; \
	t _TEMP_prelude_let_cc_throw_; \
	_TEMP_prelude_let_cc_throw_; })

/*if_then_else(b)({...})({...});*/
#define if_then_else(b) ((b)? _HELPER_prelude_if_then_else_A_
#define _HELPER_prelude_if_then_else_A_(b) (b): _HELPER_prelude_if_then_else_B_
#define _HELPER_prelude_if_then_else_B_(b) (b))

/*例 lambda(int, int x, int y)({x+y;}) */
#define lambda(return_type, ...) ({return_type _TEMP_prelude_lambda_(__VA_ARGS__) _HELPER_prelude_lambda_
#define _HELPER_prelude_lambda_(value) {return (value);}_TEMP_prelude_lambda_;})

/*参考https://blog.csdn.net/u011787119/article/details/53815950*/
#define _HELPER_prelude_ATTR_(args) args
#define _HELPER_prelude_COUNT_PARMS_IMP_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NUM, ...) NUM
#define _HELPER_prelude_COUNT_PARMS_(...) _HELPER_prelude_ATTR_(_HELPER_prelude_COUNT_PARMS_IMP_(__VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define _HELPER_prelude_SYMBOL_CATENATE_(arg1, arg2) arg1 ## arg2
#define _HELPER_prelude_SYMBOL_CATENATE_WITH_MACRO_(arg1, arg2) _HELPER_prelude_SYMBOL_CATENATE_(arg1, arg2)

#define define_private(...) \
	_HELPER_prelude_ATTR_( \
		_HELPER_prelude_SYMBOL_CATENATE_WITH_MACRO_(_HELPER_prelude_define_private, _HELPER_prelude_COUNT_PARMS_(__VA_ARGS__)) \
		(__VA_ARGS__))
#define define_public(...) \
	_HELPER_prelude_ATTR_( \
		_HELPER_prelude_SYMBOL_CATENATE_WITH_MACRO_(_HELPER_prelude_define_public, _HELPER_prelude_COUNT_PARMS_(__VA_ARGS__)) \
		(__VA_ARGS__))

#define declare_public(t, n) extern t n
#define _HELPER_prelude_function_(value) {return (value);}
#define _HELPER_prelude_ignore_(x) _HELPER_prelude_global_nothing_


#endif//_HEAD_prelude_static_

#undef declare_private
#undef _HELPER_prelude_define_private2
#undef _HELPER_prelude_define_private3
#undef _HELPER_prelude_define_public2
#undef _HELPER_prelude_define_public3
#ifdef _EOC_require_
#  define declare_private(t, n) _HELPER_prelude_global_nothing_
#  define _HELPER_prelude_define_private3(t, n, x) _HELPER_prelude_global_nothing_
#  define _HELPER_prelude_define_public3(t, n, x) declare_public(t, n)
#  define _HELPER_prelude_define_private2(t, n) _HELPER_prelude_global_nothing_
#  define _HELPER_prelude_define_public2(t, n) declare_public(t, n)
#else
#  define declare_private(t, n) static t n
#  define _HELPER_prelude_define_private3(t, n, x) static t n=x
#  define _HELPER_prelude_define_public3(t, n, x) declare_public(t, n);t n=x
#  define _HELPER_prelude_define_private2(t, n) static t n
#  define _HELPER_prelude_define_public2(t, n) declare_public(t, n);t n
#endif

/*例
define_private_function(int add(int x, int y))({
	x+y;
});*/

#undef declare_private_function
#undef define_private_function
#undef declare_public_function
#undef define_public_function
#undef declare_private_inline_function
#undef define_private_inline_function
#undef declare_public_inline_function
#undef define_public_inline_function
#ifdef _EOC_require_
#  define declare_private_function(retnameargs) _HELPER_prelude_global_nothing_
#  define define_private_function(retnameargs) _HELPER_prelude_ignore_
#  define declare_public_function(retnameargs) extern retnameargs
#  define define_public_function(retnameargs) extern retnameargs; _HELPER_prelude_ignore_
#  define declare_private_inline_function(retnameargs) _HELPER_prelude_global_nothing_
#  define define_private_inline_function(retnameargs) _HELPER_prelude_ignore_
#  if _HELPER_prelude_inline_
#    define declare_public_inline_function(retnameargs) _HELPER_prelude_externDeclare_inlineDefine_ retnameargs
#    define define_public_inline_function(retnameargs) _HELPER_prelude_externDeclare_inlineDefine_ retnameargs _HELPER_prelude_function_
#  else
#    define declare_public_inline_function(retnameargs) declare_public_function(retnameargs)
#    define define_public_inline_function(retnameargs) declare_public_function(retnameargs); _HELPER_prelude_ignore_
#  endif
#else
#  define declare_private_function(retnameargs) static retnameargs
#  define define_private_function(retnameargs) static retnameargs _HELPER_prelude_function_
#  define declare_public_function(retnameargs) extern retnameargs
#  define define_public_function(retnameargs) extern retnameargs _HELPER_prelude_function_
#  if _HELPER_prelude_inline_
#    define declare_private_inline_function(retnameargs) static inline retnameargs
#    define define_private_inline_function(retnameargs) static inline retnameargs _HELPER_prelude_function_
#    define declare_public_inline_function(retnameargs) _HELPER_prelude_externDefine_inlineDefine_ retnameargs
#    define define_public_inline_function(retnameargs) _HELPER_prelude_externDefine_inlineDefine_ retnameargs _HELPER_prelude_function_
#  else
#    define declare_private_inline_function(retnameargs) declare_private_function(retnameargs)
#    define define_private_inline_function(retnameargs) define_private_function(retnameargs)
#    define declare_public_inline_function(retnameargs) declare_public_function(retnameargs)
#    define define_public_inline_function(retnameargs) define_public_function(retnameargs)
#  endif
#endif
