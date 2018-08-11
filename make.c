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

/* 有 #define file "" */
#define echo(x) fputs(x, file)
#define echo_int(x) fprintf(file, "%d", x)
#define echo_nat(x) fprintf(file, "%u", x)
#define echo_nat_hex(x) fprintf(file, "%x", x)

#define IF IF_
#define ELSE ELSE_
#define ELIF ELIF_
#define ENDIF ENDIF_
#define DEFINE DEFINE_
#define DEFINE_FUNCTION DEFINE_FUNCTION_
#define ERROR ERROR_
#define IF_(x) echo("#if ");{x}echo("\n");
#define ELSE_ echo("#else\n");
#define ELIF_(x) echo("#elif ");{x}echo("\n");
#define ENDIF_ echo("#endif\n");
#define DEFINE_(x, v) echo("#define ");{x}echo(" ");{v}echo("\n");
#define DEFINE_FUNCTION_(name, args, v) echo("#define ");{name}{args}echo(" ");{v}echo("\n");
#define ERROR_(x) echo("#error ");{x}echo("\n");

#define X X_
#define Defined Defined_
#define Not Not_
#define Or Or_
#define And And_
#define Gt Gt_
#define GtEq GtEq_
#define Eq Eq_
#define Lt Lt_
#define LtEq LtEq_
#define X_(x) echo(x);
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

#define prefix_addbetween_from_to(prefix, addbetween, x, y) { \
	nat a=(x); \
	nat b=(y); \
	echo(prefix); \
	echo_nat_hex(a); \
	if(eq_p(a, b)){ \
	}else if(a<b){ \
		while(a!=b){ \
			a++;/*a<=b*/\
			echo(addbetween); \
			echo(prefix); \
			echo_nat_hex(a);} \
	}else{/*a>b*/ \
		while(a!=b){ \
			a--;/*a>=b*/ \
			echo(addbetween); \
			echo(prefix); \
			echo_nat_hex(a);}}}
#define from_to(x, y) prefix_addbetween_from_to("_", ",", x, y)

#define HEADER(n, x) IF(Not(Defined(n))) DEFINE(n,) {x} ENDIF

/* 有 #define TOOLS_prefix "" */
#define TOOLS \
	HEADER(X(TOOLS_prefix "defined"), \
		IF(StdC11) \
			DEFINE_FUNCTION(X(TOOLS_prefix "error"),X("(x)"),X("_Static_assert(0,x)")) \
		ELIF(CPlusPlus11) \
			DEFINE_FUNCTION(X(TOOLS_prefix "error"),X("(x)"),X("static_assert(0,x)")) \
		ELSE \
			DEFINE_FUNCTION(X(TOOLS_prefix "error"),X("(x)"),X("{{{!!!ERROR x ERROR!!!}}}")) \
		ENDIF \
		DEFINE_FUNCTION(X(TOOLS_prefix "expand"),X("(x)"),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix "countHELPER0"),X("(")from_to(0, eoc_max)X(",x)"),X("x")) \
	)

int main(){
	FILE* f=fopen("tools.h", "w");
	#define file f
	#define TOOLS_prefix "eoC_TOOLS_"
	TOOLS
}
