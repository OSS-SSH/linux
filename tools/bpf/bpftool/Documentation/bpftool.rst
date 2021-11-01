================
BPFTOOL
================
-------------------------------------------------------------------------------
tool for inspection and simple manipulation of eBPF programs and maps
-------------------------------------------------------------------------------

:Manual section: 8

SYNOPSIS
========

	**bpftool** [*OPTIONS*] *OBJECT* { *COMMAND* | **help** }

	**bpftool** **batch file** *FILE*

	**bpftool** **version**

	*OBJECT* := { **map** | **program** | **cgroup** | **perf** | **net** | **feature** }

<<<<<<< HEAD
<<<<<<< HEAD
	*OPTIONS* := { { **-V** | **--version** } |
		{ **-j** | **--json** } [{ **-p** | **--pretty** }] | { **-d** | **--debug** } }

	*MAP-COMMANDS* :=
	{ **show** | **list** | **create** | **dump** | **update** | **lookup** | **getnext** |
		**delete** | **pin** | **event_pipe** | **help** }

	*PROG-COMMANDS* := { **show** | **list** | **dump jited** | **dump xlated** | **pin** |
		**load** | **attach** | **detach** | **help** }
=======
	*OPTIONS* := { { **-V** | **--version** } | { **-h** | **--help** }
	| { **-j** | **--json** } [{ **-p** | **--pretty** }] }
=======
	*OPTIONS* := { { **-V** | **--version** } |
		{ **-j** | **--json** } [{ **-p** | **--pretty** }] | { **-d** | **--debug** } }
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	*MAP-COMMANDS* :=
	{ **show** | **list** | **create** | **dump** | **update** | **lookup** | **getnext** |
		**delete** | **pin** | **event_pipe** | **help** }

<<<<<<< HEAD
	*PROG-COMMANDS* := { **show** | **list** | **dump jited** | **dump xlated** | **pin**
	| **load** | **attach** | **detach** | **help** }
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	*PROG-COMMANDS* := { **show** | **list** | **dump jited** | **dump xlated** | **pin** |
		**load** | **attach** | **detach** | **help** }
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	*CGROUP-COMMANDS* := { **show** | **list** | **attach** | **detach** | **help** }

	*PERF-COMMANDS* := { **show** | **list** | **help** }

	*NET-COMMANDS* := { **show** | **list** | **help** }

	*FEATURE-COMMANDS* := { **probe** | **help** }

DESCRIPTION
===========
	*bpftool* allows for inspection and simple modification of BPF objects
	on the system.

	Note that format of the output of all tools is not guaranteed to be
	stable and should not be depended upon.

OPTIONS
=======
	.. include:: common_options.rst

	-m, --mapcompat
		  Allow loading maps with unknown map definitions.

	-n, --nomount
		  Do not automatically attempt to mount any virtual file system
		  (such as tracefs or BPF virtual file system) when necessary.
