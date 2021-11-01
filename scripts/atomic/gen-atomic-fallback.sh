#!/bin/sh
# SPDX-License-Identifier: GPL-2.0

ATOMICDIR=$(dirname $0)
<<<<<<< HEAD
<<<<<<< HEAD

. ${ATOMICDIR}/atomic-tbl.sh

#gen_template_fallback(template, meta, pfx, name, sfx, order, atomic, int, args...)
=======
ARCH=$2

. ${ATOMICDIR}/atomic-tbl.sh

#gen_template_fallback(template, meta, pfx, name, sfx, order, arch, atomic, int, args...)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

. ${ATOMICDIR}/atomic-tbl.sh

#gen_template_fallback(template, meta, pfx, name, sfx, order, atomic, int, args...)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
gen_template_fallback()
{
	local template="$1"; shift
	local meta="$1"; shift
	local pfx="$1"; shift
	local name="$1"; shift
	local sfx="$1"; shift
	local order="$1"; shift
<<<<<<< HEAD
<<<<<<< HEAD
	local atomic="$1"; shift
	local int="$1"; shift

	local atomicname="arch_${atomic}_${pfx}${name}${sfx}${order}"
=======
	local arch="$1"; shift
	local atomic="$1"; shift
	local int="$1"; shift

	local atomicname="${arch}${atomic}_${pfx}${name}${sfx}${order}"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	local atomic="$1"; shift
	local int="$1"; shift

	local atomicname="arch_${atomic}_${pfx}${name}${sfx}${order}"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	local ret="$(gen_ret_type "${meta}" "${int}")"
	local retstmt="$(gen_ret_stmt "${meta}")"
	local params="$(gen_params "${int}" "${atomic}" "$@")"
	local args="$(gen_args "$@")"

	if [ ! -z "${template}" ]; then
		printf "#ifndef ${atomicname}\n"
		. ${template}
		printf "#define ${atomicname} ${atomicname}\n"
		printf "#endif\n\n"
	fi
}

<<<<<<< HEAD
<<<<<<< HEAD
#gen_proto_fallback(meta, pfx, name, sfx, order, atomic, int, args...)
=======
#gen_proto_fallback(meta, pfx, name, sfx, order, arch, atomic, int, args...)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#gen_proto_fallback(meta, pfx, name, sfx, order, atomic, int, args...)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
gen_proto_fallback()
{
	local meta="$1"; shift
	local pfx="$1"; shift
	local name="$1"; shift
	local sfx="$1"; shift
	local order="$1"; shift

	local tmpl="$(find_fallback_template "${pfx}" "${name}" "${sfx}" "${order}")"
	gen_template_fallback "${tmpl}" "${meta}" "${pfx}" "${name}" "${sfx}" "${order}" "$@"
}

#gen_basic_fallbacks(basename)
gen_basic_fallbacks()
{
	local basename="$1"; shift
cat << EOF
#define ${basename}_acquire ${basename}
#define ${basename}_release ${basename}
#define ${basename}_relaxed ${basename}
EOF
}

gen_proto_order_variant()
{
	local meta="$1"; shift
	local pfx="$1"; shift
	local name="$1"; shift
	local sfx="$1"; shift
	local order="$1"; shift
<<<<<<< HEAD
<<<<<<< HEAD
	local atomic="$1"

	local basename="arch_${atomic}_${pfx}${name}${sfx}"

	printf "#define ${basename}${order} ${basename}${order}\n"
}

#gen_proto_order_variants(meta, pfx, name, sfx, atomic, int, args...)
=======
	local arch="$1"
	local atomic="$2"
=======
	local atomic="$1"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	local basename="arch_${atomic}_${pfx}${name}${sfx}"

	printf "#define ${basename}${order} ${basename}${order}\n"
}

