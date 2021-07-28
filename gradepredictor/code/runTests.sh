#!/bin/bash

gcc project.c -Wall -ansi -pedantic -o project

for test in tests_p1/*.in; do
    ./project < ${test} > ${test%.in}.outhyp

    echo ${test%.in}
	diff -b ${test%.in}.out ${test%.in}.outhyp

    rm ${test%.in}.outhyp
done

rm project
