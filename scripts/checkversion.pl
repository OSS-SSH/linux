#! /usr/bin/env perl
# SPDX-License-Identifier: GPL-2.0
#
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
# checkversion finds uses of all macros in <linux/version.h>
# where the source files do not #include <linux/version.h>; or cases
# of including <linux/version.h> where it is not needed.
# Copyright (C) 2003, Randy Dunlap <rdunlap@infradead.org>
<<<<<<< HEAD
=======
# checkversion find uses of LINUX_VERSION_CODE or KERNEL_VERSION
# without including <linux/version.h>, or cases of
# including <linux/version.h> that don't need it.
# Copyright (C) 2003, Randy Dunlap <rdunlap@xenotime.net>
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

use strict;

$| = 1;

my $debugging;

foreach my $file (@ARGV) {
<<<<<<< HEAD
<<<<<<< HEAD
    next if $file =~ "include/generated/uapi/linux/version\.h";
    next if $file =~ "usr/include/linux/version\.h";
=======
    next if $file =~ "include/linux/version\.h";
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
    next if $file =~ "include/generated/uapi/linux/version\.h";
    next if $file =~ "usr/include/linux/version\.h";
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
    # Open this file.
    open( my $f, '<', $file )
      or die "Can't open $file: $!\n";

    # Initialize variables.
    my ($fInComment, $fInString, $fUseVersion);
    my $iLinuxVersion = 0;

    while (<$f>) {
	# Strip comments.
	$fInComment && (s+^.*?\*/+ +o ? ($fInComment = 0) : next);
	m+/\*+o && (s+/\*.*?\*/+ +go, (s+/\*.*$+ +o && ($fInComment = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iLinuxVersion      = $. if m/^\s*#\s*include\s*"linux\/version\.h"/o;
	}

	# Strip strings.
	$fInString && (s+^.*?"+ +o ? ($fInString = 0) : next);
	m+"+o && (s+".*?"+ +go, (s+".*$+ +o && ($fInString = 1)));

	# Pick up definitions.
	if ( m/^\s*#/o ) {
	    $iLinuxVersion      = $. if m/^\s*#\s*include\s*<linux\/version\.h>/o;
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	# Look for uses: LINUX_VERSION_CODE, KERNEL_VERSION,
	# LINUX_VERSION_MAJOR, LINUX_VERSION_PATCHLEVEL, LINUX_VERSION_SUBLEVEL
	if (($_ =~ /LINUX_VERSION_CODE/) || ($_ =~ /\WKERNEL_VERSION/) ||
	    ($_ =~ /LINUX_VERSION_MAJOR/) || ($_ =~ /LINUX_VERSION_PATCHLEVEL/) ||
	    ($_ =~ /LINUX_VERSION_SUBLEVEL/)) {
<<<<<<< HEAD
=======
	# Look for uses: LINUX_VERSION_CODE, KERNEL_VERSION, UTS_RELEASE
	if (($_ =~ /LINUX_VERSION_CODE/) || ($_ =~ /\WKERNEL_VERSION/)) {
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	    $fUseVersion = 1;
            last if $iLinuxVersion;
        }
    }

    # Report used version IDs without include?
    if ($fUseVersion && ! $iLinuxVersion) {
	print "$file: $.: need linux/version.h\n";
    }

    # Report superfluous includes.
    if ($iLinuxVersion && ! $fUseVersion) {
	print "$file: $iLinuxVersion linux/version.h not needed.\n";
    }

    # debug: report OK results:
    if ($debugging) {
        if ($iLinuxVersion && $fUseVersion) {
	    print "$file: version use is OK ($iLinuxVersion)\n";
        }
        if (! $iLinuxVersion && ! $fUseVersion) {
	    print "$file: version use is OK (none)\n";
        }
    }

    close($f);
}
