#!/bin/sh

set -e

# exec_cmd_silent() {
# 	RESULT=$("$0[@] 2>&1")
# 	RET_CODE=$?
# 	if [ $RET_CODE != 0 ]; then
# 		echo "$0 command failed: $RET_CODE"
# 		exit 1
# 	fi

# 	echo -n $RESULT
# }

TARGET_PACKAGE=$1
if [ -z $TARGET_PACKAGE ]; then
	echo "Package is not provided!"
	exit 1
fi

INCLUDES_NOT_STRIPPED=$(pkg-config --cflags-only-I $TARGET_PACKAGE 2>&1)

INCLUDES=""
for dir in $INCLUDES_NOT_STRIPPED
do
	STRIPPED=$(echo $dir | sed s/"-I"//g 2>&1)
	INCLUDES="$INCLUDES $STRIPPED"
done

INCLUDES=$(echo $INCLUDES | awk '{$1=$1};1')

echo -n $INCLUDES
exit 0