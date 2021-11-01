#!/bin/bash
# SPDX-License-Identifier: GPL-2.0
# Copyright(c) 2020 Intel Corporation.

ksft_pass=0
ksft_fail=1
ksft_xfail=2
ksft_xpass=3
ksft_skip=4

<<<<<<< HEAD
<<<<<<< HEAD
SPECFILE=veth.spec
XSKOBJ=xdpxceiver
=======
GREEN='\033[0;92m'
YELLOW='\033[0;93m'
RED='\033[0;31m'
NC='\033[0m'
STACK_LIM=131072
SPECFILE=veth.spec
XSKOBJ=xdpxceiver
NUMPKTS=10000
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
SPECFILE=veth.spec
XSKOBJ=xdpxceiver
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

validate_root_exec()
{
	msg="skip all tests:"
	if [ $UID != 0 ]; then
		echo $msg must be run as root >&2
		test_exit $ksft_fail 2
	else
		return $ksft_pass
	fi
}

validate_veth_support()
{
	msg="skip all tests:"
	if [ $(ip link add $1 type veth 2>/dev/null; echo $?;) != 0 ]; then
		echo $msg veth kernel support not available >&2
		test_exit $ksft_skip 1
	else
		ip link del $1
		return $ksft_pass
	fi
}

validate_veth_spec_file()
{
	if [ ! -f ${SPECFILE} ]; then
		test_exit $ksft_skip 1
	fi
}

test_status()
{
	statusval=$1
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if [ $statusval -eq 2 ]; then
		echo -e "$2: [ FAIL ]"
	elif [ $statusval -eq 1 ]; then
		echo -e "$2: [ SKIPPED ]"
	elif [ $statusval -eq 0 ]; then
		echo -e "$2: [ PASS ]"
<<<<<<< HEAD
=======
	if [ -n "${colorconsole+set}" ]; then
		if [ $statusval -eq 2 ]; then
			echo -e "${YELLOW}$2${NC}: [ ${RED}FAIL${NC} ]"
		elif [ $statusval -eq 1 ]; then
			echo -e "${YELLOW}$2${NC}: [ ${RED}SKIPPED${NC} ]"
		elif [ $statusval -eq 0 ]; then
			echo -e "${YELLOW}$2${NC}: [ ${GREEN}PASS${NC} ]"
		fi
	else
		if [ $statusval -eq 2 ]; then
			echo -e "$2: [ FAIL ]"
		elif [ $statusval -eq 1 ]; then
			echo -e "$2: [ SKIPPED ]"
		elif [ $statusval -eq 0 ]; then
			echo -e "$2: [ PASS ]"
		fi
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	fi
}

test_exit()
{
	retval=$1
	if [ $2 -ne 0 ]; then
		test_status $2 $(basename $0)
	fi
	exit $retval
}

clear_configs()
{
	if [ $(ip netns show | grep $3 &>/dev/null; echo $?;) == 0 ]; then
		[ $(ip netns exec $3 ip link show $2 &>/dev/null; echo $?;) == 0 ] &&
			{ ip netns exec $3 ip link del $2; }
		ip netns del $3
	fi
	#Once we delete a veth pair node, the entire veth pair is removed,
	#this is just to be cautious just incase the NS does not exist then
	#veth node inside NS won't get removed so we explicitly remove it
	[ $(ip link show $1 &>/dev/null; echo $?;) == 0 ] &&
		{ ip link del $1; }
	if [ -f ${SPECFILE} ]; then
		rm -f ${SPECFILE}
	fi
}

cleanup_exit()
{
	clear_configs $1 $2 $3
}

validate_ip_utility()
{
	[ ! $(type -P ip) ] && { echo "'ip' not found. Skipping tests."; test_exit $ksft_skip 1; }
}

execxdpxceiver()
{
<<<<<<< HEAD
<<<<<<< HEAD
	./${XSKOBJ} -i ${VETH0} -i ${VETH1},${NS1} ${VERBOSE_ARG} ${DUMP_PKTS_ARG}
=======
	./${XSKOBJ} -i ${VETH0} -i ${VETH1},${NS1} -C ${NUMPKTS} ${VERBOSE_ARG} ${DUMP_PKTS_ARG}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	./${XSKOBJ} -i ${VETH0} -i ${VETH1},${NS1} ${VERBOSE_ARG} ${DUMP_PKTS_ARG}
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}
