/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __QCOM_WNCSS_H__
#define __QCOM_WNCSS_H__

struct qcom_iris;
struct qcom_wcnss;

extern struct platform_driver qcom_iris_driver;

struct wcnss_vreg_info {
	const char * const name;
	int min_voltage;
	int max_voltage;

	int load_uA;

	bool super_turbo;
};

<<<<<<< HEAD
<<<<<<< HEAD
struct qcom_iris *qcom_iris_probe(struct device *parent, bool *use_48mhz_xo);
void qcom_iris_remove(struct qcom_iris *iris);
int qcom_iris_enable(struct qcom_iris *iris);
void qcom_iris_disable(struct qcom_iris *iris);

=======
int qcom_iris_enable(struct qcom_iris *iris);
void qcom_iris_disable(struct qcom_iris *iris);

void qcom_wcnss_assign_iris(struct qcom_wcnss *wcnss, struct qcom_iris *iris, bool use_48mhz_xo);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
struct qcom_iris *qcom_iris_probe(struct device *parent, bool *use_48mhz_xo);
void qcom_iris_remove(struct qcom_iris *iris);
int qcom_iris_enable(struct qcom_iris *iris);
void qcom_iris_disable(struct qcom_iris *iris);

>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
#endif
