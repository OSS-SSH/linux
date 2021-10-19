// SPDX-License-Identifier: GPL-2.0+
/*
 *  Pvpanic Device Support
 *
 *  Copyright (C) 2021 Oracle.
 */

#ifndef PVPANIC_H_
#define PVPANIC_H_

struct pvpanic_instance {
	void __iomem *base;
	unsigned int capability;
	unsigned int events;
	struct list_head list;
};

<<<<<<< HEAD
int pvpanic_probe(struct pvpanic_instance *pi);
void pvpanic_remove(struct pvpanic_instance *pi);
=======
int devm_pvpanic_probe(struct device *dev, struct pvpanic_instance *pi);
>>>>>>> 337c5b93cca6f9be4b12580ce75a06eae468236a

#endif /* PVPANIC_H_ */
