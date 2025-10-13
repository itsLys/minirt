#!/usr/bin/env bash
set -euo pipefail #what is this

EXEC="$1"
DIR="$2"
SLEEP=${3:-5}
LOG_FILE="log.txt"

echo "-------------------------------------" > $LOG_FILE
for file in "$DIR"/*; do

	echo "-------------------------------------" >> $LOG_FILE
	echo "Testing file: $file" >> $LOG_FILE
	# run bin
	if "valgrind" "--show-leak-kinds=all" "--leak-check=full" "$EXEC" "$file" 2>> $LOG_FILE; then
		echo "ERROR: $EXEC on $file succeeded (expected failiure)"
		exit 1
	else
		echo "PASSED: failed as expected" >> $LOG_FILE
	fi
	echo "-------------------------------------" >> $LOG_FILE
done
