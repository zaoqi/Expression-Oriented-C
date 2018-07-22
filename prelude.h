/*
    語: The Language
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


#define the(t, x) t x

#define true 0
#define false 1
typedef char bool;
#define Ref(x) ((x)*)
#define unRef(x) (*(x))
#define toRef(x) (&(x))
#define RefAny (void*)

#define eq_p(x,y) x==y

#define declare_private(t, n) static t n
#define declare_public(t, n) extern t n
#define define_private(t, n, x) declare_private(t, n);t n=x
#define define_public(t, n, x) declare_public(t, n);t n=x
#define define_private_zero(t, n) declare_private(t, n);t n
#define define_public_zero(t, n) declare_public(t, n);t n

#define declare_function_private(ret, nameargs) static ret nameargs
#define define_function_private(ret, nameargs, value) static ret nameargs{return (value);}
#define declare_function_public(ret, nameargs) extern ret nameargs
#define define_function_public(ret, nameargs, value) extern ret nameargs{return (value);}
#define declare_function_inline(ret, nameargs) inline ret nameargs
#define define_function_inline(ret, nameargs, value) inline ret nameargs{return (value);}

#define declare_doer_private(nameargs) static void nameargs
#define define_doer_private(nameargs, body) static void nameargs{body}
#define declare_doer_public(nameargs) extern void nameargs
#define define_doer_public(nameargs, body) extern void nameargs{body}
#define declare_doer_inline(nameargs) inline void nameargs
#define define_doer_inline(nameargs, body) inline void nameargs{body}

#define record(x) struct x;typedef struct x x;struct x
#define anonymous_record struct
#define enumeration(x) enum x;typedef enum x x;enum x
#define anonymous_enumeration enum

#define let_cc(t, x, body) ({t _LET_CC_##x;_LET_CC_##x=(body);_LET_CC_LABEL_##x:_LET_CC_##x;})
#define throw(x, v) ({_LET_CC_##x=v;goto _LET_CC_LABEL_##x;*((void*)0);})
#define let_cc_doer(x, body) body _LET_CC_LABEL_##x:
#define throw_doer(x) goto _LET_CC_LABEL_##x


#endif
