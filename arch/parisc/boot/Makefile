# SPDX-License-Identifier: GPL-2.0-only
#
# Makefile for the linux parisc-specific parts of the boot image creator.
#

targets := image
targets += bzImage
subdir- := compressed

$(obj)/image: vmlinux FORCE
	$(call if_changed,objcopy)

$(obj)/bzImage: $(obj)/compressed/vmlinux FORCE
	$(call if_changed,objcopy)

$(obj)/compressed/vmlinux: FORCE
	$(Q)$(MAKE) $(build)=$(obj)/compressed $@
<<<<<<< HEAD
<<<<<<< HEAD
=======

install: $(CONFIGURE) $(obj)/bzImage
	sh -x  $(srctree)/$(obj)/install.sh $(KERNELRELEASE) $(obj)/bzImage \
	      System.map "$(INSTALL_PATH)"
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
