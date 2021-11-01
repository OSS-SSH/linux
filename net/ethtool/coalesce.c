// SPDX-License-Identifier: GPL-2.0-only

#include "netlink.h"
#include "common.h"

struct coalesce_req_info {
	struct ethnl_req_info		base;
};

struct coalesce_reply_data {
	struct ethnl_reply_data		base;
	struct ethtool_coalesce		coalesce;
<<<<<<< HEAD
<<<<<<< HEAD
	struct kernel_ethtool_coalesce	kernel_coalesce;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct kernel_ethtool_coalesce	kernel_coalesce;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	u32				supported_params;
};

#define COALESCE_REPDATA(__reply_base) \
	container_of(__reply_base, struct coalesce_reply_data, base)

#define __SUPPORTED_OFFSET ETHTOOL_A_COALESCE_RX_USECS
static u32 attr_to_mask(unsigned int attr_type)
{
	return BIT(attr_type - __SUPPORTED_OFFSET);
}

/* build time check that indices in ethtool_ops::supported_coalesce_params
 * match corresponding attribute types with an offset
 */
#define __CHECK_SUPPORTED_OFFSET(x) \
	static_assert((ETHTOOL_ ## x) == \
		      BIT((ETHTOOL_A_ ## x) - __SUPPORTED_OFFSET))
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES_IRQ);
__CHECK_SUPPORTED_OFFSET(COALESCE_STATS_BLOCK_USECS);
__CHECK_SUPPORTED_OFFSET(COALESCE_USE_ADAPTIVE_RX);
__CHECK_SUPPORTED_OFFSET(COALESCE_USE_ADAPTIVE_TX);
__CHECK_SUPPORTED_OFFSET(COALESCE_PKT_RATE_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES_LOW);
__CHECK_SUPPORTED_OFFSET(COALESCE_PKT_RATE_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_USECS_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_RX_MAX_FRAMES_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_USECS_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_TX_MAX_FRAMES_HIGH);
__CHECK_SUPPORTED_OFFSET(COALESCE_RATE_SAMPLE_INTERVAL);

const struct nla_policy ethnl_coalesce_get_policy[] = {
	[ETHTOOL_A_COALESCE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
};

static int coalesce_prepare_data(const struct ethnl_req_info *req_base,
				 struct ethnl_reply_data *reply_base,
				 struct genl_info *info)
{
	struct coalesce_reply_data *data = COALESCE_REPDATA(reply_base);
<<<<<<< HEAD
<<<<<<< HEAD
	struct netlink_ext_ack *extack = info ? info->extack : NULL;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct netlink_ext_ack *extack = info ? info->extack : NULL;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct net_device *dev = reply_base->dev;
	int ret;

	if (!dev->ethtool_ops->get_coalesce)
		return -EOPNOTSUPP;
	data->supported_params = dev->ethtool_ops->supported_coalesce_params;
	ret = ethnl_ops_begin(dev);
	if (ret < 0)
		return ret;
<<<<<<< HEAD
<<<<<<< HEAD
	ret = dev->ethtool_ops->get_coalesce(dev, &data->coalesce,
					     &data->kernel_coalesce, extack);
=======
	ret = dev->ethtool_ops->get_coalesce(dev, &data->coalesce);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	ret = dev->ethtool_ops->get_coalesce(dev, &data->coalesce,
					     &data->kernel_coalesce, extack);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	ethnl_ops_complete(dev);

	return ret;
}

static int coalesce_reply_size(const struct ethnl_req_info *req_base,
			       const struct ethnl_reply_data *reply_base)
{
	return nla_total_size(sizeof(u32)) +	/* _RX_USECS */
	       nla_total_size(sizeof(u32)) +	/* _RX_MAX_FRAMES */
	       nla_total_size(sizeof(u32)) +	/* _RX_USECS_IRQ */
	       nla_total_size(sizeof(u32)) +	/* _RX_MAX_FRAMES_IRQ */
	       nla_total_size(sizeof(u32)) +	/* _TX_USECS */
	       nla_total_size(sizeof(u32)) +	/* _TX_MAX_FRAMES */
	       nla_total_size(sizeof(u32)) +	/* _TX_USECS_IRQ */
	       nla_total_size(sizeof(u32)) +	/* _TX_MAX_FRAMES_IRQ */
	       nla_total_size(sizeof(u32)) +	/* _STATS_BLOCK_USECS */
	       nla_total_size(sizeof(u8)) +	/* _USE_ADAPTIVE_RX */
	       nla_total_size(sizeof(u8)) +	/* _USE_ADAPTIVE_TX */
	       nla_total_size(sizeof(u32)) +	/* _PKT_RATE_LOW */
	       nla_total_size(sizeof(u32)) +	/* _RX_USECS_LOW */
	       nla_total_size(sizeof(u32)) +	/* _RX_MAX_FRAMES_LOW */
	       nla_total_size(sizeof(u32)) +	/* _TX_USECS_LOW */
	       nla_total_size(sizeof(u32)) +	/* _TX_MAX_FRAMES_LOW */
	       nla_total_size(sizeof(u32)) +	/* _PKT_RATE_HIGH */
	       nla_total_size(sizeof(u32)) +	/* _RX_USECS_HIGH */
	       nla_total_size(sizeof(u32)) +	/* _RX_MAX_FRAMES_HIGH */
	       nla_total_size(sizeof(u32)) +	/* _TX_USECS_HIGH */
	       nla_total_size(sizeof(u32)) +	/* _TX_MAX_FRAMES_HIGH */
<<<<<<< HEAD
<<<<<<< HEAD
	       nla_total_size(sizeof(u32)) +	/* _RATE_SAMPLE_INTERVAL */
	       nla_total_size(sizeof(u8)) +	/* _USE_CQE_MODE_TX */
	       nla_total_size(sizeof(u8));	/* _USE_CQE_MODE_RX */
=======
	       nla_total_size(sizeof(u32));	/* _RATE_SAMPLE_INTERVAL */
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	       nla_total_size(sizeof(u32)) +	/* _RATE_SAMPLE_INTERVAL */
	       nla_total_size(sizeof(u8)) +	/* _USE_CQE_MODE_TX */
	       nla_total_size(sizeof(u8));	/* _USE_CQE_MODE_RX */
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
}

static bool coalesce_put_u32(struct sk_buff *skb, u16 attr_type, u32 val,
			     u32 supported_params)
{
	if (!val && !(supported_params & attr_to_mask(attr_type)))
		return false;
	return nla_put_u32(skb, attr_type, val);
}

static bool coalesce_put_bool(struct sk_buff *skb, u16 attr_type, u32 val,
			      u32 supported_params)
{
	if (!val && !(supported_params & attr_to_mask(attr_type)))
		return false;
	return nla_put_u8(skb, attr_type, !!val);
}

static int coalesce_fill_reply(struct sk_buff *skb,
			       const struct ethnl_req_info *req_base,
			       const struct ethnl_reply_data *reply_base)
{
	const struct coalesce_reply_data *data = COALESCE_REPDATA(reply_base);
<<<<<<< HEAD
<<<<<<< HEAD
	const struct kernel_ethtool_coalesce *kcoal = &data->kernel_coalesce;
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	const struct kernel_ethtool_coalesce *kcoal = &data->kernel_coalesce;
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	const struct ethtool_coalesce *coal = &data->coalesce;
	u32 supported = data->supported_params;

	if (coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS,
			     coal->rx_coalesce_usecs, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES,
			     coal->rx_max_coalesced_frames, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS_IRQ,
			     coal->rx_coalesce_usecs_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ,
			     coal->rx_max_coalesced_frames_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS,
			     coal->tx_coalesce_usecs, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES,
			     coal->tx_max_coalesced_frames, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS_IRQ,
			     coal->tx_coalesce_usecs_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ,
			     coal->tx_max_coalesced_frames_irq, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_STATS_BLOCK_USECS,
			     coal->stats_block_coalesce_usecs, supported) ||
	    coalesce_put_bool(skb, ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX,
			      coal->use_adaptive_rx_coalesce, supported) ||
	    coalesce_put_bool(skb, ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX,
			      coal->use_adaptive_tx_coalesce, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_PKT_RATE_LOW,
			     coal->pkt_rate_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS_LOW,
			     coal->rx_coalesce_usecs_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW,
			     coal->rx_max_coalesced_frames_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS_LOW,
			     coal->tx_coalesce_usecs_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW,
			     coal->tx_max_coalesced_frames_low, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_PKT_RATE_HIGH,
			     coal->pkt_rate_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_USECS_HIGH,
			     coal->rx_coalesce_usecs_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH,
			     coal->rx_max_coalesced_frames_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_USECS_HIGH,
			     coal->tx_coalesce_usecs_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH,
			     coal->tx_max_coalesced_frames_high, supported) ||
	    coalesce_put_u32(skb, ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL,
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
			     coal->rate_sample_interval, supported) ||
	    coalesce_put_bool(skb, ETHTOOL_A_COALESCE_USE_CQE_MODE_TX,
			      kcoal->use_cqe_mode_tx, supported) ||
	    coalesce_put_bool(skb, ETHTOOL_A_COALESCE_USE_CQE_MODE_RX,
			      kcoal->use_cqe_mode_rx, supported))
<<<<<<< HEAD
=======
			     coal->rate_sample_interval, supported))
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
		return -EMSGSIZE;

	return 0;
}

const struct ethnl_request_ops ethnl_coalesce_request_ops = {
	.request_cmd		= ETHTOOL_MSG_COALESCE_GET,
	.reply_cmd		= ETHTOOL_MSG_COALESCE_GET_REPLY,
	.hdr_attr		= ETHTOOL_A_COALESCE_HEADER,
	.req_info_size		= sizeof(struct coalesce_req_info),
	.reply_data_size	= sizeof(struct coalesce_reply_data),

	.prepare_data		= coalesce_prepare_data,
	.reply_size		= coalesce_reply_size,
	.fill_reply		= coalesce_fill_reply,
};

/* COALESCE_SET */

const struct nla_policy ethnl_coalesce_set_policy[] = {
	[ETHTOOL_A_COALESCE_HEADER]		=
		NLA_POLICY_NESTED(ethnl_header_policy),
	[ETHTOOL_A_COALESCE_RX_USECS]		= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_USECS_IRQ]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_USECS]		= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_USECS_IRQ]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_STATS_BLOCK_USECS]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX]	= { .type = NLA_U8 },
	[ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX]	= { .type = NLA_U8 },
	[ETHTOOL_A_COALESCE_PKT_RATE_LOW]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_USECS_LOW]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_USECS_LOW]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_PKT_RATE_HIGH]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_USECS_HIGH]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_USECS_HIGH]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH]	= { .type = NLA_U32 },
	[ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL] = { .type = NLA_U32 },
