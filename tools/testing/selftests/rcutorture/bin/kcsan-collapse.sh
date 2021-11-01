#!/bin/bash
# SPDX-License-Identifier: GPL-2.0+
#
# If this was a KCSAN run, collapse the reports in the various console.log
# files onto pairs of functions.
#
# Usage: kcsan-collapse.sh resultsdir
#
# Copyright (C) 2020 Facebook, Inc.
#
# Authors: Paul E. McKenney <paulmck@kernel.org>

if test -z "$TORTURE_KCONFIG_KCSAN_ARG"
then
	exit 0
fi
<<<<<<< HEAD
find $1 -name console.log -exec cat {} \; |
=======
cat $1/*/console.log |
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
	grep "BUG: KCSAN: " |
	sed -e 's/^\[[^]]*] //' |
	sort |
	uniq -c |
	sort -k1nr > $1/kcsan.sum
