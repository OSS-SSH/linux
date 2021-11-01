/*
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#define UART0_PHYS_BASE (0xf1000000 + 0x12000)

#define UART_THR ((volatile unsigned char *)(UART0_PHYS_BASE + 0x0))
#define UART_LSR ((volatile unsigned char *)(UART0_PHYS_BASE + 0x14))

#define LSR_THRE	0x20

<<<<<<< HEAD
<<<<<<< HEAD
static inline void putc(const char c)
=======
static void putc(const char c)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static inline void putc(const char c)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int i;

	for (i = 0; i < 0x1000; i++) {
		/* Transmit fifo not full? */
		if (*UART_LSR & LSR_THRE)
			break;
	}

	*UART_THR = c;
}

<<<<<<< HEAD
<<<<<<< HEAD
static inline void flush(void)
=======
static void flush(void)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static inline void flush(void)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
}

/*
 * nothing to do
 */
#define arch_decomp_setup()
