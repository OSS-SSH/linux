#!/bin/bash
# SPDX-License-Identifier: (GPL-2.0-only OR BSD-2-Clause)
<<<<<<< HEAD
=======
set -e
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a

# Assume script is located under tools/testing/selftests/bpf/. We want to start
# build attempts from the top of kernel repository.
SCRIPT_REL_PATH=$(realpath --relative-to=$PWD $0)
SCRIPT_REL_DIR=$(dirname $SCRIPT_REL_PATH)
KDIR_ROOT_DIR=$(realpath $PWD/$SCRIPT_REL_DIR/../../../../)
cd $KDIR_ROOT_DIR

for tgt in docs docs-clean; do
	make -s -C $PWD/$SCRIPT_REL_DIR $tgt;
done
