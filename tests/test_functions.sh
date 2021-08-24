#!/bin/sh

test_expression() {
    EXPECTED=$1
    shift
    EXPRESSION=$*
    
    echo "Testing '${EXPRESSION}' = ${EXPECTED}"

    RES=$( ./roll --test ${EXPRESSION} )

    if [ $? -ne 0 ] ; then
        echo "  Error: ${RES}"
        exit 1
    else
        if [ "${RES}" -ne "${EXPECTED}" ] ; then
            echo "  Wrong result: ${RES} != ${EXPECTED}"
            exit 1
        fi
    fi
    
    
}
