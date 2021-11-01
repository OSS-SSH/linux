#!/bin/bash
# SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause)
set -e

# Assume script is located under tools/testing/selftests/bpf/. We want to start
# build attempts from the top of kernel repository.
<<<<<<< HEAD
SCRIPT_REL_PATH=$(realpath $0)
SCRIPT_REL_DIR=$(dirname $SCRIPT_REL_PATH)
KDIR_ROOT_DIR=$(realpath $SCRIPT_REL_DIR/../../../../)
SCRIPT_REL_DIR=$(dirname $(realpath --relative-to=$KDIR_ROOT_DIR $SCRIPT_REL_PATH))
cd $KDIR_ROOT_DIR

if [ ! -e $PWD/$SCRIPT_REL_DIR/Makefile ]; then
	echo -e "skip:    bpftool files not found!\n"
	exit 4 # KSFT_SKIP=4
fi

=======
SCRIPT_REL_PATH=$(realpath --relative-to=$PWD $0)
SCRIPT_REL_DIR=$(dirname $SCRIPT_REL_PATH)
KDIR_ROOT_DIR=$(realpath $PWD/$SCRIPT_REL_DIR/../../../../)
cd $KDIR_ROOT_DIR

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
for tgt in docs docs-clean; do
	make -s -C $PWD/$SCRIPT_REL_DIR $tgt;
done
