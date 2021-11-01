// SPDX-License-Identifier: GPL-2.0-only
/*
 * Filtering ARP tables module.
 *
 * Copyright (C) 2002 David S. Miller (davem@redhat.com)
 *
 */

#include <linux/module.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter_arp/arp_tables.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David S. Miller <davem@redhat.com>");
MODULE_DESCRIPTION("arptables filter table");

#define FILTER_VALID_HOOKS ((1 << NF_ARP_IN) | (1 << NF_ARP_OUT) | \
			   (1 << NF_ARP_FORWARD))

<<<<<<< HEAD
<<<<<<< HEAD
=======
static int __net_init arptable_filter_table_init(struct net *net);

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
static const struct xt_table packet_filter = {
	.name		= "filter",
	.valid_hooks	= FILTER_VALID_HOOKS,
	.me		= THIS_MODULE,
	.af		= NFPROTO_ARP,
	.priority	= NF_IP_PRI_FILTER,
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.table_init	= arptable_filter_table_init,
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

/* The work comes in here from netfilter.c */
static unsigned int
arptable_filter_hook(void *priv, struct sk_buff *skb,
		     const struct nf_hook_state *state)
{
	return arpt_do_table(skb, state, priv);
}

static struct nf_hook_ops *arpfilter_ops __read_mostly;

<<<<<<< HEAD
<<<<<<< HEAD
static int arptable_filter_table_init(struct net *net)
=======
static int __net_init arptable_filter_table_init(struct net *net)
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
static int arptable_filter_table_init(struct net *net)
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
{
	struct arpt_replace *repl;
	int err;

	repl = arpt_alloc_initial_table(&packet_filter);
	if (repl == NULL)
		return -ENOMEM;
	err = arpt_register_table(net, &packet_filter, repl, arpfilter_ops);
	kfree(repl);
	return err;
}

static void __net_exit arptable_filter_net_pre_exit(struct net *net)
{
	arpt_unregister_table_pre_exit(net, "filter");
}

static void __net_exit arptable_filter_net_exit(struct net *net)
{
	arpt_unregister_table(net, "filter");
}

static struct pernet_operations arptable_filter_net_ops = {
	.exit = arptable_filter_net_exit,
	.pre_exit = arptable_filter_net_pre_exit,
};

static int __init arptable_filter_init(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	int ret = xt_register_template(&packet_filter,
				       arptable_filter_table_init);

	if (ret < 0)
		return ret;
<<<<<<< HEAD

	arpfilter_ops = xt_hook_ops_alloc(&packet_filter, arptable_filter_hook);
	if (IS_ERR(arpfilter_ops)) {
		xt_unregister_template(&packet_filter);
		return PTR_ERR(arpfilter_ops);
	}

	ret = register_pernet_subsys(&arptable_filter_net_ops);
	if (ret < 0) {
		xt_unregister_template(&packet_filter);
=======
	int ret;
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b

	arpfilter_ops = xt_hook_ops_alloc(&packet_filter, arptable_filter_hook);
	if (IS_ERR(arpfilter_ops)) {
		xt_unregister_template(&packet_filter);
		return PTR_ERR(arpfilter_ops);
	}

	ret = register_pernet_subsys(&arptable_filter_net_ops);
	if (ret < 0) {
<<<<<<< HEAD
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
		xt_unregister_template(&packet_filter);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		kfree(arpfilter_ops);
		return ret;
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======
	ret = arptable_filter_table_init(&init_net);
	if (ret) {
		unregister_pernet_subsys(&arptable_filter_net_ops);
		kfree(arpfilter_ops);
	}

>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	return ret;
}

static void __exit arptable_filter_fini(void)
{
	unregister_pernet_subsys(&arptable_filter_net_ops);
<<<<<<< HEAD
<<<<<<< HEAD
	xt_unregister_template(&packet_filter);
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	xt_unregister_template(&packet_filter);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	kfree(arpfilter_ops);
}

module_init(arptable_filter_init);
module_exit(arptable_filter_fini);
