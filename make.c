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
#define UNDEFINE UNDEFINE_
#define DEFINE DEFINE_
#define DEFINE_FUNCTION DEFINE_FUNCTION_
#define ERROR ERROR_
#define LINE LINE_
#define INCLUDE INCLUDE_
#define IF_(x) echo("#if ");{x}echo("\n");
#define ELSE_ echo("#else\n");
#define ELIF_(x) echo("#elif ");{x}echo("\n");
#define ENDIF_ echo("#endif\n");
#define UNDEFINE_(x) echo("#undef ");{x}echo("\n");
#define DEFINE_(x, v) echo("#define ");{x}echo(" ");{v}echo("\n");
#define DEFINE_FUNCTION_(name, args, v) echo("#define ");{name}echo("(");{args}echo(") ");{v}echo("\n");
#define ERROR_(x) echo("#error ");{x}echo("\n");
#define LINE_(x) {x}echo("\n");
#define INCLUDE_(x) echo("#include ");{x}echo("\n");

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

#define CPlusPlus Defined(X("__cplusplus"))
#define StdC Defined(X("__STDC_VERSION__"))
#define StdC99 And(StdC,GtEq(X("__STDC_VERSION__"),X("199901L")))
#define StdC11 And(StdC,GtEq(X("__STDC_VERSION__"),X("201112L")))
#define CPlusPlus11 And(CPlusPlus,GtEq(X("__cplusplus"),X("201103L")))

#define WITH_MACRO_VA_ARGS(x) IF(Or(StdC99, CPlusPlus11)){x}ELSE ERROR(X("__VA_ARGS__ requires C99 or later or C++11 or later")) ENDIF

#define REDEFINE(x) UNDEFINE(x) DEFINE(x)

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

/* 有 #define TOOLS_prefix "..." */
#define TOOLS \
	HEADER(X(TOOLS_prefix"dEFINEd"),WITH_MACRO_VA_ARGS( \
		IF(StdC11) \
			DEFINE_FUNCTION(X(TOOLS_prefix"error"),X("x"),X("_Static_assert(0,x)")) \
		ELIF(CPlusPlus11) \
			DEFINE_FUNCTION(X(TOOLS_prefix"error"),X("x"),X("static_assert(0,x)")) \
		ELSE \
			DEFINE_FUNCTION(X(TOOLS_prefix"error"),X("x"),X("{{{!!!ERROR x ERROR!!!}}}")) \
		ENDIF \
		DEFINE_FUNCTION(X(TOOLS_prefix"expand"),X("x"),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"countHELPER0"),var_from_to(0,eoc_max)X(",x,..."),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"countHELPER1"),X("..."), \
			Call1(X(TOOLS_prefix"expand"),Call2(X(TOOLS_prefix"countHELPER0"),X("__VA_ARGS__"),from_to(eoc_max, 0)))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"count"),X("..."), \
			Call2(X(TOOLS_prefix"countHELPER1"),X("_Nothing"),X("##__VA_ARGS__"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"symbol_append"),X("x,y"),X("x##y")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"symbol_append_with_macro"),X("x,y"),Call2(X(TOOLS_prefix"symbol_append"),X("x"),X("y"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"with_count"),X("ider,..."), \
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
		DEFINE_FUNCTION(X(TOOLS_prefix"init1"),X("x"),) \
		for_in_from_to(i, 2, eoc_max, { \
			nat isub=i-1; \
			DEFINE_FUNCTION(X(TOOLS_prefix"init")Nat(i),var_from_to(1,i),var_from_to(1,isub)) }) \
		\
		DEFINE_FUNCTION(X(TOOLS_prefix"reduce"),X("..."),Call2(X(TOOLS_prefix"with_count"),X(TOOLS_prefix"reduce"),X("__VA_ARGS__"))) \
		DEFINE_FUNCTION(X(TOOLS_prefix"reduce2"),X("f,x"),X("x")) \
		DEFINE_FUNCTION(X(TOOLS_prefix"reduce3"),X("f,x,y"),X("f(x,y)")) \
		for_in_from_to(i, 4, eoc_max, { \
			nat length=i-1; \
			nat p1=length/2; \
			nat p2=length-p1; \
			nat p2base=i-p2+1; \
			DEFINE_FUNCTION(X(TOOLS_prefix"reduce")Nat(i),var_from_to(1,i),/*_1=f*/\
				Call2(X("_1"), \
					Call1(X(TOOLS_prefix"reduce")Nat(p1+1),var_from_to(1,p1+1)), \
					Call2(X(TOOLS_prefix"reduce")Nat(p2+1),X("_1"),var_from_to(p2base,i)))) }) \
	))

