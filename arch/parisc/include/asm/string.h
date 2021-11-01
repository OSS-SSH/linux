/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _PA_STRING_H_
#define _PA_STRING_H_

#define __HAVE_ARCH_MEMSET
extern void * memset(void *, int, size_t);

#define __HAVE_ARCH_MEMCPY
void * memcpy(void * dest,const void *src,size_t count);

<<<<<<< HEAD
<<<<<<< HEAD
=======
#define __HAVE_ARCH_STRLEN
extern size_t strlen(const char *s);

#define __HAVE_ARCH_STRCPY
extern char *strcpy(char *dest, const char *src);

#define __HAVE_ARCH_STRNCPY
extern char *strncpy(char *dest, const char *src, size_t count);

#define __HAVE_ARCH_STRCAT
extern char *strcat(char *dest, const char *src);

#define __HAVE_ARCH_MEMSET
extern void *memset(void *, int, size_t);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif
