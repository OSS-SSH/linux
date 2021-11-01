#include <linux/spinlock.h>

#include <asm/checksum.h>
#include <asm/console.h>
#include <asm/page.h>
#include <asm/string.h>
#include <linux/uaccess.h>

#include <asm-generic/asm-prototypes.h>

extern void __divl(void);
extern void __reml(void);
extern void __divq(void);
extern void __remq(void);
extern void __divlu(void);
extern void __remlu(void);
extern void __divqu(void);
extern void __remqu(void);
<<<<<<< HEAD
<<<<<<< HEAD
extern unsigned long __udiv_qrnnd(unsigned long *, unsigned long, unsigned long , unsigned long);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
extern unsigned long __udiv_qrnnd(unsigned long *, unsigned long, unsigned long , unsigned long);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
