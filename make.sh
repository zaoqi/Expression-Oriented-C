#!/bin/bash
max=128
mkrequire(){
	if [ $1 = $max ] ; then
		echo '#error "Too many levels of require"'
	else
		echo "#ifdef _EOC_require_$1_"
		local k=$1
		let k++
		mkrequire $k
		echo "#else"
		echo "#define _EOC_require_$1_"
		echo "#endif"
	fi
}
mkmodule(){
	if [ $1 = $max ] ; then
		echo "#ifdef _EOC_require_$1_"
		echo '#error "BUG!"'
		echo "#else"
		echo "#unset $2"
		echo "#endif"
	else
		echo "#ifdef _EOC_require_$1_"
		local k=$1
		let k++
		mkmodule $k "_EOC_require_$1_"
		echo "#else"
		echo "#unset $2"
		echo "#endif"
	fi
}
echo "#pragma once" > -require-
echo "#ifdef _EOC_require_" >> -require-
mkrequire 0 >> -require-
echo "#else" >> -require-
echo "#define _EOC_require_" >> -require-
echo "#endif" >> -require-
echo '#include "prelude.h"' >> -require-

echo "#pragma once" > -module-
echo "#ifdef _EOC_require_" >> -module-
mkmodule 0 _EOC_require_ >> -module-
echo "#else" >> -module-
echo '#error "Too many -module-"' >> -module-
echo "#endif" >> -module-
echo '#include "prelude.h"' >> -module-
