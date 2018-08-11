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
#include <stdio.h>
#define eoc_max 64

#define eq_p(x, y) ((x)==(y))
#define nat unsigned long long
#define string char*

/* 有 #define file "" */
#define echo(x) fputs(x, file)
#define echo_nat(x) fprintf(file, "%u", x)

#define IF IF_
#define ELSE ELSE_
#define ELIF ELIF_
#define ENDIF ENDIF_
#define DEFINE DEFINE_
#define DEFINE_FUNCTION DEFINE_FUNCTION_
#define ERROR ERROR_
#define LINE LINE_
#define IF_(x) echo("#if ");{x}echo("\n");
#define ELSE_ echo("#else\n");
#define ELIF_(x) echo("#elif ");{x}echo("\n");
#define ENDIF_ echo("#endif\n");
#define DEFINE_(x, v) echo("#define ");{x}echo(" ");{v}echo("\n");
#define DEFINE_FUNCTION_(name, args, v) echo("#define ");{name}{args}echo(" ");{v}echo("\n");
#define ERROR_(x) echo("#error ");{x}echo("\n");
#define LINE_(x) {x}echo("\n");

#define String String_
#define X X_
#define Nat Nat_
#define Defined Defined_
#define Not Not_
#define Or Or_
#define And And_
#define Gt Gt_
#define GtEq GtEq_
#define Eq Eq_
#define Lt Lt_
#define LtEq LtEq_
#define String_(x) echo("\"");echo(x);echo("\"");
#define X_(x) echo(x);
#define Nat_(x) echo_nat(x);
#define Defined_(x) echo("defined(");{x}echo(")");
#define Not_(x) echo("(!(");{x}echo("))");
#define Or_(x, y) echo("((");{x}echo(")||(");{y}echo("))");
#define And_(x, y) echo("((");{x}echo(")&&(");{y}echo("))");
#define Gt_(x, y) echo("((");{x}echo(")>(");{y}echo("))");
#define GtEq_(x, y) echo("((");{x}echo(")>=(");{y}echo("))");
#define Eq_(x, y) echo("((");{x}echo(")==(");{y}echo("))");
#define Lt_(x, y) echo("((");{x}echo(")<(");{y}echo("))");
#define LtEq_(x, y) echo("((");{x}echo(")<=(");{y}echo("))");

#define StdC99 And(Defined(X("__STDC_VERSION__")),GtEq(X("__STDC_VERSION__"),X("199901L")))
#define StdC11 And(Defined(X("__STDC_VERSION__")),GtEq(X("__STDC_VERSION__"),X("201112L")))
#define CPlusPlus11 And(Defined(X("__cplusplus")),GtEq(X("__cplusplus"),X("201103L")))

#define WITH_MACRO_VA_ARGS(x) IF(Or(StdC99, CPlusPlus11)){x}ELSE ERROR(X("__VA_ARGS__ requires C99 or later or C++11 or later")) ENDIF

#define Call0(f) {f}X("()")
#define Call1(f, x) {f}X("("){x}X(")")
#define Call2(f, x, y) {f}X("("){x}X(","){y}X(")")
#define Call3(f, x, y, z) {f}X("("){x}X(","){y}X(","){z}X(")")

#define prefix_addbetween_from_to(prefix, addbetween, x, y) { \
	nat a=(x); \
	nat b=(y); \
	X(prefix); \
	Nat(a); \
	if(eq_p(a, b)){ \
	}else if(a<b){ \
		while(a!=b){ \
			a++;/*a<=b*/\
			X(addbetween prefix); \
			Nat(a);} \
	}else{/*a>b*/ \
		while(a!=b){ \
			a--;/*a>=b*/ \
			X(addbetween prefix); \
			Nat(a);}}}
#define var_from_to(x, y) prefix_addbetween_from_to("_", ",", x, y)
#define list_var_from_to(x, y) X("(")prefix_addbetween_from_to("_", ",", x, y)X(")")
#define from_to(x, y) prefix_addbetween_from_to("", ",", x, y)
#define for_in_from_to(v, x, y, body) { \
	nat for_in_from_toTEMPx=(x); \
	nat for_in_from_toTEMPy=(y); \
	{nat v=for_in_from_toTEMPx;{body}} \
	if(eq_p(for_in_from_toTEMPx, for_in_from_toTEMPy)){ \
	}else if(for_in_from_toTEMPx<for_in_from_toTEMPy){ \
		while(for_in_from_toTEMPx!=for_in_from_toTEMPy){ \
			for_in_from_toTEMPx++; \
			{nat v=for_in_from_toTEMPx;{body}}} \
	}else{ \
		while(for_in_from_toTEMPx!=for_in_from_toTEMPy){ \
			for_in_from_toTEMPx--; \
			{nat v=for_in_from_toTEMPx;{body}}}}}