<<<<<<< HEAD
#gen_proto_order_variants(meta, pfx, name, sfx, arch, atomic, int, args...)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#gen_proto_order_variants(meta, pfx, name, sfx, atomic, int, args...)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
gen_proto_order_variants()
{
	local meta="$1"; shift
	local pfx="$1"; shift
	local name="$1"; shift
	local sfx="$1"; shift
<<<<<<< HEAD
<<<<<<< HEAD
	local atomic="$1"

	local basename="arch_${atomic}_${pfx}${name}${sfx}"

	local template="$(find_fallback_template "${pfx}" "${name}" "${sfx}" "${order}")"

=======
	local arch="$1"
	local atomic="$2"
=======
	local atomic="$1"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	local basename="arch_${atomic}_${pfx}${name}${sfx}"

	local template="$(find_fallback_template "${pfx}" "${name}" "${sfx}" "${order}")"

<<<<<<< HEAD
	if [ -z "$arch" ]; then
		gen_proto_order_variant "${meta}" "${pfx}" "${name}" "${sfx}" "" "$@"

		if meta_has_acquire "${meta}"; then
			gen_proto_order_variant "${meta}" "${pfx}" "${name}" "${sfx}" "_acquire" "$@"
		fi
		if meta_has_release "${meta}"; then
			gen_proto_order_variant "${meta}" "${pfx}" "${name}" "${sfx}" "_release" "$@"
		fi
		if meta_has_relaxed "${meta}"; then
			gen_proto_order_variant "${meta}" "${pfx}" "${name}" "${sfx}" "_relaxed" "$@"
		fi

		echo ""
	fi

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	# If we don't have relaxed atomics, then we don't bother with ordering fallbacks
	# read_acquire and set_release need to be templated, though
	if ! meta_has_relaxed "${meta}"; then
		gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "" "$@"

		if meta_has_acquire "${meta}"; then
			gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "_acquire" "$@"
		fi

		if meta_has_release "${meta}"; then
			gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "_release" "$@"
		fi

		return
	fi

	printf "#ifndef ${basename}_relaxed\n"

	if [ ! -z "${template}" ]; then
		printf "#ifdef ${basename}\n"
	fi

	gen_basic_fallbacks "${basename}"

	if [ ! -z "${template}" ]; then
<<<<<<< HEAD
<<<<<<< HEAD
		printf "#endif /* ${basename} */\n\n"
=======
		printf "#endif /* ${arch}${atomic}_${pfx}${name}${sfx} */\n\n"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		printf "#endif /* ${basename} */\n\n"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "" "$@"
		gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "_acquire" "$@"
		gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "_release" "$@"
		gen_proto_fallback "${meta}" "${pfx}" "${name}" "${sfx}" "_relaxed" "$@"
	fi

	printf "#else /* ${basename}_relaxed */\n\n"

	gen_template_fallback "${ATOMICDIR}/fallbacks/acquire"  "${meta}" "${pfx}" "${name}" "${sfx}" "_acquire" "$@"
	gen_template_fallback "${ATOMICDIR}/fallbacks/release"  "${meta}" "${pfx}" "${name}" "${sfx}" "_release" "$@"
	gen_template_fallback "${ATOMICDIR}/fallbacks/fence"  "${meta}" "${pfx}" "${name}" "${sfx}" "" "$@"

	printf "#endif /* ${basename}_relaxed */\n\n"
}

gen_order_fallbacks()
{
	local xchg="$1"; shift

cat <<EOF

#ifndef ${xchg}_acquire
#define ${xchg}_acquire(...) \\
	__atomic_op_acquire(${xchg}, __VA_ARGS__)
#endif

#ifndef ${xchg}_release
#define ${xchg}_release(...) \\
	__atomic_op_release(${xchg}, __VA_ARGS__)
#endif

#ifndef ${xchg}
#define ${xchg}(...) \\
	__atomic_op_fence(${xchg}, __VA_ARGS__)
#endif

EOF
}

gen_xchg_fallbacks()
{
	local xchg="$1"; shift
	printf "#ifndef ${xchg}_relaxed\n"

	gen_basic_fallbacks ${xchg}

	printf "#else /* ${xchg}_relaxed */\n"

	gen_order_fallbacks ${xchg}

	printf "#endif /* ${xchg}_relaxed */\n\n"
}

