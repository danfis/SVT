#!/bin/bash

# Creates .tar.gz package of specified version.
# Takes one argument - identification of commit

COMMIT="$1"
PRJ_NAME=svt
PREFIX=$PRJ_NAME-$COMMIT
FN=$PRJ_NAME-$COMMIT.tar.gz
CMD="git archive"

if [ "$COMMIT" = "" ]; then
    echo "Error: you must specify commit which should be packed"
    exit -1;
fi;

if echo "$COMMIT" | grep '^v[0-9]\.[0-9]\+' >/dev/null 2>&1; then
    tmp=$(echo "$COMMIT" | sed 's/^v//')
    PREFIX=$PRJ_NAME-$tmp/
    FN=$PRJ_NAME-$tmp.tar.gz
fi


$CMD --prefix="$PREFIX" --format=tar $COMMIT | gzip >"$FN"
echo "Package: $FN"

