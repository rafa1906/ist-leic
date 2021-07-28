#!/bin/bash

cd project

export CLASSPATH=./m19-app/m19-app.jar:./m19-core/m19-core.jar:./po-uuilib/po-uuilib.jar:.

cd po-uuilib
make
cd ../m19-core
make
cd ../m19-app
make

cd ..
for test in tests/*.in; do
	if [ -f ${test%.in}.import ]; then
    		java -Dimport=${test%.in}.import -Din=${test%.in}.in -Dout=${test%.in}.outhyp m19.app.App
	else 
    		java -Din=${test%.in}.in -Dout=${test%.in}.outhyp m19.app.App
	fi
	
	echo ${test%.in}
	diff -b ${test%.in}.out ${test%.in}.outhyp
done

cd po-uuilib
make clean
cd ../m19-core
make clean
cd ../m19-app
make clean

