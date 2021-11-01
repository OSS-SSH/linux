#!/bin/sh
# SPDX-License-Identifier: GPL-2.0

set -e

# List of exported symbols
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#
# If the object has no symbol, $NM warns 'no symbols'.
# Suppress the stderr.
# TODO:
#   Use -q instead of 2>/dev/null when we upgrade the minimum version of
#   binutils to 2.37, llvm to 13.0.0.
ksyms=$($NM $1 2>/dev/null | sed -n 's/.*__ksym_marker_\(.*\)/\1/p')
<<<<<<< HEAD
=======
ksyms=$($NM $1 | sed -n 's/.*__ksym_marker_\(.*\)/\1/p' | tr A-Z a-z)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

if [ -z "$ksyms" ]; then
	exit 0
fi

echo
echo "ksymdeps_$1 := \\"

for s in $ksyms
do
<<<<<<< HEAD
<<<<<<< HEAD
	printf '    $(wildcard include/ksym/%s) \\\n' "$s"
=======
	echo $s | sed -e 's:^_*:    $(wildcard include/ksym/:' \
			-e 's:__*:/:g' -e 's/$/.h) \\/'
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	printf '    $(wildcard include/ksym/%s) \\\n' "$s"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
done

echo
echo "$1: \$(ksymdeps_$1)"
echo
echo "\$(ksymdeps_$1):"