#define HEADER(n, x) IF(Not(Defined(n))) DEFINE(n,) {x} ENDIF

/* 有 #define TOOLS_prefix "" */
#define TOOLS \
	HEADER(X(TOOLS_prefix"dEFINEd"),WITH_MACRO_VA_ARGS( \
		IF(StdC11) \
			DEFINE_FUNCTION(X(TOOLS_prefix"error"),X("(x)"),X("_Static_assert(0,x)")) \
		ELIF(CPlusPlus11) \
			DEFINE_FUNCTION(X(TOOLS_prefix"error"),X("(x)"),X("static_assert(0,x)")) \
		ELSE \
			DEFINE_FUNCTION(X(TOOLS_prefix"error"),X("(x)"),X("{{{!!!ERROR x ERROR!!!}}}")) \
		ENDIF \
		DEFINE_FUNCTION(X(TOOLS_prefix"expand"),X("(x)"),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"countHELPER0"),X("(")var_from_to(0,eoc_max)X(",x,...)"),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"countHELPER1"),X("(...)"), \
			Call1(X(TOOLS_prefix"expand"),Call2(X(TOOLS_prefix"countHELPER0"),X("__VA_ARGS__"),from_to(eoc_max, 0)))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"count"),X("(...)"), \
			Call2(X(TOOLS_prefix"countHELPER1"),X("_Nothing"),X("##__VA_ARGS__"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"symbol_append"),X("(x,y)"),X("x##y")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"symbol_append_with_macro"),X("(x,y)"),Call2(X(TOOLS_prefix"symbol_append"),X("x"),X("y"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"with_count"),X("(ider,...)"), \
			Call1(X(TOOLS_prefix"expand"), \
				Call2(X(TOOLS_prefix"symbol_append_with_macro"), \
					X("ider"), \
					Call1(X(TOOLS_prefix"count"),X("__VA_ARGS__"))) \
				X("(__VA_ARGS__)"))) \
		\
		DEFINE(X(TOOLS_prefix"count_assert0"),) \
		DEFINE(X(TOOLS_prefix"count_assert1"),Call1(X(TOOLS_prefix"error"), \
			String("this compiler does not offers an extension that allows ## to appear after a comma and before __VA_ARGS__ , in which case the ## does nothing when __VA_ARGS__ is non-empty, but removes the comma when __VA_ARGS__ is empty"))) \
		LINE(Call1(X(TOOLS_prefix"expand"), \
			Call2(X(TOOLS_prefix"symbol_append"), \
				X(TOOLS_prefix"count_assert"), \
				Call0(X(TOOLS_prefix"count"))))) \
		\
		DEFINE_FUNCTION(X(TOOLS_prefix"init"),X("..."),Call2(X(TOOLS_prefix"with_count"),X(TOOLS_prefix"init"),X("__VA_ARGS__"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"init1"),X("(x)"),) \
		for_in_from_to(i, 2, eoc_max, { \
			nat isub=i-1; \
			DEFINE_FUNCTION(X(TOOLS_prefix"init")Nat(i),list_var_from_to(1,i),var_from_to(1,isub)) }) \
		\
		DEFINE_FUNCTION(X(TOOLS_prefix"reduce"),X("..."),Call2(X(TOOLS_prefix"with_count"),X(TOOLS_prefix"reduce"),X("__VA_ARGS__"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"reduce2"),X("(f,x)"),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"reduce3"),X("(f,x,y)"),X("f(x,y)")) \
		for_in_from_to(i, 4, eoc_max, { \
			nat length=i-1; \
			nat p1=length/2; \
			nat p2=length-p1; \
			nat p2base=i-p2+1; \
			DEFINE_FUNCTION(X(TOOLS_prefix"reduce")Nat(i),list_var_from_to(1,i),/*_1=f*/\
				Call2(X("_1"), \
					Call1(X(TOOLS_prefix"reduce")Nat(p1+1),var_from_to(1,p1+1)), \
					Call2(X(TOOLS_prefix"reduce")Nat(p2+1),X("_1"),var_from_to(p2base,i)))) }) \
	))

/* 有 #define LANG_prefix "" */
#define LANG \
	HEADER(X(LANG_prefix"dEFINEd"),WITH_MACRO_VA_ARGS( \
	))

int main(){
	FILE* f=fopen("module<", "w");
	#define file f
	#define TOOLS_prefix "eoC_TOOLS_"
	#define LANG_prefix "eoC_LANG_"
	TOOLS
	LANG
}
