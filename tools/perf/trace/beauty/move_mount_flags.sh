#!/bin/sh
# SPDX-License-Identifier: LGPL-2.1

if [ $# -ne 1 ] ; then
	linux_header_dir=tools/include/uapi/linux
else
	linux_header_dir=$1
fi

linux_mount=${linux_header_dir}/mount.h

printf "static const char *move_mount_flags[] = {\n"
<<<<<<< HEAD
<<<<<<< HEAD
regex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MOVE_MOUNT_([^_]+_[[:alnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
=======
regex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MOVE_MOUNT_([FT]_[[:alnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
regex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MOVE_MOUNT_([^_]+_[[:alnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
egrep $regex ${linux_mount} | \
	sed -r "s/$regex/\2 \1/g"	| \
	xargs printf "\t[ilog2(%s) + 1] = \"%s\",\n"
printf "};\n"