<<<<<<< HEAD
<<<<<<< HEAD
	[ETHTOOL_A_COALESCE_USE_CQE_MODE_TX]	= NLA_POLICY_MAX(NLA_U8, 1),
	[ETHTOOL_A_COALESCE_USE_CQE_MODE_RX]	= NLA_POLICY_MAX(NLA_U8, 1),
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	[ETHTOOL_A_COALESCE_USE_CQE_MODE_TX]	= NLA_POLICY_MAX(NLA_U8, 1),
	[ETHTOOL_A_COALESCE_USE_CQE_MODE_RX]	= NLA_POLICY_MAX(NLA_U8, 1),
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
};

int ethnl_set_coalesce(struct sk_buff *skb, struct genl_info *info)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct kernel_ethtool_coalesce kernel_coalesce = {};
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	struct kernel_ethtool_coalesce kernel_coalesce = {};
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	struct ethtool_coalesce coalesce = {};
	struct ethnl_req_info req_info = {};
	struct nlattr **tb = info->attrs;
	const struct ethtool_ops *ops;
	struct net_device *dev;
	u32 supported_params;
	bool mod = false;
	int ret;
	u16 a;

	ret = ethnl_parse_header_dev_get(&req_info,
					 tb[ETHTOOL_A_COALESCE_HEADER],
					 genl_info_net(info), info->extack,
					 true);
	if (ret < 0)
		return ret;
	dev = req_info.dev;
	ops = dev->ethtool_ops;
	ret = -EOPNOTSUPP;
	if (!ops->get_coalesce || !ops->set_coalesce)
		goto out_dev;

	/* make sure that only supported parameters are present */
	supported_params = ops->supported_coalesce_params;
	for (a = ETHTOOL_A_COALESCE_RX_USECS; a < __ETHTOOL_A_COALESCE_CNT; a++)
		if (tb[a] && !(supported_params & attr_to_mask(a))) {
			ret = -EINVAL;
			NL_SET_ERR_MSG_ATTR(info->extack, tb[a],
					    "cannot modify an unsupported parameter");
			goto out_dev;
		}

	rtnl_lock();
	ret = ethnl_ops_begin(dev);
	if (ret < 0)
		goto out_rtnl;