/* 有 #define LANG_prefix "..." */
/* 有 #define LANG_EXPORT("...") ... */
#define LANG \
	HEADER(X(LANG_prefix"dEFINEd"),WITH_MACRO_VA_ARGS( \
		HEADER(X(LANG_prefix"_static_dEFINEd"), \
			IF(CPlusPlus) \
				DEFINE(X(LANG_prefix"HELPERstaticDefine_inlineDefine"),X("static inline")) \
				DEFINE(X(LANG_prefix"HELPERexternDefine_inlineDefine"),X("inline")) \
				DEFINE(X(LANG_prefix"HELPERexternDeclare_inlineDefine"),X("inline")) \
			ELIF(StdC99) \
				DEFINE(X(LANG_prefix"HELPERstaticDefine_inlineDefine"),X("static inline")) \
				DEFINE(X(LANG_prefix"HELPERexternDefine_inlineDefine"),X("extern inline")) \
				DEFINE(X(LANG_prefix"HELPERexternDeclare_inlineDefine"),X("inline")) \
			ELSE \
				ERROR(X("inline requires C99 or later or C++")) \
			ENDIF \
			LANG_EXPORT("make_void") LINE(X(LANG_prefix"HELPERstaticDefine_inlineDefine void "LANG_prefix"make_void(void){}")) \
			\
			LANG_EXPORT("define_type") \
			DEFINE(X(LANG_prefix"define_type"),X("typedef")) \
			\
			LANG_EXPORT("int8") LANG_EXPORT("int16") LANG_EXPORT("int32") LANG_EXPORT("int64") LANG_EXPORT("int_pointer") \
			LANG_EXPORT("nat8") LANG_EXPORT("nat16") LANG_EXPORT("nat32") LANG_EXPORT("nat64") LANG_EXPORT("nat_pointer") \
			LANG_EXPORT("byte") LANG_EXPORT("signed_byte") \
			IF(CPlusPlus11) \
				LANG_EXPORT("restrict") \
				DEFINE(X(LANG_prefix"restrict"),) \
				INCLUDE(X("<cstddef>")) \
				LINE(X("using std::size_t;")) \
				INCLUDE(X("<cstdint>")) \
				LINE(X("typedef std::int_least8_t "LANG_prefix"int8;")) \
				LINE(X("typedef std::int_least8_t "LANG_prefix"signed_byte;")) \
				LINE(X("typedef std::int_least16_t "LANG_prefix"int16;")) \
				LINE(X("typedef std::int_least32_t "LANG_prefix"int32;")) \
				LINE(X("typedef std::int_least64_t "LANG_prefix"int64;")) \
				LINE(X("typedef std::uint_least8_t "LANG_prefix"nat8;")) \
				LINE(X("typedef std::uint_least8_t "LANG_prefix"byte;")) \
				LINE(X("typedef std::uint_least16_t "LANG_prefix"nat16;")) \
				LINE(X("typedef std::uint_least32_t "LANG_prefix"nat32;")) \
				LINE(X("typedef std::uint_least64_t "LANG_prefix"nat64;")) \
				LINE(X("typedef std::uintptr_t "LANG_prefix"nat_pointer;")) \
				LINE(X("typedef std::intptr_t "LANG_prefix"int_pointer;")) \
			ELIF(StdC99) \
				INCLUDE(X("<stddef.h>")) \
				INCLUDE(X("<stdint.h>")) \
				LINE(X("typedef int_least8_t "LANG_prefix"int8;")) \
				LINE(X("typedef int_least8_t "LANG_prefix"signed_byte;")) \
				LINE(X("typedef int_least16_t "LANG_prefix"int16;")) \
				LINE(X("typedef int_least32_t "LANG_prefix"int32;")) \
				LINE(X("typedef int_least64_t "LANG_prefix"int64;")) \
				LINE(X("typedef uint_least8_t "LANG_prefix"nat8;")) \
				LINE(X("typedef uint_least8_t "LANG_prefix"byte;")) \
				LINE(X("typedef uint_least16_t "LANG_prefix"nat16;")) \
				LINE(X("typedef uint_least32_t "LANG_prefix"nat32;")) \
				LINE(X("typedef uint_least64_t "LANG_prefix"nat64;")) \
				LINE(X("typedef uintptr_t "LANG_prefix"nat_pointer;")) \
				LINE(X("typedef intptr_t "LANG_prefix"int_pointer;")) \
			ELSE \
				ERROR(X("<stdint.h> or <cstdint> requires C99 or later or C++11 or later")) \
			ENDIF \
			\
			LANG_EXPORT("cast") DEFINE_FUNCTION(X(LANG_prefix"cast"),X("x,t"),X("((t)x)")) \
			LANG_EXPORT("annotate") DEFINE_FUNCTION(X(LANG_prefix"annotate"),X("x,t"),X("({t "LANG_prefix"tEMp=x;"LANG_prefix"tEMp;})")) \
			LANG_EXPORT("bool_not") DEFINE_FUNCTION(X(LANG_prefix"bool_not"),X("x"),X("(!(x))")) \
			LANG_EXPORT("eq_p") DEFINE_FUNCTION(X(LANG_prefix"eq_p"),X("..."), \
				Call2(X(TOOLS_prefix"reduce"),X(LANG_prefix"eq_p2"),X("__VA_ARGS__"))) \
			DEFINE_FUNCTION(X(LANG_prefix"eq_p2"),X("x,y"),X("((x)==(y))")) \
			LANG_EXPORT("not_eq_p") DEFINE_FUNCTION(X(LANG_prefix"not_eq_p"),X("x,y"),X("((x)!=(y))")) \
			LANG_EXPORT("bool_and") DEFINE_FUNCTION(X(LANG_prefix"bool_and"),X("..."), \
				Call2(X(TOOLS_prefix"reduce"),X(LANG_prefix"bool_and2"),X("__VA_ARGS__"))) \
			DEFINE_FUNCTION(X(LANG_prefix"bool_and2"),X("x,y"),X("((x)&&(y))")) \
			LANG_EXPORT("bool_or") DEFINE_FUNCTION(X(LANG_prefix"bool_or"),X("..."), \
				Call2(X(TOOLS_prefix"reduce"),X(LANG_prefix"bool_or2"),X("__VA_ARGS__"))) \
			DEFINE_FUNCTION(X(LANG_prefix"bool_or2"),X("x,y"),X("((x)||(y))")) \
			\
			LANG_EXPORT("anonymous_struct") LANG_EXPORT("declare_struct") LANG_EXPORT("define_struct") \
			LANG_EXPORT("anonymous_union") LANG_EXPORT("declare_union") LANG_EXPORT("define_union") \
			LANG_EXPORT("anonymous_enumeration") LANG_EXPORT("declare_enumeration") LANG_EXPORT("define_enumeration") \
			DEFINE(X(LANG_prefix"anonymous_struct"),X("struct")) \
			DEFINE(X(LANG_prefix"anonymous_union"),X("union")) \
			DEFINE(X(LANG_prefix"anonymous_enumeration"),X("enum")) \
			IF(CPlusPlus) \
				DEFINE_FUNCTION(X(LANG_prefix"declare_struct"),X("x"),X("struct x")) \
				DEFINE_FUNCTION(X(LANG_prefix"define_struct"),X("x"),X("struct x")) \
				DEFINE_FUNCTION(X(LANG_prefix"declare_union"),X("x"),X("union x")) \
				DEFINE_FUNCTION(X(LANG_prefix"define_union"),X("x"),X("union x")) \
				DEFINE_FUNCTION(X(LANG_prefix"declare_enumeration"),X("x"),X("enum x")) \
				DEFINE_FUNCTION(X(LANG_prefix"define_enumeration"),X("x"),X("enum x")) \
			ELSE \
				DEFINE_FUNCTION(X(LANG_prefix"declare_struct"),X("x"),X("struct x;typedef struct x x")) \
				DEFINE_FUNCTION(X(LANG_prefix"define_struct"),X("x"),Call1(X(LANG_prefix"declare_struct"),X("x"))X(";struct x")) \
				DEFINE_FUNCTION(X(LANG_prefix"declare_union"),X("x"),X("union x;typedef union x x")) \
				DEFINE_FUNCTION(X(LANG_prefix"define_union"),X("x"),Call1(X(LANG_prefix"declare_union"),X("x"))X(";union x")) \
				DEFINE_FUNCTION(X(LANG_prefix"declare_enumeration"),X("x"),X("enum x;typedef enum x x")) \
				DEFINE_FUNCTION(X(LANG_prefix"define_enumeration"),X("x"),Call1(X(LANG_prefix"declare_enumeration"),X("x"))X(";enum x")) \
			ENDIF \
			\
			IF(And(Defined(X("__bool_true_false_are_defined")),X("__bool_true_false_are_defined"))) \
			ELIF(CPlusPlus) \
			ELIF(StdC99) \
				INCLUDE(X("<stdbool.h>")) \
			ELSE \
				DEFINE(X(LANG_prefix"__bool_true_false_are_defined"),Nat(1)) \
				DEFINE(X(LANG_prefix"bool"),X("unsigned char")) \
				DEFINE(X(LANG_prefix"true"),Nat(1)) \
				DEFINE(X(LANG_prefix"false"),Nat(0)) \
			ENDIF \
			LANG_EXPORT_IFDEF("__bool_true_false_are_defined",LANG_prefix"__bool_true_false_are_defined") \
			LANG_EXPORT_IFDEF("bool",LANG_prefix"__bool_true_false_are_defined") \
			LANG_EXPORT_IFDEF("true",LANG_prefix"__bool_true_false_are_defined") \
			LANG_EXPORT_IFDEF("false",LANG_prefix"__bool_true_false_are_defined") \
			\
			"WIP"; \
		) \
	))

int main(){
	FILE* f=fopen("module<", "w");
	FILE* undef=fopen("undef.h", "w");
	FILE* redef=fopen("redef.h", "w");
	#define file f
	#define TOOLS_prefix "eoC_TOOLS_"
	TOOLS
	#define LANG_prefix "eoC_LANG_"
	#define LANG_EXPORT(x) { \
		fputs("#undef "x"\n",undef); \
		fputs("#define "x" "LANG_prefix x"\n",redef); \
		DEFINE(X(x),X(LANG_prefix x))}
	#define LANG_EXPORT_IFDEF(x, m) { \
		fputs("#ifdef "m"\n#undef "x"\n#endif\n",undef); \
		fputs("#ifdef "m"\n#define "x" "LANG_prefix x"\n#endif\n",redef); \
		IF(Defined(X(m))) DEFINE(X(x),X(LANG_prefix x)) ENDIF}
	LANG
	fclose(f);
	fclose(undef);
	fclose(redef);
}
