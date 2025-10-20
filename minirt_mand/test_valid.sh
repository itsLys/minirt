#!/usr/bin/env bash
set -euo pipefail #what is this

EXEC="$1"
DIR="$2"
SLEEP=${3:-20}

for file in "$DIR"/*; do
	echo "Running $EXEC on $file"

	# run bin
	"$EXEC" "$file" & 
	pid=$!

	echo "PID: $pid - sleeping $SLEEP seconds..."
	sleep "$SLEEP"
	
	if kill -0 "$pid" 2>/dev/null; then
		echo "Killing $pid"
		kill "$pid"
	fi
	echo "finished $file"
	echo "-------------------------------------"
done
