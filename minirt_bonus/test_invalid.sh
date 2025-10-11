#!/usr/bin/env bash
set -euo pipefail #what is this

EXEC="$1"
DIR="$2"
SLEEP=${3:-5}

for file in "$DIR"/*; do
	echo "Testing invlid file: $file"

	# run bin
	if "$EXEC" "$file"; then
		echo "ERROR: $EXEC on $file succeeded (expected failiure)"
		exit 1
	else
		echo "PASSED: failed as expected"
	fi
	echo "-------------------------------------"
done
