#ifndef __KERNEL__
#define __KERNEL__
#endif
#ifndef MODULE
#define MODULE
#endif

#include <linux/errno.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/in.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/ip.h>
#include <linux/module.h>

#include <linux/version.h>
#if LINUX_VERSION_CODE > KERNEL_VERSION(3, 3, 0)
#include <asm/switch_to.h>
#else
#include <asm/system.h>
#endif

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/dma.h>

MODULE_LICENSE("GPL");

static struct net_device *vnet_dev;

static void emulator_rx_packet(struct sk_buff *skb, struct net_device *dev)
{
    /* 参考LDD3 */
    unsigned char *type;
    struct iphdr *ih;

    __be32 *saddr, *daddr, tmp;
    unsigned char tmp_dev_addr[ETH_ALEN];
    struct ethhdr *ethhdr;
    struct sk_buff *rx_skb;

    //从硬件读出/保存数据
    /* 对调“源/目的”的MAC地址 */
    ethhdr = (struct ethhdr *)skb->data;
    memcpy(tmp_dev_addr, ethhdr->h_dest, ETH_ALEN);
    memcpy(ethhdr->h_dest, ethhdr->h_source, ETH_ALEN);
    memcpy(ethhdr->h_source, tmp_dev_addr, ETH_ALEN);

    /* 对调“源/目的”的IP地址 */
    ih = (struct iphdr *)(skb->data + sizeof(struct ethhdr));
    saddr = &ih->saddr;
    daddr = &ih->daddr;
    tmp = *saddr;
    *saddr = *daddr;
    *daddr = tmp;

    type = skb->data + sizeof(struct ethhdr) + sizeof(struct iphdr);
    //修改类型，原来0x8表示ping
    *type = 0; /* 0表示reply */

    ih->check = 0; /* and rebuild the checksum (ip need it) */
    ih->check = ip_fast_csum((unsigned char *)ih, ih->ihl);

    //构造一个sk_buff
    rx_skb = dev_alloc_skb(skb->len + 2);
    skb_reserve(rx_skb, 2); /* align IP on 16B boundary */  /*使用skb_reserve()来腾出2字节头部空间  */
    memcpy(skb_put(rx_skb, skb->len), skb->data, skb->len); /*使用memcpy()将之前修改好的sk_buff->data复制到新的sk_buff里*/
                                                            // skb_put():来动态扩大sk_buff结构体里中的数据区，避免溢出
                     
    /* write metadata,and then pass to the receive level */
    rx_skb->dev = dev;
    rx_skb->protocol = eth_type_trans(rx_skb, dev);
    rx_skb->ip_summed = CHECKSUM_UNNECESSARY; /* don't check it */

    /* 更新接收统计信息,并使用netif_rx( )来 传递sk_fuffer收包 */
    dev->stats.rx_packets++;
    dev->stats.rx_bytes += skb->len;
    // dev->last_rx = jiffies; //收包时间戳

    netif_rx(rx_skb);
}

static int virt_net_sendpacket(struct sk_buff *skb, struct net_device *dev)
{
    static int cnt = 0;

    printk(" virt_net_sendpacket cnt = %d \n", ++cnt);

    /* 对于真实的网卡，把skb里的数据通过网卡发送出去 */

    netif_stop_queue(dev);  /* 停止该网卡的队列 */
    /*                   */ /* 把skb的数据写入网卡 */

    /* 构造一个假的sk_buff上报 */
    emulator_rx_packet(skb, dev);

    dev_kfree_skb(skb); /* 释放skb */

    /* 更新统计信息 */
    dev->stats.tx_packets++;
    dev->stats.tx_bytes += skb->len;

    netif_wake_queue(dev); /* 数据全部发送出去后，唤醒网卡的队列 */

    return 0;
}

static int s3c_vnet_init(void)
{
    /* 1. 分配一个net_device结构体 */
    //vnet_dev = alloc_netdev(0, "vnet%d", ether_setup, 1); /* 也可以使用alloc_etherdev函数来分配 */
    ether_setup(vnet_dev);

    /* 2. 设置net_device结构体 */
    // vnet_dev->hard_start_xmit = virt_net_sendpacket; /* 发包函数 */

    /* 2.1 设置MAC地址 */
    vnet_dev->dev_addr[0] = 0x08;
    vnet_dev->dev_addr[1] = 0x89;
    vnet_dev->dev_addr[2] = 0x89;
    vnet_dev->dev_addr[3] = 0x89;
    vnet_dev->dev_addr[4] = 0x89;
    vnet_dev->dev_addr[5] = 0x11;

    /* 2.2 设置下面两项才能ping通 */
    /* keep the default flags, just add NOARP */
    vnet_dev->flags |= IFF_NOARP;
    vnet_dev->features |= NETIF_F_IP_CSUM;

    /* 3. 注册net_device结构体：register_netdev */
    register_netdev(vnet_dev);

    return 0;
}

static void s3c_vnet_exit(void)
{
    unregister_netdev(vnet_dev);
    free_netdev(vnet_dev);
}

module_init(s3c_vnet_init);
module_exit(s3c_vnet_exit);