<<<<<<< HEAD
<<<<<<< HEAD
	ret = ops->get_coalesce(dev, &coalesce, &kernel_coalesce,
				info->extack);
=======
	ret = ops->get_coalesce(dev, &coalesce);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	ret = ops->get_coalesce(dev, &coalesce, &kernel_coalesce,
				info->extack);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (ret < 0)
		goto out_ops;

	ethnl_update_u32(&coalesce.rx_coalesce_usecs,
			 tb[ETHTOOL_A_COALESCE_RX_USECS], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES], &mod);
	ethnl_update_u32(&coalesce.rx_coalesce_usecs_irq,
			 tb[ETHTOOL_A_COALESCE_RX_USECS_IRQ], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames_irq,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_IRQ], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs,
			 tb[ETHTOOL_A_COALESCE_TX_USECS], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs_irq,
			 tb[ETHTOOL_A_COALESCE_TX_USECS_IRQ], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames_irq,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_IRQ], &mod);
	ethnl_update_u32(&coalesce.stats_block_coalesce_usecs,
			 tb[ETHTOOL_A_COALESCE_STATS_BLOCK_USECS], &mod);
	ethnl_update_bool32(&coalesce.use_adaptive_rx_coalesce,
			    tb[ETHTOOL_A_COALESCE_USE_ADAPTIVE_RX], &mod);
	ethnl_update_bool32(&coalesce.use_adaptive_tx_coalesce,
			    tb[ETHTOOL_A_COALESCE_USE_ADAPTIVE_TX], &mod);
	ethnl_update_u32(&coalesce.pkt_rate_low,
			 tb[ETHTOOL_A_COALESCE_PKT_RATE_LOW], &mod);
	ethnl_update_u32(&coalesce.rx_coalesce_usecs_low,
			 tb[ETHTOOL_A_COALESCE_RX_USECS_LOW], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames_low,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_LOW], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs_low,
			 tb[ETHTOOL_A_COALESCE_TX_USECS_LOW], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames_low,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_LOW], &mod);
	ethnl_update_u32(&coalesce.pkt_rate_high,
			 tb[ETHTOOL_A_COALESCE_PKT_RATE_HIGH], &mod);
	ethnl_update_u32(&coalesce.rx_coalesce_usecs_high,
			 tb[ETHTOOL_A_COALESCE_RX_USECS_HIGH], &mod);
	ethnl_update_u32(&coalesce.rx_max_coalesced_frames_high,
			 tb[ETHTOOL_A_COALESCE_RX_MAX_FRAMES_HIGH], &mod);
	ethnl_update_u32(&coalesce.tx_coalesce_usecs_high,
			 tb[ETHTOOL_A_COALESCE_TX_USECS_HIGH], &mod);
	ethnl_update_u32(&coalesce.tx_max_coalesced_frames_high,
			 tb[ETHTOOL_A_COALESCE_TX_MAX_FRAMES_HIGH], &mod);
	ethnl_update_u32(&coalesce.rate_sample_interval,
			 tb[ETHTOOL_A_COALESCE_RATE_SAMPLE_INTERVAL], &mod);
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	ethnl_update_u8(&kernel_coalesce.use_cqe_mode_tx,
			tb[ETHTOOL_A_COALESCE_USE_CQE_MODE_TX], &mod);
	ethnl_update_u8(&kernel_coalesce.use_cqe_mode_rx,
			tb[ETHTOOL_A_COALESCE_USE_CQE_MODE_RX], &mod);
<<<<<<< HEAD
=======
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	ret = 0;
	if (!mod)
		goto out_ops;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = dev->ethtool_ops->set_coalesce(dev, &coalesce, &kernel_coalesce,
					     info->extack);
=======
	ret = dev->ethtool_ops->set_coalesce(dev, &coalesce);
>>>>>>> d5cf6b5674f37a44bbece21e8ef09dbcf9515554
=======
	ret = dev->ethtool_ops->set_coalesce(dev, &coalesce, &kernel_coalesce,
					     info->extack);
>>>>>>> a8fa06cfb065a2e9663fe7ce32162762b5fcef5b
	if (ret < 0)
		goto out_ops;
	ethtool_notify(dev, ETHTOOL_MSG_COALESCE_NTF, NULL);

out_ops:
	ethnl_ops_complete(dev);
out_rtnl:
	rtnl_unlock();
out_dev:
	dev_put(dev);
	return ret;
}
