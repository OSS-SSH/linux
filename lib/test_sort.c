// SPDX-License-Identifier: GPL-2.0-only
<<<<<<< HEAD
<<<<<<< HEAD

#include <kunit/test.h>

=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======

#include <kunit/test.h>

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#include <linux/sort.h>
#include <linux/slab.h>
#include <linux/module.h>

/* a simple boot-time regression test */

#define TEST_LEN 1000

<<<<<<< HEAD
<<<<<<< HEAD
static int cmpint(const void *a, const void *b)
=======
static int __init cmpint(const void *a, const void *b)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int cmpint(const void *a, const void *b)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	return *(int *)a - *(int *)b;
}

<<<<<<< HEAD
<<<<<<< HEAD
static void test_sort(struct kunit *test)
{
	int *a, i, r = 1;

	a = kunit_kmalloc_array(test, TEST_LEN, sizeof(*a), GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, a);
=======
static int __init test_sort_init(void)
=======
static void test_sort(struct kunit *test)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	int *a, i, r = 1;

<<<<<<< HEAD
	a = kmalloc_array(TEST_LEN, sizeof(*a), GFP_KERNEL);
	if (!a)
		return err;
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	a = kunit_kmalloc_array(test, TEST_LEN, sizeof(*a), GFP_KERNEL);
	KUNIT_ASSERT_NOT_ERR_OR_NULL(test, a);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	for (i = 0; i < TEST_LEN; i++) {
		r = (r * 725861) % 6599;
		a[i] = r;
	}

	sort(a, TEST_LEN, sizeof(*a), cmpint, NULL);

<<<<<<< HEAD
<<<<<<< HEAD
	for (i = 0; i < TEST_LEN-1; i++)
		KUNIT_ASSERT_LE(test, a[i], a[i + 1]);
}

static struct kunit_case sort_test_cases[] = {
	KUNIT_CASE(test_sort),
	{}
};

static struct kunit_suite sort_test_suite = {
	.name = "lib_sort",
	.test_cases = sort_test_cases,
};

kunit_test_suites(&sort_test_suite);
=======
	err = -EINVAL;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	for (i = 0; i < TEST_LEN-1; i++)
		KUNIT_ASSERT_LE(test, a[i], a[i + 1]);
}

static struct kunit_case sort_test_cases[] = {
	KUNIT_CASE(test_sort),
	{}
};

static struct kunit_suite sort_test_suite = {
	.name = "lib_sort",
	.test_cases = sort_test_cases,
};

<<<<<<< HEAD
module_init(test_sort_init);
module_exit(test_sort_exit);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
kunit_test_suites(&sort_test_suite);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

MODULE_LICENSE("GPL");
