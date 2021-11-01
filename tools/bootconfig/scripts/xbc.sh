#!/bin/sh
# SPDX-License-Identifier: GPL-2.0-only

# bootconfig utility functions

XBC_TMPFILE=
XBC_BASEDIR=`dirname $0`
BOOTCONFIG=${BOOTCONFIG:=$XBC_BASEDIR/../bootconfig}
if [ ! -x "$BOOTCONFIG" ]; then
	BOOTCONFIG=`which bootconfig`
	if [ -z "$BOOTCONFIG" ]; then
		echo "Erorr: bootconfig command is not found" 1>&2
		exit 1
	fi
fi

xbc_cleanup() {
	if [ "$XBC_TMPFILE" ]; then
		rm -f "$XBC_TMPFILE"
	fi
}

xbc_init() { # bootconfig-file
	xbc_cleanup
	XBC_TMPFILE=`mktemp bconf-XXXX`
	trap xbc_cleanup EXIT TERM

	$BOOTCONFIG -l $1 > $XBC_TMPFILE || exit 1
}

nr_args() { # args
	echo $#
}

xbc_get_val() { # key [maxnum]
	if [ "$2" ]; then
		MAXOPT="-L $2"
	fi
	grep "^$1 =" $XBC_TMPFILE | cut -d= -f2- | \
		sed -e 's/", /" /g' -e "s/',/' /g" | \
		xargs $MAXOPT -n 1 echo
}

xbc_has_key() { # key
	grep -q "^$1 =" $XBC_TMPFILE
}

xbc_has_branch() { # prefix-key
	grep -q "^$1" $XBC_TMPFILE
}

<<<<<<< HEAD
<<<<<<< HEAD
xbc_subkeys() { # prefix-key depth [subkey-pattern]
	__keys=`echo $1 | sed "s/\./ /g"`
	__s=`nr_args $__keys`
	grep "^$1$3" $XBC_TMPFILE | cut -d= -f1| cut -d. -f$((__s + 1))-$((__s + $2)) | uniq
=======
xbc_subkeys() { # prefix-key depth
	__keys=`echo $1 | sed "s/\./ /g"`
	__s=`nr_args $__keys`
	grep "^$1" $XBC_TMPFILE | cut -d= -f1| cut -d. -f$((__s + 1))-$((__s + $2)) | uniq
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
xbc_subkeys() { # prefix-key depth [subkey-pattern]
	__keys=`echo $1 | sed "s/\./ /g"`
	__s=`nr_args $__keys`
	grep "^$1$3" $XBC_TMPFILE | cut -d= -f1| cut -d. -f$((__s + 1))-$((__s + $2)) | uniq
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}
