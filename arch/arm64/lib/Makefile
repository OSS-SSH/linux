# SPDX-License-Identifier: GPL-2.0
lib-y		:= clear_user.o delay.o copy_from_user.o		\
<<<<<<< HEAD
<<<<<<< HEAD
		   copy_to_user.o copy_page.o				\
=======
		   copy_to_user.o copy_in_user.o copy_page.o		\
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		   copy_to_user.o copy_page.o				\
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		   clear_page.o csum.o insn.o memchr.o memcpy.o		\
		   memset.o memcmp.o strcmp.o strncmp.o strlen.o	\
		   strnlen.o strchr.o strrchr.o tishift.o

ifeq ($(CONFIG_KERNEL_MODE_NEON), y)
obj-$(CONFIG_XOR_BLOCKS)	+= xor-neon.o
CFLAGS_REMOVE_xor-neon.o	+= -mgeneral-regs-only
CFLAGS_xor-neon.o		+= -ffreestanding
endif

lib-$(CONFIG_ARCH_HAS_UACCESS_FLUSHCACHE) += uaccess_flushcache.o

obj-$(CONFIG_CRC32) += crc32.o

obj-$(CONFIG_FUNCTION_ERROR_INJECTION) += error-inject.o

obj-$(CONFIG_ARM64_MTE) += mte.o

obj-$(CONFIG_KASAN_SW_TAGS) += kasan_sw_tags.o
