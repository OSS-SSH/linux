/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __CGROUP_HELPERS_H
#define __CGROUP_HELPERS_H
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <errno.h>
#include <string.h>

#define clean_errno() (errno == 0 ? "None" : strerror(errno))
#define log_err(MSG, ...) fprintf(stderr, "(%s:%d: errno: %s) " MSG "\n", \
	__FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

<<<<<<< HEAD
<<<<<<< HEAD
/* cgroupv2 related */
int cgroup_setup_and_join(const char *path);
int create_and_get_cgroup(const char *path);
unsigned long long get_cgroup_id(const char *path);

int join_cgroup(const char *path);

int setup_cgroup_environment(void);
void cleanup_cgroup_environment(void);

/* cgroupv1 related */
int set_classid(unsigned int id);
int join_classid(void);

int setup_classid_environment(void);
void cleanup_classid_environment(void);

#endif /* __CGROUP_HELPERS_H */
=======

=======
/* cgroupv2 related */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
int cgroup_setup_and_join(const char *path);
int create_and_get_cgroup(const char *path);
unsigned long long get_cgroup_id(const char *path);

int join_cgroup(const char *path);

int setup_cgroup_environment(void);
void cleanup_cgroup_environment(void);

<<<<<<< HEAD
#endif
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
/* cgroupv1 related */
int set_classid(unsigned int id);
int join_classid(void);

int setup_classid_environment(void);
void cleanup_classid_environment(void);

#endif /* __CGROUP_HELPERS_H */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