gen_try_cmpxchg_fallback()
{
	local order="$1"; shift;

cat <<EOF
<<<<<<< HEAD
<<<<<<< HEAD
#ifndef arch_try_cmpxchg${order}
#define arch_try_cmpxchg${order}(_ptr, _oldp, _new) \\
({ \\
	typeof(*(_ptr)) *___op = (_oldp), ___o = *___op, ___r; \\
	___r = arch_cmpxchg${order}((_ptr), ___o, (_new)); \\
=======
#ifndef ${ARCH}try_cmpxchg${order}
#define ${ARCH}try_cmpxchg${order}(_ptr, _oldp, _new) \\
({ \\
	typeof(*(_ptr)) *___op = (_oldp), ___o = *___op, ___r; \\
	___r = ${ARCH}cmpxchg${order}((_ptr), ___o, (_new)); \\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#ifndef arch_try_cmpxchg${order}
#define arch_try_cmpxchg${order}(_ptr, _oldp, _new) \\
({ \\
	typeof(*(_ptr)) *___op = (_oldp), ___o = *___op, ___r; \\
	___r = arch_cmpxchg${order}((_ptr), ___o, (_new)); \\
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (unlikely(___r != ___o)) \\
		*___op = ___r; \\
	likely(___r == ___o); \\
})
<<<<<<< HEAD
<<<<<<< HEAD
#endif /* arch_try_cmpxchg${order} */
=======
#endif /* ${ARCH}try_cmpxchg${order} */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#endif /* arch_try_cmpxchg${order} */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

EOF
}

gen_try_cmpxchg_fallbacks()
{
<<<<<<< HEAD
<<<<<<< HEAD
	printf "#ifndef arch_try_cmpxchg_relaxed\n"
	printf "#ifdef arch_try_cmpxchg\n"

	gen_basic_fallbacks "arch_try_cmpxchg"

	printf "#endif /* arch_try_cmpxchg */\n\n"
=======
	printf "#ifndef ${ARCH}try_cmpxchg_relaxed\n"
	printf "#ifdef ${ARCH}try_cmpxchg\n"
=======
	printf "#ifndef arch_try_cmpxchg_relaxed\n"
	printf "#ifdef arch_try_cmpxchg\n"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	gen_basic_fallbacks "arch_try_cmpxchg"

<<<<<<< HEAD
	printf "#endif /* ${ARCH}try_cmpxchg */\n\n"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	printf "#endif /* arch_try_cmpxchg */\n\n"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	for order in "" "_acquire" "_release" "_relaxed"; do
		gen_try_cmpxchg_fallback "${order}"
	done

<<<<<<< HEAD
<<<<<<< HEAD
	printf "#else /* arch_try_cmpxchg_relaxed */\n"

	gen_order_fallbacks "arch_try_cmpxchg"

	printf "#endif /* arch_try_cmpxchg_relaxed */\n\n"
=======
	printf "#else /* ${ARCH}try_cmpxchg_relaxed */\n"
=======
	printf "#else /* arch_try_cmpxchg_relaxed */\n"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	gen_order_fallbacks "arch_try_cmpxchg"

<<<<<<< HEAD
	printf "#endif /* ${ARCH}try_cmpxchg_relaxed */\n\n"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	printf "#endif /* arch_try_cmpxchg_relaxed */\n\n"
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

cat << EOF
// SPDX-License-Identifier: GPL-2.0

// Generated by $0
// DO NOT MODIFY THIS FILE DIRECTLY

#ifndef _LINUX_ATOMIC_FALLBACK_H
#define _LINUX_ATOMIC_FALLBACK_H

#include <linux/compiler.h>

EOF

<<<<<<< HEAD
<<<<<<< HEAD
for xchg in "arch_xchg" "arch_cmpxchg" "arch_cmpxchg64"; do
=======
for xchg in "${ARCH}xchg" "${ARCH}cmpxchg" "${ARCH}cmpxchg64"; do
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
for xchg in "arch_xchg" "arch_cmpxchg" "arch_cmpxchg64"; do
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	gen_xchg_fallbacks "${xchg}"
done

gen_try_cmpxchg_fallbacks

grep '^[a-z]' "$1" | while read name meta args; do
<<<<<<< HEAD
<<<<<<< HEAD
	gen_proto "${meta}" "${name}" "atomic" "int" ${args}
=======
	gen_proto "${meta}" "${name}" "${ARCH}" "atomic" "int" ${args}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	gen_proto "${meta}" "${name}" "atomic" "int" ${args}
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
done

cat <<EOF
#ifdef CONFIG_GENERIC_ATOMIC64
#include <asm-generic/atomic64.h>
#endif

EOF

grep '^[a-z]' "$1" | while read name meta args; do
<<<<<<< HEAD
<<<<<<< HEAD
	gen_proto "${meta}" "${name}" "atomic64" "s64" ${args}
=======
	gen_proto "${meta}" "${name}" "${ARCH}" "atomic64" "s64" ${args}
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	gen_proto "${meta}" "${name}" "atomic64" "s64" ${args}
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
done

cat <<EOF
#endif /* _LINUX_ATOMIC_FALLBACK_H */
EOF
