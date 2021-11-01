/* SPDX-License-Identifier: GPL-2.0 */
#ifndef BOOT_BOOT_H
#define BOOT_BOOT_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <asm/extable.h>
#include <linux/types.h>

=======
#include <linux/types.h>

#define BOOT_STACK_OFFSET 0x8000

#ifndef __ASSEMBLY__

#include <linux/compiler.h>

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
#include <asm/extable.h>
#include <linux/types.h>

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void startup_kernel(void);
unsigned long detect_memory(void);
bool is_ipl_block_dump(void);
void store_ipl_parmblock(void);
void setup_boot_command_line(void);
void parse_boot_command_line(void);
void verify_facilities(void);
void print_missing_facilities(void);
<<<<<<< HEAD
<<<<<<< HEAD
void sclp_early_setup_buffer(void);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
void sclp_early_setup_buffer(void);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
void print_pgm_check_info(void);
unsigned long get_random_base(unsigned long safe_addr);
void __printf(1, 2) decompressor_printk(const char *fmt, ...);

<<<<<<< HEAD
<<<<<<< HEAD
/* Symbols defined by linker scripts */
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
/* Symbols defined by linker scripts */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
extern const char kernel_version[];
extern unsigned long memory_limit;
extern unsigned long vmalloc_size;
extern int vmalloc_size_set;
extern int kaslr_enabled;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
extern char __boot_data_start[], __boot_data_end[];
extern char __boot_data_preserved_start[], __boot_data_preserved_end[];
extern char _decompressor_syms_start[], _decompressor_syms_end[];
extern char _stack_start[], _stack_end[];
<<<<<<< HEAD

unsigned long read_ipl_report(unsigned long safe_offset);

=======

unsigned long read_ipl_report(unsigned long safe_offset);

#endif /* __ASSEMBLY__ */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

unsigned long read_ipl_report(unsigned long safe_offset);

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif /* BOOT_BOOT_H */
