#!/bin/bash
#    Copyright (C) 2018  Zaoqi

#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Affero General Public License as published
#    by the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Affero General Public License for more details.

#    You should have received a copy of the GNU Affero General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

# 参考https://blog.csdn.net/u011787119/article/details/53815950
if [ -z "$prefix" ]
then
	prefix=EOC_HELPER_
fi

max=64

define(){
	echo "#define $prefix$*"
}
defn(){
	echo -n "#define $prefix$1("
	shift
	local temp="$1"
	shift
	local first="true"
	while true
	do
		if [ -z "$1" ]
		then
			echo ") $temp"
			return
		else
			if [ -n "$first" ]
			then
				first=""
			else
				echo -n ","
			fi
			echo -n "$temp"
			temp="$1"
			shift
		fi
	done
}
call(){
	echo -n "$prefix$1("
	shift
	local first="true"
	while [ -n "$1" ]
	do
		if [ -n "$first" ]
		then
			first=""
		else
			echo -n ","
		fi
		echo -n "$1"
		shift
	done
	echo -n ")"
}
prefix_from_to_suffix(){
	eval echo $1{$2..$3}$4
}
defn expand x x
defn count_helper0 $(prefix_from_to_suffix _ 0 $max) x ... x
defn count_helper1 ... "$(call expand $(call count_helper0 __VA_ARGS__ $(prefix_from_to_suffix '' $max 0)))"
defn count ... "$(call count_helper1 _Nothing '##'__VA_ARGS__)"

