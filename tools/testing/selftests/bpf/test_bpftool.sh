#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
# Copyright (c) 2020 SUSE LLC.

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# 'make -C tools/testing/selftests/bpf install' will install to SCRIPT_DIR
SCRIPT_DIR=$(dirname $(realpath $0))

# 'make -C tools/testing/selftests/bpf' will install to BPFTOOL_INSTALL_PATH
BPFTOOL_INSTALL_PATH="$SCRIPT_DIR"/tools/sbin
export PATH=$SCRIPT_DIR:$BPFTOOL_INSTALL_PATH:$PATH
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
python3 -m unittest -v test_bpftool.TestBpftool
