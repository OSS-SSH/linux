/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef _LINUX_IO_URING_H
#define _LINUX_IO_URING_H

#include <linux/sched.h>
#include <linux/xarray.h>

#if defined(CONFIG_IO_URING)
struct sock *io_uring_get_socket(struct file *file);
<<<<<<< HEAD
void __io_uring_cancel(bool cancel_all);
void __io_uring_free(struct task_struct *tsk);

static inline void io_uring_files_cancel(void)
{
	if (current->io_uring)
		__io_uring_cancel(false);
}
static inline void io_uring_task_cancel(void)
{
	if (current->io_uring)
		__io_uring_cancel(true);
=======
void __io_uring_cancel(struct files_struct *files);
void __io_uring_free(struct task_struct *tsk);

static inline void io_uring_files_cancel(struct files_struct *files)
{
	if (current->io_uring)
		__io_uring_cancel(files);
}
static inline void io_uring_task_cancel(void)
{
	return io_uring_files_cancel(NULL);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
}
static inline void io_uring_free(struct task_struct *tsk)
{
	if (tsk->io_uring)
		__io_uring_free(tsk);
}
#else
static inline struct sock *io_uring_get_socket(struct file *file)
{
	return NULL;
}
static inline void io_uring_task_cancel(void)
{
}
<<<<<<< HEAD
static inline void io_uring_files_cancel(void)
=======
static inline void io_uring_files_cancel(struct files_struct *files)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
{
}
static inline void io_uring_free(struct task_struct *tsk)
{
}
#endif

#endif
