#!/bin/sh

while true; do
	OLDLIST="$LIST"
	LIST="`ls -l`"

	if [ "$LIST" != "$OLDLIST" ]; then
		make
	fi
	sleep 3
done
